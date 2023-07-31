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

