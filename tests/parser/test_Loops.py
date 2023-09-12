import typing
from unittest import TestCase
from pycompiler import Parser, Lexer, TypeResolver
from pycompiler.Parser import (
    AssignmentExpression,
    NameAccessExpression,
    ConstantAccessExpression,
    ClassDefinitionNode,
    PyNewlineNode,
    WhileStatement,
    ForLoopStatement,
    CallExpression,
)
from pycompiler.Lexer import TokenType


class TestWhileStatement(TestCase):
    def test_simple(self):
        parser = Parser.Parser("while 1:\n    test = 10")
        expr = parser.parse()

        self.assertEqual(
            [
                WhileStatement(
                    ConstantAccessExpression(1),
                    [
                        PyNewlineNode(TokenType.NEWLINE("\n")),
                        AssignmentExpression(
                            [
                                NameAccessExpression(TokenType.IDENTIFIER("test")),
                            ],
                            TokenType.EQUAL_SIGN("="),
                            ConstantAccessExpression(10),
                        ),
                    ],
                )
            ],
            expr,
        )


class TestForStatement(TestCase):
    def test_simple(self):
        parser = Parser.Parser("for x in y:\n    test = x()")
        expr = parser.parse()

        self.assertEqual(
            [
                ForLoopStatement(
                    NameAccessExpression(TokenType.IDENTIFIER("x")),
                    NameAccessExpression(TokenType.IDENTIFIER("y")),
                    [
                        PyNewlineNode(TokenType.NEWLINE("\n")),
                        AssignmentExpression(
                            [NameAccessExpression(TokenType.IDENTIFIER("test"))],
                            TokenType.EQUAL_SIGN("="),
                            CallExpression(
                                NameAccessExpression(TokenType.IDENTIFIER("x")),
                                [],
                                TokenType.OPENING_ROUND_BRACKET("("),
                                [],
                                TokenType.CLOSING_ROUND_BRACKET(")"),
                            ),
                        ),
                    ],
                    [],
                )
            ],
            expr,
        )
