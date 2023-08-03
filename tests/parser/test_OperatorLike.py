import typing
from unittest import TestCase
from pycompiler import Parser, Lexer, TypeResolver
from pycompiler.Parser import (
    FunctionDefinitionNode,
    AssignmentExpression,
    NameAccessExpression,
    ConstantAccessExpression,
    BinaryOperatorExpression,
    WalrusOperatorExpression,
    PriorityBrackets,
)
from pycompiler.Lexer import TokenType


class TestPriorityBrackets(TestCase):
    def test_basic(self):
        parser = Parser.Parser("ab = (10)")
        expr = parser.parse()
        self.assertEqual(
            [
                AssignmentExpression(
                    [
                        NameAccessExpression(TokenType.IDENTIFIER("ab")),
                    ],
                    TokenType.EQUAL_SIGN("="),
                    PriorityBrackets(ConstantAccessExpression(10)),
                ),
            ],
            expr,
        )


class TestWalrusOperator(TestCase):
    def test_basic(self):
        parser = Parser.Parser("test = ab := 10")
        expr = parser.parse()
        self.assertEqual(
            [
                AssignmentExpression(
                    [
                        NameAccessExpression(TokenType.IDENTIFIER("test")),
                    ],
                    TokenType.EQUAL_SIGN("="),
                    WalrusOperatorExpression(
                        NameAccessExpression(TokenType.IDENTIFIER("ab")),
                        ConstantAccessExpression(10),
                    ),
                ),
            ],
            expr,
        )
