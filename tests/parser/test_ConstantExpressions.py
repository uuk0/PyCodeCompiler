from __future__ import annotations

import unittest

from pycompiler.parser.Parser import Parser
from pycompiler.parser.AbstractSyntaxTreeNode import AbstractSyntaxTreeNode
from pycompiler.parser.ConstantValueExpressionNode import ConstantValueExpressionNode


class ConstantTestBase(unittest.TestCase):
    def variants(self, code: str, expected: AbstractSyntaxTreeNode):
        parser = Parser(code)
        self.assertEqual(expected, parser.try_parse_expression())
        parser = Parser(code)
        self.assertEqual(expected, parser.try_parse_code_line_obj())
        parser = Parser(code)
        self.assertEqual([expected], parser.parse_code_block())


class TestIntegerLiterals(ConstantTestBase):
    def test_basic(self):
        self.variants("10", ConstantValueExpressionNode(10))


class TestStringLiterals(ConstantTestBase):
    def test_basic_single(self):
        self.variants("'test'", ConstantValueExpressionNode("test"))

    def test_basic_double(self):
        self.variants('"test"', ConstantValueExpressionNode("test"))

    def test_basic_single_w_other(self):
        self.variants("'test\"'", ConstantValueExpressionNode('test"'))

    def test_basic_double_w_other(self):
        self.variants('"test\'"', ConstantValueExpressionNode("test'"))

    def test_basic_single_escaped(self):
        self.variants("'test\\''", ConstantValueExpressionNode("test'"))

    def test_basic_double_escaped(self):
        self.variants('"test\\""', ConstantValueExpressionNode('test"'))

    def test_basic_single_escape_trick(self):
        self.variants("'test\\\\'", ConstantValueExpressionNode("test\\"))

    def test_basic_double_escape_trick(self):
        self.variants('"test\\\\"', ConstantValueExpressionNode("test\\"))
