from __future__ import annotations

from pycompiler.emitter.CodeBuilder import CodeBuilder
from pycompiler.parser.Parser import Parser
from pycompiler.parser.FunctionDefinitionStatementNode import FunctionDefinitionNode
from pycompiler.visitors.FunctionDefinitionExtractor import FunctionDefinitionExtractor
from pycompiler.visitors.Scope import Scope


class Project:
    def __init__(self, build_folder: str = None):
        self.build_folder = build_folder

    def compile_file(self, code: str) -> str:
        parser = Parser(code)
        module = parser.parse_module()

        module.update_child_parent_relation()

        function_definition_visitor = FunctionDefinitionExtractor()
        function_definition_visitor.visit_any(module)
        function_definition_visitor.definitions.append(
            FunctionDefinitionNode("_STATIC", None, None, module.nodes)
        )

        functions = [
            function.get_function_definition()
            for function in function_definition_visitor.definitions
        ]

        return "\n\n".join(functions)
