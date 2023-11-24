from __future__ import annotations

import pathlib
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

    def get_c_code(self):
        return f"""// PyCodeCompiler output
#include <stdlib.h>
#include "pyinclude.h"

// Functions

{"\n\n".join([
    function.get_function_definition()
    for function in self.function_definitions
])}
"""


class Project:
    def __init__(self, build_folder: str = None):
        self.build_folder = build_folder

    def add_file(self, file: str, entry=False):
        pass

    def add_source_directory(self, directory: str):
        pass

    def ensure_module_included(self, module_name: str):
        pass

    def build(self, reuse_intermediates=False):
        pass
