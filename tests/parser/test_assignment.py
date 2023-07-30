from unittest import TestCase
from pycompiler import Parser, Lexer


class TestAssignment(TestCase):
    def test_simple(self):
        parser = Parser.Parser("target = source")
        expr = parser.try_parse_assignment()

        self.assertEqual(
            Parser.AssignmentExpression(
                [
                    Parser.NameAccessExpression(Lexer.TokenType.IDENTIFIER("target"))
                ],
                Lexer.TokenType.EQUAL_SIGN("="),
                Parser.NameAccessExpression(Lexer.TokenType.IDENTIFIER("source")),
            ),
            expr,
        )

