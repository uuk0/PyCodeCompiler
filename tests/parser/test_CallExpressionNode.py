from unittest import TestCase

from pycompiler.parser.Parser import Parser
from pycompiler.parser.NameAccessNode import NameAccessNode
from pycompiler.parser.CallExpression import CallExpression, CallExpressionArgument
from pycompiler.parser.util import ArgType


class TestAssignmentParsing(TestCase):
    def helper(self, code: str, expected: CallExpression):
        with self.subTest("expression"):
            parser = Parser(code)
            self.assertEqual(expected, parser.try_parse_expression())

        with self.subTest("code line"):
            parser = Parser(code)
            self.assertEqual(expected, parser.try_parse_code_line_obj())

        with self.subTest("code block"):
            parser = Parser(code)
            self.assertEqual([expected], parser.parse_code_block())

        with self.subTest("copy eq itself"):
            parser = Parser(code)
            expr = parser.try_parse_expression()
            self.assertEqual(expr, expr.copy())
            self.assertIsNot(expr, expr.copy())

    def test_missing_closing_bracket(self):
        self.assertRaises(SyntaxError, lambda: Parser("test(").try_parse_expression())

    def test_missing_comma(self):
        self.assertRaises(
            SyntaxError, lambda: Parser("test(x af)").try_parse_expression()
        )

    def test_star_without_value(self):
        self.assertRaises(SyntaxError, lambda: Parser("test(*)").try_parse_expression())

    def test_star_without_value_eof(self):
        self.assertRaises(SyntaxError, lambda: Parser("test(*").try_parse_expression())

    def test_double_star_without_value(self):
        self.assertRaises(
            SyntaxError, lambda: Parser("test(**)").try_parse_expression()
        )

    def test_double_star_without_value_eof(self):
        self.assertRaises(SyntaxError, lambda: Parser("test(**").try_parse_expression())

    def test_triple_star(self):
        self.assertRaises(
            SyntaxError, lambda: Parser("test(***a)").try_parse_expression()
        )

    def test_missing_keyword_value(self):
        self.assertRaises(
            SyntaxError, lambda: Parser("test(a=)").try_parse_expression()
        )

    def test_missing_keyword_value_eof(self):
        self.assertRaises(SyntaxError, lambda: Parser("test(a=").try_parse_expression())

    def test_expression(self):
        self.helper(
            "test()",
            CallExpression(NameAccessNode("test"), []),
        )

    def test_expression_arg(self):
        self.helper(
            "test(a)",
            CallExpression(
                NameAccessNode("test"),
                [CallExpressionArgument(ArgType.NORMAL, NameAccessNode("a"))],
            ),
        )

    def test_expression_arg_trailing(self):
        self.helper(
            "test(a,)",
            CallExpression(
                NameAccessNode("test"),
                [CallExpressionArgument(ArgType.NORMAL, NameAccessNode("a"))],
            ),
        )

    def test_expression_arg_multi(self):
        self.helper(
            "test(a, b)",
            CallExpression(
                NameAccessNode("test"),
                [
                    CallExpressionArgument(ArgType.NORMAL, NameAccessNode("a")),
                    CallExpressionArgument(ArgType.NORMAL, NameAccessNode("b")),
                ],
            ),
        )

    def test_expression_arg_multi_trailing(self):
        self.helper(
            "test(a, b,)",
            CallExpression(
                NameAccessNode("test"),
                [
                    CallExpressionArgument(ArgType.NORMAL, NameAccessNode("a")),
                    CallExpressionArgument(ArgType.NORMAL, NameAccessNode("b")),
                ],
            ),
        )

    def test_expression_keyword(self):
        self.helper(
            "test(a=b)",
            CallExpression(
                NameAccessNode("test"),
                [CallExpressionArgument(ArgType.KEYWORD, NameAccessNode("b"), "a")],
            ),
        )

    def test_expression_star(self):
        self.helper(
            "test(*a)",
            CallExpression(
                NameAccessNode("test"),
                [CallExpressionArgument(ArgType.STAR, NameAccessNode("a"))],
            ),
        )

    def test_expression_star_star(self):
        self.helper(
            "test(**a)",
            CallExpression(
                NameAccessNode("test"),
                [CallExpressionArgument(ArgType.STAR_STAR, NameAccessNode("a"))],
            ),
        )
