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
from pycompiler.TypeResolver import BinaryOperatorPriorityRewriter


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


class TestOperatorPriority(TestCase):
    def test_simple(self):
        parser = Parser.Parser("8 * 7 + 10")
        expr = parser.parse()

        self.assertEqual(
            [
                BinaryOperatorExpression(
                    ConstantAccessExpression(8),
                    BinaryOperatorExpression.BinaryOperation.MULTIPLY,
                    BinaryOperatorExpression(
                        ConstantAccessExpression(7),
                        BinaryOperatorExpression.BinaryOperation.PLUS,
                        ConstantAccessExpression(10),
                    ),
                )
            ],
            expr,
        )

        BinaryOperatorPriorityRewriter().visit_any_list(expr)

        self.assertEqual(
            [
                BinaryOperatorExpression(
                    BinaryOperatorExpression(
                        ConstantAccessExpression(8),
                        BinaryOperatorExpression.BinaryOperation.MULTIPLY,
                        ConstantAccessExpression(7),
                    ),
                    BinaryOperatorExpression.BinaryOperation.PLUS,
                    ConstantAccessExpression(10),
                )
            ],
            expr,
        )

    def test_double_possible(self):
        parser = Parser.Parser("8 + 7 * 10 + 12")
        expr = parser.parse()

        self.assertEqual(
            [
                BinaryOperatorExpression(
                    ConstantAccessExpression(8),
                    BinaryOperatorExpression.BinaryOperation.PLUS,
                    BinaryOperatorExpression(
                        ConstantAccessExpression(7),
                        BinaryOperatorExpression.BinaryOperation.MULTIPLY,
                        BinaryOperatorExpression(
                            ConstantAccessExpression(10),
                            BinaryOperatorExpression.BinaryOperation.PLUS,
                            ConstantAccessExpression(12),
                        ),
                    ),
                )
            ],
            expr,
        )

        BinaryOperatorPriorityRewriter().visit_any_list(expr)

        self.assertEqual(
            [
                BinaryOperatorExpression(
                    ConstantAccessExpression(8),
                    BinaryOperatorExpression.BinaryOperation.PLUS,
                    BinaryOperatorExpression(
                        BinaryOperatorExpression(
                            ConstantAccessExpression(7),
                            BinaryOperatorExpression.BinaryOperation.MULTIPLY,
                            ConstantAccessExpression(10),
                        ),
                        BinaryOperatorExpression.BinaryOperation.PLUS,
                        ConstantAccessExpression(12),
                    ),
                )
            ],
            expr,
        )
