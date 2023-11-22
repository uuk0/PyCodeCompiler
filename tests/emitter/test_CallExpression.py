from __future__ import annotations

import typing
import unittest

from pycompiler.parser.Parser import Parser
from pycompiler.emitter.CodeBuilder import CodeBuilder


class TestCallExpressions(unittest.TestCase):
    def helper(self, code: str, c_code: str):
        parser = Parser(code)
        code = parser.try_parse_expression()
        self.assertIsNotNone(code)
        builder = CodeBuilder()
        code.push_code(builder)
        self.assertEqual(c_code, builder.get_full_code())

    def test_basic(self):
        self.helper("test()", "test0();")

    def test_single_parameters(self):
        self.helper("test(a)", "test0(a1);")

    def test_chained_calls(self):
        self.helper("test()()", "void* var1 = test0();\nvar1();")

    def test_multi_parameters(self):
        self.helper("test(a, b)", "test0(a1, b2);")
