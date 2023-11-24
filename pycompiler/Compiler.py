from __future__ import annotations

from pycompiler.emitter.CodeBuilder import CodeBuilder
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


class Project:
    def __init__(self, build_folder: str = None):
        self.build_folder = build_folder

    def compile_file(self, code: str) -> str:
        parser = Parser(code)
        module = parser.parse_module()

        module.update_child_parent_relation()

        module_scope = Scope()
        ScopeAssigner(module_scope).visit_any(module)

        function_definition_visitor = FunctionDefinitionExtractor()
        function_definition_visitor.visit_any(module)

        function_definition_visitor.definitions.append(
            static_function := FunctionDefinitionNode(
                "_STATIC", None, None, module.nodes
            )
        )

        InsertImplicitReturnNoneInFunction().visit_any_list(
            function_definition_visitor.definitions
        )
        MergeGenericsIntoReferenceVisitor().visit_any(module)
        MergeGenericsIntoReferenceVisitor().visit_any_list(
            function_definition_visitor.definitions
        )
        OperatorPrioritiesRewriter().visit_any(module)
        OperatorPrioritiesRewriter().visit_any_list(
            function_definition_visitor.definitions
        )

        module.update_child_parent_relation()
        static_function.update_child_parent_relation()
        Local2ModuleRewriter().visit_any(static_function)

        functions = [
            function.get_function_definition()
            for function in function_definition_visitor.definitions
        ]

        return f"""// PyCodeCompiler output
#include <stdlib.h>
#include "pyinclude.h"

// Functions

{"\n\n".join(functions)}
"""

    def add_file(self, file: str):
        pass

    def add_source_directory(self, directory: str):
        pass

    def ensure_module_included(self, module_name: str):
        pass

    def build(self, reuse_intermediates=False):
        pass
