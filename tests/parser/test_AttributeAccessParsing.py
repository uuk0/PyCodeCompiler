from unittest import TestCase

from pycompiler.parser.Parser import Parser
from pycompiler.parser.NameAccessNode import NameAccessNode
from pycompiler.parser.AttributeAccessExpressionNode import (
    AttributeAccessExpressionNode,
)


class TestAttributeAccess(TestCase):
    def helper(self, code: str, expected: AttributeAccessExpressionNode):
        with self.subTest("direct"):
            parser = Parser(code)
            self.assertEqual(expected, parser.try_parse_expression())

        with self.subTest("target"):
            parser = Parser(code)
            self.assertEqual(expected, parser.try_parse_expression())

        with self.subTest("line"):
            parser = Parser(code)
            self.assertEqual(expected, parser.try_parse_code_line_obj())

        with self.subTest("code block"):
            parser = Parser(code)
            self.assertEqual([expected], parser.parse_code_block())

        with self.subTest("copy equals original"):
            parser = Parser(code)
            expr = parser.try_parse_expression()
            self.assertEqual(expr, expr.copy())
            self.assertIsNot(expr, expr.copy())

    def test_error_on_missing_dot(self):
        self.assertRaises(SyntaxError, lambda: Parser("test.").try_parse_expression())

    def test_error_on_missing_dot_on_multi(self):
        self.assertRaises(
            SyntaxError, lambda: Parser("test.ets2.").try_parse_expression()
        )

    def test_basic(self):
        self.helper(
            "test.test2",
            AttributeAccessExpressionNode(NameAccessNode("test"), "test2"),
        )

    def test_multi_attr(self):
        self.helper(
            "test.test2.test3",
            AttributeAccessExpressionNode(
                AttributeAccessExpressionNode(NameAccessNode("test"), "test2"), "test3"
            ),
        )
