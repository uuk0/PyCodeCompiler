from __future__ import annotations

import typing
import unittest

from pycompiler.emitter import CodeBuilder
from pycompiler.parser.Parser import Parser
from pycompiler.parser.FunctionDefinitionStatementNode import FunctionDefinitionNode


class TestFunctionDefinition(unittest.TestCase):
    def helper(self, code: str, ccode: str):
        node: FunctionDefinitionNode = typing.cast(
            FunctionDefinitionNode, Parser(code).try_parse_code_line_obj()
        )
        self.assertEqual(ccode, node.get_function_definition())
        self.assertEqual(ccode.split("{")[0].rstrip(), node.get_function_declaration())

    def test_basic(self):
        self.helper("def test(): pass", "void* test() {\n    \n}")

    def test_parameter_propagation(self):
        self.helper("def test(x): pass", "void* test(void* x) {\n    \n}")
