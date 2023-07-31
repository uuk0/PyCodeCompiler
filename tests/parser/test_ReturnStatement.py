import typing
from unittest import TestCase
from pycompiler import Parser, Lexer, TypeResolver
from pycompiler.Parser import FunctionDefinitionNode, AssignmentExpression, NameAccessExpression, ConstantAccessExpression, ReturnStatement
from pycompiler.Lexer import TokenType


class TestReturnStatement(TestCase):
    def test_simple(self):
        parser = Parser.Parser("def test(): return 10")
        expr: FunctionDefinitionNode = typing.cast(FunctionDefinitionNode, parser.parse()[0])

        self.assertEqual(ReturnStatement(
            ConstantAccessExpression(10)
        ), expr.body[0])

    def test_outside_function(self):
        parser = Parser.Parser("return 10")
        self.assertRaises(SyntaxError, parser.parse)

