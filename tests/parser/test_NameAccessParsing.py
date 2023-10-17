from unittest import TestCase

from pycompiler.parser.Parser import Parser
from pycompiler.parser.NameAccessNode import NameAccessNode
from pycompiler.Lexer import Token, TokenType


class TestNameAccessParsing(TestCase):
    def test_expression(self):
        parser = Parser("test")
        self.assertEqual(parser.try_parse_expression(), NameAccessNode("test"))

    def test_code_line_expression(self):
        parser = Parser("test")
        self.assertEqual(parser.try_parse_code_line_obj(), NameAccessNode("test"))
