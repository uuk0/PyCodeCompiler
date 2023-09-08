from unittest import TestCase
from pycompiler import Parser, Lexer, TypeResolver
from pycompiler.Parser import (
    FunctionDefinitionNode,
    AssignmentExpression,
    NameAccessExpression,
    ConstantAccessExpression,
    PyNewlineNode,
    ImportStatement,
)
from pycompiler.Lexer import TokenType


class TestImportStatement(TestCase):
    def test_basic(self):
        parser = Parser.Parser("import typing")
        expr = parser.parse()
        self.assertEqual(
            [
                ImportStatement("typing"),
            ],
            expr,
        )

    def test_with_dots(self):
        parser = Parser.Parser("import os.path")
        expr = parser.parse()
        self.assertEqual(
            [
                ImportStatement("os.path"),
            ],
            expr,
        )

    def test_with_as(self):
        parser = Parser.Parser("import typing as t")
        expr = parser.parse()
        self.assertEqual(
            [
                ImportStatement("typing", "t"),
            ],
            expr,
        )

    def test_with_dots_and_as(self):
        parser = Parser.Parser("import os.path as p")
        expr = parser.parse()
        self.assertEqual(
            [
                ImportStatement("os.path", "p"),
            ],
            expr,
        )
