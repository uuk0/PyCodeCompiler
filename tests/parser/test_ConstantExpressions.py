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

    def test_basic_underscore(self):
        self.variants("1_0", ConstantValueExpressionNode(10))

    def test_float(self):
        self.variants("10.0", ConstantValueExpressionNode(10.0))

    def test_float_only_end(self):
        self.variants("10.", ConstantValueExpressionNode(10.0))

    def test_float_only_front(self):
        self.variants(".10", ConstantValueExpressionNode(0.1))

    def test_binary(self):
        self.variants("0b10", ConstantValueExpressionNode(0b10))

    def test_octal(self):
        self.variants("0o10", ConstantValueExpressionNode(0o10))

    def test_hex(self):
        self.variants("0x10", ConstantValueExpressionNode(0x10))


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
