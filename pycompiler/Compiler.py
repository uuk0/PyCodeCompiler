from __future__ import annotations

import pathlib
import subprocess
import typing

from pycompiler.emitter.CodeBuilder import CodeBuilder
from pycompiler.parser.ModuleNode import ModuleNode
from pycompiler.parser.Parser import Parser
from pycompiler.parser.FunctionDefinitionStatementNode import FunctionDefinitionNode
from pycompiler.visitors.FunctionDefinitionExtractor import FunctionDefinitionExtractor
from pycompiler.visitors.Local2ModuleRewriter import Local2ModuleRewriter
from pycompiler.visitors.ScopeAssigner import ScopeAssigner
from pycompiler.visitors.OperatorPrioritiesRewriter import OperatorPrioritiesRewriter
from pycompiler.visitors.MergeGenericsIntoReference import (
    MergeGenericsIntoReferenceVisitor,
)
from pycompiler.visitors.InsertImplicitReturnNoneInFunction import (
    InsertImplicitReturnNoneInFunction,
)
from pycompiler.visitors.Scope import Scope


class FileInstance:
    def __init__(self, file: str, module_name: str = None):
        self.file = file
        self.module_name = module_name or file.split("/")[-1].split("\\")[-1].split(".")[0]
        self.code: str | None = None
        self.ast_base: ModuleNode | None = None
        self.function_definitions: typing.List[FunctionDefinitionNode] = []

    def parse(self):
        if self.code is None:
            self.code = pathlib.Path(self.file).read_text()

        parser = Parser(self.code, filename=self.file)
        self.ast_base = parser.parse_module()
        return self

    def apply_ast_operations(self):
        self.ast_base.update_child_parent_relation()

        module_scope = Scope()
        ScopeAssigner(module_scope).visit_any(self.ast_base)

        function_definition_visitor = FunctionDefinitionExtractor()
        function_definition_visitor.visit_any(self.ast_base)

        function_definition_visitor.definitions.append(
            static_function := FunctionDefinitionNode(
                "_STATIC", None, None, self.ast_base.nodes
            )
        )

        InsertImplicitReturnNoneInFunction().visit_any_list(
            function_definition_visitor.definitions
        )
        MergeGenericsIntoReferenceVisitor().visit_any(self.ast_base)
        MergeGenericsIntoReferenceVisitor().visit_any_list(
            function_definition_visitor.definitions
        )
        OperatorPrioritiesRewriter().visit_any(self.ast_base)
        OperatorPrioritiesRewriter().visit_any_list(
            function_definition_visitor.definitions
        )

        self.ast_base.update_child_parent_relation()
        static_function.update_child_parent_relation()
        Local2ModuleRewriter().visit_any(static_function)

        self.function_definitions[:] = function_definition_visitor.definitions

        return self

    def apply_interleaved_optimisations(self):
        pass

    def get_c_code(self) -> str:
        return f"""// PyCodeCompiler output for module {self.module_name}
#include <stdlib.h>
#include "pyinclude.h"

// Functions

{"\n\n".join([
    function.get_function_definition()
    for function in self.function_definitions
])}
"""

    def get_header_code(self) -> str:
        return f"""// PyCodeCompiler HEADER output for module {self.module_name}
#include <stdlib.h>
#include "pyinclude.h"

// Functions

{"\n\n".join([
    function.get_function_declaration()
    for function in self.function_definitions
])}
"""


class Project:
    def __init__(self, build_folder: str = None):
        self.build_folder = build_folder
        self.path = []
        self.known_module_instances: typing.Dict[str, FileInstance] = {}
        self.entry_files: typing.List[FileInstance] = []
        self.pending_module_parsing: typing.List[FileInstance] = []
        self.concrete_module_references: typing.Dict[str, object] = {}  # todo: implement

    def get_concrete_module_reference(self, name: str):
        pass

    def add_file(self, file: str, entry=False):
        file_obj = FileInstance(file)
        self.known_module_instances[file_obj.module_name] = file_obj

        if entry:
            self.entry_files.append(file_obj)

        return self

    def add_source_directory(self, directory: str):
        self.path.append(directory)
        return self

    def ensure_module_included(self, module_name: str):
        if module_name in self.known_module_instances:
            return

        # todo: discover via path
        raise ModuleNotFoundError(module_name)

    def build(self, output_file: str, reuse_intermediates=False):
        include_c_files: typing.List[str] = []

        for module in self.known_module_instances.values():
            self.concrete_module_references[module.module_name] = None  # todo: implement

        for module in self.known_module_instances.values():
            module.parse()
            module.apply_ast_operations()

        while self.pending_module_parsing:
            task = self.pending_module_parsing.pop(-1)
            assert task.module_name in self.known_module_instances, "guard against issue when a file is required by multiple other modules"
            task.parse()
            task.apply_ast_operations()

        for module in self.known_module_instances.values():
            module.apply_interleaved_optimisations()

        for module in self.known_module_instances.values():
            c_file = f"{self.build_folder}/{module.module_name.replace(".", "__")})"
            h_file = f"{self.build_folder}/{module.module_name.replace(".", "__")})"
            include_c_files.append(c_file)

            with open(c_file, mode="w") as f:
                f.write(module.get_c_code())

            with open(h_file, mode="w") as f:
                f.write(module.get_header_code())

        entry_file = f"""// Entry Code created by PyCodeCompiler
#include <stdlib.h>
#include "pyinclude.h"

// Entry Modules
// TODO

int main(int argc, char* args[])
{{
    // TODO: call the entry points one after another!
}}
"""

        with open(f"{self.build_folder}/entry.c", mode="w") as f:
            f.write(entry_file)

        command = [
            "gcc",
            "-o",
            output_file,
            f"{self.build_folder}/entry.c",
        ] + include_c_files
        exit_code = subprocess.call(command)

        if exit_code != 0:
            raise RuntimeError("compilation failed; see above for more information!")
