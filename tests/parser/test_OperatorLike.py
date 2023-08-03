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
    TupleConstructor,
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


class TestTupleConstructor(TestCase):
    def test_singleton(self):
        parser = Parser.Parser("(10,)")
        expr = parser.parse()

        self.assertEqual(
            [
                TupleConstructor(
                    [ConstantAccessExpression(10)],
                ),
            ],
            expr,
        )

    def test_duplex(self):
        parser = Parser.Parser("(10, 20)")
        expr = parser.parse()

        self.assertEqual(
            [
                TupleConstructor(
                    [
                        ConstantAccessExpression(10),
                        ConstantAccessExpression(20),
                    ],
                ),
            ],
            expr,
        )

    def test_duplex_trailing(self):
        parser = Parser.Parser("(10, 20,)")
        expr = parser.parse()

        self.assertEqual(
            [
                TupleConstructor(
                    [
                        ConstantAccessExpression(10),
                        ConstantAccessExpression(20),
                    ],
                ),
            ],
            expr,
        )
