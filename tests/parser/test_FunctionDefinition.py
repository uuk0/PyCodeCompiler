from unittest import TestCase
from pycompiler import Parser, Lexer, TypeResolver
from pycompiler.Parser import FunctionDefinitionNode, AssignmentExpression, NameAccessExpression, ConstantAccessExpression, PyNewlineNode
from pycompiler.Lexer import TokenType


class TestFunctionDefinition(TestCase):
    def test_simple(self):
        parser = Parser.Parser("def xy(): \n    x = 10")
        expr = parser.parse()
        self.assertEqual([FunctionDefinitionNode(
            TokenType.IDENTIFIER("xy"),
            [],
            [],
            [
                PyNewlineNode(TokenType.NEWLINE("\n")),
                AssignmentExpression(
                    [
                        NameAccessExpression(TokenType.IDENTIFIER("x"))
                    ],
                    TokenType.EQUAL_SIGN("="),
                    ConstantAccessExpression(10),
                ),
            ],
        )], expr)

    def test_generic_simple(self):
        parser = Parser.Parser("def xy[a](): \n    x = 10")
        expr = parser.parse()
        self.assertEqual([FunctionDefinitionNode(
            TokenType.IDENTIFIER("xy"),
            [
                TokenType.IDENTIFIER("a")
            ],
            [],
            [
                PyNewlineNode(TokenType.NEWLINE("\n")),
                AssignmentExpression(
                    [
                        NameAccessExpression(TokenType.IDENTIFIER("x"))
                    ],
                    TokenType.EQUAL_SIGN("="),
                    ConstantAccessExpression(10),
                ),
            ],
        )], expr)

    def test_generic_double(self):
        parser = Parser.Parser("def xy[a, b](): \n    x = 10")
        expr = parser.parse()
        self.assertEqual([FunctionDefinitionNode(
            TokenType.IDENTIFIER("xy"),
            [
                TokenType.IDENTIFIER("a"),
                TokenType.IDENTIFIER("b"),
            ],
            [],
            [
                PyNewlineNode(TokenType.NEWLINE("\n")),
                AssignmentExpression(
                    [
                        NameAccessExpression(TokenType.IDENTIFIER("x"))
                    ],
                    TokenType.EQUAL_SIGN("="),
                    ConstantAccessExpression(10),
                ),
            ],
        )], expr)

    def test_generic_double_trailing(self):
        parser = Parser.Parser("def xy[a, b,](): \n    x = 10")
        expr = parser.parse()
        self.assertEqual([FunctionDefinitionNode(
            TokenType.IDENTIFIER("xy"),
            [
                TokenType.IDENTIFIER("a"),
                TokenType.IDENTIFIER("b"),
            ],
            [],
            [
                PyNewlineNode(TokenType.NEWLINE("\n")),
                AssignmentExpression(
                    [
                        NameAccessExpression(TokenType.IDENTIFIER("x"))
                    ],
                    TokenType.EQUAL_SIGN("="),
                    ConstantAccessExpression(10),
                ),
            ],
        )], expr)

    def test_generic_duplicate(self):
        parser = Parser.Parser("def xy[a, a](): \n    x = 10")
        self.assertRaises(NameError, parser.parse)

