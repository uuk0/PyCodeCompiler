from __future__ import annotations

import unittest

from pycompiler.parser.ListConstruction import (
    ListComprehensionNode,
    ListConstructorNode,
)
from pycompiler.parser.NameAccessNode import NameAccessNode, NameWriteAccessNode
from pycompiler.parser.Parser import Parser


class TestListCreation(unittest.TestCase):
    def helper(self, code: str, expected: ListConstructorNode):
        with self.subTest("expression"):
            expr = Parser(code).try_parse_expression()
            self.assertEqual(expected, expr)

        with self.subTest("code line"):
            expr = Parser(code).try_parse_code_line_obj()
            self.assertEqual(expected, expr)

        with self.subTest("code block"):
            expr = Parser(code).parse_code_block()
            self.assertEqual([expected], expr)

        with self.subTest("copy eq"):
            copy = expected.copy()
            self.assertEqual(expected, copy)
            self.assertIsNot(expected, copy)

    def test_missing_closing_bracket(self):
        self.assertRaises(
            SyntaxError, lambda: Parser("[hello world").try_parse_expression()
        )
        self.assertRaises(SyntaxError, lambda: Parser("[hello").try_parse_expression())

    def test_empty(self):
        self.helper("[]", ListConstructorNode([]))

    def test_single(self):
        self.helper("[a]", ListConstructorNode([NameAccessNode("a")]))

    def test_trailing_comma(self):
        self.helper("[a,]", ListConstructorNode([NameAccessNode("a")]))

    def test_double(self):
        self.helper(
            "[a, b]",
            ListConstructorNode([NameAccessNode("a"), NameAccessNode("b")]),
        )

    def test_double_with_trailing(self):
        self.helper(
            "[a, b,]",
            ListConstructorNode([NameAccessNode("a"), NameAccessNode("b")]),
        )

    def test_stacked_two(self):
        self.helper("[[]]", ListConstructorNode([ListConstructorNode([])]))

    def test_stacked_three(self):
        self.helper(
            "[[[]]]",
            ListConstructorNode([ListConstructorNode([ListConstructorNode([])])]),
        )


class ListComprehensionTest(unittest.TestCase):
    def helper(self, code: str, expected: ListComprehensionNode):
        with self.subTest("expression"):
            expr = Parser(code).try_parse_expression()
            self.assertEqual(expected, expr)

        with self.subTest("code line"):
            expr = Parser(code).try_parse_code_line_obj()
            self.assertEqual(expected, expr)

        with self.subTest("code block"):
            expr = Parser(code).parse_code_block()
            self.assertEqual([expected], expr)

        with self.subTest("copy eq"):
            copy = expected.copy()
            self.assertEqual(expected, copy)
            self.assertIsNot(expected, copy)

    def test_basic(self):
        self.helper(
            "[a for a in b]",
            ListComprehensionNode(
                NameAccessNode("a"), NameWriteAccessNode("a"), NameAccessNode("b")
            ),
        )

    def test_with_if(self):
        self.helper(
            "[a for a in b if a]",
            ListComprehensionNode(
                NameAccessNode("a"),
                NameWriteAccessNode("a"),
                NameAccessNode("b"),
                NameAccessNode("a"),
            ),
        )
