import typing
from unittest import TestCase
from pycompiler import Parser, Lexer, TypeResolver
from pycompiler.Parser import (
    AssignmentExpression,
    NameAccessExpression,
    ConstantAccessExpression,
    CallExpression,
)
from pycompiler.Lexer import TokenType


class TestFunctionCall(TestCase):
    def test_simple(self):
        parser = Parser.Parser("test()")
        expr = parser.try_parse_expression()
        self.assertEqual(
            CallExpression(
                NameAccessExpression(TokenType.IDENTIFIER("test")),
                [],
                TokenType.OPENING_ROUND_BRACKET("("),
                [],
                TokenType.CLOSING_ROUND_BRACKET(")"),
            ),
            expr,
        )

    def test_single_arg(self):
        parser = Parser.Parser("test(arg)")
        expr = parser.try_parse_expression()
        self.assertEqual(
            CallExpression(
                NameAccessExpression(TokenType.IDENTIFIER("test")),
                [],
                TokenType.OPENING_ROUND_BRACKET("("),
                [
                    CallExpression.CallExpressionArgument(
                        NameAccessExpression(TokenType.IDENTIFIER("arg")),
                        CallExpression.ParameterType.NORMAL,
                    ),
                ],
                TokenType.CLOSING_ROUND_BRACKET(")"),
            ),
            expr,
        )

    def test_single_arg_trailing(self):
        parser = Parser.Parser("test(arg,)")
        expr = parser.try_parse_expression()
        self.assertEqual(
            CallExpression(
                NameAccessExpression(TokenType.IDENTIFIER("test")),
                [],
                TokenType.OPENING_ROUND_BRACKET("("),
                [
                    CallExpression.CallExpressionArgument(
                        NameAccessExpression(TokenType.IDENTIFIER("arg")),
                        CallExpression.ParameterType.NORMAL,
                    ),
                ],
                TokenType.CLOSING_ROUND_BRACKET(")"),
            ),
            expr,
        )

    def test_double_arg(self):
        parser = Parser.Parser("test(arg, arg2)")
        expr = parser.try_parse_expression()
        self.assertEqual(
            CallExpression(
                NameAccessExpression(TokenType.IDENTIFIER("test")),
                [],
                TokenType.OPENING_ROUND_BRACKET("("),
                [
                    CallExpression.CallExpressionArgument(
                        NameAccessExpression(TokenType.IDENTIFIER("arg")),
                        CallExpression.ParameterType.NORMAL,
                    ),
                    CallExpression.CallExpressionArgument(
                        NameAccessExpression(TokenType.IDENTIFIER("arg2")),
                        CallExpression.ParameterType.NORMAL,
                    ),
                ],
                TokenType.CLOSING_ROUND_BRACKET(")"),
            ),
            expr,
        )

    def test_single_star_arg(self):
        parser = Parser.Parser("test(*arg)")
        expr = parser.try_parse_expression()
        self.assertEqual(
            CallExpression(
                NameAccessExpression(TokenType.IDENTIFIER("test")),
                [],
                TokenType.OPENING_ROUND_BRACKET("("),
                [
                    CallExpression.CallExpressionArgument(
                        NameAccessExpression(TokenType.IDENTIFIER("arg")),
                        CallExpression.ParameterType.STAR,
                    ),
                ],
                TokenType.CLOSING_ROUND_BRACKET(")"),
            ),
            expr,
        )

    def test_star_star_arg(self):
        parser = Parser.Parser("test(**arg)")
        expr = parser.try_parse_expression()
        self.assertEqual(
            CallExpression(
                NameAccessExpression(TokenType.IDENTIFIER("test")),
                [],
                TokenType.OPENING_ROUND_BRACKET("("),
                [
                    CallExpression.CallExpressionArgument(
                        NameAccessExpression(TokenType.IDENTIFIER("arg")),
                        CallExpression.ParameterType.STAR_STAR,
                    ),
                ],
                TokenType.CLOSING_ROUND_BRACKET(")"),
            ),
            expr,
        )

    def test_keyword_arg(self):
        parser = Parser.Parser("test(arg=value)")
        expr = parser.try_parse_expression()
        self.assertEqual(
            CallExpression(
                NameAccessExpression(TokenType.IDENTIFIER("test")),
                [],
                TokenType.OPENING_ROUND_BRACKET("("),
                [
                    CallExpression.CallExpressionArgument(
                        NameAccessExpression(TokenType.IDENTIFIER("value")),
                        CallExpression.ParameterType.KEYWORD,
                        key=TokenType.IDENTIFIER("arg"),
                    ),
                ],
                TokenType.CLOSING_ROUND_BRACKET(")"),
            ),
            expr,
        )
