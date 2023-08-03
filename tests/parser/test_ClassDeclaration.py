import typing
from unittest import TestCase
from pycompiler import Parser, Lexer, TypeResolver
from pycompiler.Parser import (
    AssignmentExpression,
    NameAccessExpression,
    ConstantAccessExpression,
    ClassDefinitionNode,
    PyNewlineNode,
    FunctionDefinitionNode,
    ReturnStatement,
)
from pycompiler.Lexer import TokenType


class TestClassDeclaration(TestCase):
    def test_simple(self):
        parser = Parser.Parser("class xy:\n    attr = 10")
        expr = parser.parse()

        self.assertEqual(
            [
                ClassDefinitionNode(
                    TokenType.IDENTIFIER("xy"),
                    [],
                    [],
                    [
                        PyNewlineNode(TokenType.NEWLINE("\n")),
                        AssignmentExpression(
                            [
                                NameAccessExpression(TokenType.IDENTIFIER("attr")),
                            ],
                            TokenType.EQUAL_SIGN("="),
                            ConstantAccessExpression(10),
                        ),
                    ],
                ),
            ],
            expr,
        )

    def test_parent(self):
        parser = Parser.Parser("class xy(sup):\n    attr = 10")
        expr = parser.parse()

        self.assertEqual(
            [
                ClassDefinitionNode(
                    TokenType.IDENTIFIER("xy"),
                    [],
                    [
                        NameAccessExpression(TokenType.IDENTIFIER("sup")),
                    ],
                    [
                        PyNewlineNode(TokenType.NEWLINE("\n")),
                        AssignmentExpression(
                            [
                                NameAccessExpression(TokenType.IDENTIFIER("attr")),
                            ],
                            TokenType.EQUAL_SIGN("="),
                            ConstantAccessExpression(10),
                        ),
                    ],
                ),
            ],
            expr,
        )

    def test_parent_twice(self):
        parser = Parser.Parser("class xy(sup, sup2):\n    attr = 10")
        expr = parser.parse()

        self.assertEqual(
            [
                ClassDefinitionNode(
                    TokenType.IDENTIFIER("xy"),
                    [],
                    [
                        NameAccessExpression(TokenType.IDENTIFIER("sup")),
                        NameAccessExpression(TokenType.IDENTIFIER("sup2")),
                    ],
                    [
                        PyNewlineNode(TokenType.NEWLINE("\n")),
                        AssignmentExpression(
                            [
                                NameAccessExpression(TokenType.IDENTIFIER("attr")),
                            ],
                            TokenType.EQUAL_SIGN("="),
                            ConstantAccessExpression(10),
                        ),
                    ],
                ),
            ],
            expr,
        )

    def test_generic(self):
        parser = Parser.Parser("class xy[gen]:\n    attr = 10")
        expr = parser.parse()

        self.assertEqual(
            [
                ClassDefinitionNode(
                    TokenType.IDENTIFIER("xy"),
                    [TokenType.IDENTIFIER("gen")],
                    [],
                    [
                        PyNewlineNode(TokenType.NEWLINE("\n")),
                        AssignmentExpression(
                            [
                                NameAccessExpression(TokenType.IDENTIFIER("attr")),
                            ],
                            TokenType.EQUAL_SIGN("="),
                            ConstantAccessExpression(10),
                        ),
                    ],
                ),
            ],
            expr,
        )

    def test_generic_twice(self):
        parser = Parser.Parser("class xy[gen, gen2]:\n    attr = 10")
        expr = parser.parse()

        self.assertEqual(
            [
                ClassDefinitionNode(
                    TokenType.IDENTIFIER("xy"),
                    [TokenType.IDENTIFIER("gen"), TokenType.IDENTIFIER("gen2")],
                    [],
                    [
                        PyNewlineNode(TokenType.NEWLINE("\n")),
                        AssignmentExpression(
                            [
                                NameAccessExpression(TokenType.IDENTIFIER("attr")),
                            ],
                            TokenType.EQUAL_SIGN("="),
                            ConstantAccessExpression(10),
                        ),
                    ],
                ),
            ],
            expr,
        )

    def test_generic_super(self):
        parser = Parser.Parser("class xy[gen](sup):\n    attr = 10")
        expr = parser.parse()

        self.assertEqual(
            [
                ClassDefinitionNode(
                    TokenType.IDENTIFIER("xy"),
                    [TokenType.IDENTIFIER("gen")],
                    [NameAccessExpression(TokenType.IDENTIFIER("sup"))],
                    [
                        PyNewlineNode(TokenType.NEWLINE("\n")),
                        AssignmentExpression(
                            [
                                NameAccessExpression(TokenType.IDENTIFIER("attr")),
                            ],
                            TokenType.EQUAL_SIGN("="),
                            ConstantAccessExpression(10),
                        ),
                    ],
                ),
            ],
            expr,
        )

    def test_double_func_declaration(self):
        parser = Parser.Parser(
            "class xy:\n    def a():\n        return 10\n    def b():\n        return 20"
        )
        expr = parser.parse()

        self.assertEqual(
            [
                ClassDefinitionNode(
                    TokenType.IDENTIFIER("xy"),
                    [],
                    [],
                    [
                        PyNewlineNode(TokenType.NEWLINE("\n")),
                        FunctionDefinitionNode(
                            TokenType.IDENTIFIER("a"),
                            [],
                            [],
                            [
                                PyNewlineNode(TokenType.NEWLINE("\n")),
                                ReturnStatement(ConstantAccessExpression(10)),
                                PyNewlineNode(TokenType.NEWLINE("\n")),
                            ],
                        ),
                        FunctionDefinitionNode(
                            TokenType.IDENTIFIER("b"),
                            [],
                            [],
                            [
                                PyNewlineNode(TokenType.NEWLINE("\n")),
                                ReturnStatement(ConstantAccessExpression(20)),
                            ],
                        ),
                    ],
                )
            ],
            expr,
        )
