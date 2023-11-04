from __future__ import annotations

import typing
import unittest

from pycompiler.parser.Parser import Parser
from pycompiler.parser.util import OperatorType
from pycompiler.parser.OperatorExpressionNode import (
    SingletonOperator,
    BinaryOperator,
    BinaryInplaceOperator,
)
from pycompiler.parser.NameAccessNode import NameAccessNode


class TestSingletonOperator(unittest.TestCase):
    def helper(self, code: str, node: SingletonOperator):
        with self.subTest("basic"):
            self.assertEqual(node, Parser(code).try_parse_expression())

        with self.subTest("line"):
            self.assertEqual(node, Parser(code).try_parse_code_line_obj())

        with self.subTest("block"):
            self.assertEqual([node], Parser(code).parse_code_block())

        with self.subTest("copy"):
            self.assertEqual(node, node.copy())
            self.assertIsNot(node, node.copy())

    def test_plus(self):
        self.helper(
            "+test", SingletonOperator(OperatorType.SINGLE_PLUS, NameAccessNode("test"))
        )

    def test_minus(self):
        self.helper(
            "-test",
            SingletonOperator(OperatorType.SINGLE_MINUS, NameAccessNode("test")),
        )

    def test_invert(self):
        self.helper(
            "~test",
            SingletonOperator(OperatorType.SINGLE_INVERSE, NameAccessNode("test")),
        )

    def test_not(self):
        self.helper(
            "not test",
            SingletonOperator(OperatorType.LOGIC_NOT, NameAccessNode("test")),
        )


class TestBinaryOperator(unittest.TestCase):
    def helper(self, code: str, node: BinaryOperator):
        with self.subTest("basic"):
            self.assertEqual(node, Parser(code).try_parse_expression())

        with self.subTest("line"):
            self.assertEqual(node, Parser(code).try_parse_code_line_obj())

        with self.subTest("block"):
            self.assertEqual([node], Parser(code).parse_code_block())

        with self.subTest("copy"):
            self.assertEqual(node, node.copy())
            self.assertIsNot(node, node.copy())

    def test_add(self):
        self.helper(
            "a + b",
            BinaryOperator(
                OperatorType.BINARY_PLUS, NameAccessNode("a"), NameAccessNode("b")
            ),
        )

    def test_sub(self):
        self.helper(
            "a - b",
            BinaryOperator(
                OperatorType.BINARY_MINUS, NameAccessNode("a"), NameAccessNode("b")
            ),
        )

    def test_times(self):
        self.helper(
            "a * b",
            BinaryOperator(
                OperatorType.BINARY_STAR, NameAccessNode("a"), NameAccessNode("b")
            ),
        )

    def test_pow(self):
        self.helper(
            "a ** b",
            BinaryOperator(
                OperatorType.BINARY_STAR_STAR, NameAccessNode("a"), NameAccessNode("b")
            ),
        )

    def test_truediv(self):
        self.helper(
            "a / b",
            BinaryOperator(
                OperatorType.BINARY_SLASH, NameAccessNode("a"), NameAccessNode("b")
            ),
        )

    def test_floordiv(self):
        self.helper(
            "a // b",
            BinaryOperator(
                OperatorType.BINARY_SLASH_SLASH,
                NameAccessNode("a"),
                NameAccessNode("b"),
            ),
        )

    def test_mod(self):
        self.helper(
            "a % b",
            BinaryOperator(
                OperatorType.BINARY_PERCENT, NameAccessNode("a"), NameAccessNode("b")
            ),
        )

    def test_and(self):
        self.helper(
            "a and b",
            BinaryOperator(
                OperatorType.LOGIC_AND, NameAccessNode("a"), NameAccessNode("b")
            ),
        )

    def test_or(self):
        self.helper(
            "a or b",
            BinaryOperator(
                OperatorType.LOGIC_OR, NameAccessNode("a"), NameAccessNode("b")
            ),
        )

    def test_bitwise_and(self):
        self.helper(
            "a & b",
            BinaryOperator(
                OperatorType.BINARY_LOGIC_AND, NameAccessNode("a"), NameAccessNode("b")
            ),
        )

    def test_bitwise_or(self):
        self.helper(
            "a | b",
            BinaryOperator(
                OperatorType.BINARY_LOGIC_OR, NameAccessNode("a"), NameAccessNode("b")
            ),
        )

    def test_bitwise_xor(self):
        self.helper(
            "a ^ b",
            BinaryOperator(
                OperatorType.BINARY_LOGIC_XOR, NameAccessNode("a"), NameAccessNode("b")
            ),
        )
