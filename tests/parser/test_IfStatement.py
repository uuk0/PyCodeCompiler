from unittest import TestCase
from pycompiler.Parser import (
    Parser,
    IfStatement,
    NameAccessExpression,
    PassStatement,
    PyNewlineNode,
    AssignmentExpression,
)
from pycompiler.Lexer import TokenType


class TestIfStatement(TestCase):
    def test_simple(self):
        parser = Parser("if x: pass")
        expr = parser.parse()
        self.assertEqual(
            [
                IfStatement(
                    NameAccessExpression(TokenType.IDENTIFIER("x")),
                    [
                        PassStatement(),
                    ],
                ),
            ],
            expr,
        )

    def test_simple_with_newline(self):
        parser = Parser("if x:\n    pass")
        expr = parser.parse()
        self.assertEqual(
            [
                IfStatement(
                    NameAccessExpression(TokenType.IDENTIFIER("x")),
                    [
                        PyNewlineNode(),
                        PassStatement(),
                    ],
                ),
            ],
            expr,
        )

    def test_simple_with_else(self):
        parser = Parser("if x: pass\nelse: pass")
        expr = parser.parse()
        self.assertEqual(
            [
                IfStatement(
                    NameAccessExpression(TokenType.IDENTIFIER("x")),
                    [
                        PassStatement(),
                    ],
                    else_block=[
                        PassStatement(),
                    ],
                ),
            ],
            expr,
        )

    def test_simple_with_elif(self):
        parser = Parser("if x: pass\nelif t: pass")
        expr = parser.parse()
        self.assertEqual(
            [
                IfStatement(
                    NameAccessExpression("x"),
                    [
                        PassStatement(),
                    ],
                    [
                        (
                            NameAccessExpression("t"),
                            [
                                PassStatement(),
                            ],
                        )
                    ],
                ),
            ],
            expr,
        )

    def test_simple_with_elif_twice(self):
        parser = Parser("if x: pass\nelif t: pass\nelif u: t = u")
        expr = parser.parse()
        self.assertEqual(
            [
                IfStatement(
                    NameAccessExpression("x"),
                    [
                        PassStatement(),
                    ],
                    [
                        (
                            NameAccessExpression("t"),
                            [
                                PassStatement(),
                            ],
                        ),
                        (
                            NameAccessExpression("u"),
                            [
                                AssignmentExpression(
                                    [
                                        NameAccessExpression("t"),
                                    ],
                                    TokenType.EQUAL_SIGN("="),
                                    NameAccessExpression("u"),
                                ),
                            ],
                        ),
                    ],
                ),
            ],
            expr,
        )

    def test_simple_with_elif_and_else(self):
        parser = Parser("if x: pass\nelif t: pass\nelse: pass")
        expr = parser.parse()
        self.assertEqual(
            [
                IfStatement(
                    NameAccessExpression(TokenType.IDENTIFIER("x")),
                    [
                        PassStatement(),
                    ],
                    [
                        (
                            NameAccessExpression("t"),
                            [
                                PassStatement(),
                            ],
                        )
                    ],
                    [
                        PassStatement(),
                    ],
                ),
            ],
            expr,
        )

    def test_simple_with_elif_twice_and_else(self):
        parser = Parser("if x: pass\nelif t: pass\nelif u: t = u\nelse: pass")
        expr = parser.parse()
        self.assertEqual(
            [
                IfStatement(
                    NameAccessExpression(TokenType.IDENTIFIER("x")),
                    [
                        PassStatement(),
                    ],
                    [
                        (
                            NameAccessExpression("t"),
                            [
                                PassStatement(),
                            ],
                        ),
                        (
                            NameAccessExpression("u"),
                            [
                                AssignmentExpression(
                                    [
                                        NameAccessExpression("t"),
                                    ],
                                    TokenType.EQUAL_SIGN("="),
                                    NameAccessExpression("u"),
                                ),
                            ],
                        ),
                    ],
                    [
                        PassStatement(),
                    ],
                ),
            ],
            expr,
        )
