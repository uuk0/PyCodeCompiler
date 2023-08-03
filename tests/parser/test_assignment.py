from unittest import TestCase
from pycompiler import Parser, Lexer


class TestAssignment(TestCase):
    def test_simple(self):
        parser = Parser.Parser("target = source")
        expr = parser.try_parse_assignment()

        self.assertEqual(
            Parser.AssignmentExpression(
                [
                    Parser.NameAccessExpression(Lexer.TokenType.IDENTIFIER("target")),
                ],
                Lexer.TokenType.EQUAL_SIGN("="),
                Parser.NameAccessExpression(Lexer.TokenType.IDENTIFIER("source")),
            ),
            expr,
        )

    def test_simple_lhs_expr(self):
        parser = Parser.Parser("target[self] = source")
        expr = parser.try_parse_assignment()

        self.assertEqual(
            Parser.AssignmentExpression(
                [
                    Parser.SubscriptionExpression(
                        Parser.NameAccessExpression(
                            Lexer.TokenType.IDENTIFIER("target")
                        ),
                        Lexer.TokenType.OPENING_SQUARE_BRACKET("["),
                        Parser.NameAccessExpression(Lexer.TokenType.IDENTIFIER("self")),
                        Lexer.TokenType.CLOSING_SQUARE_BRACKET("]"),
                    ),
                ],
                Lexer.TokenType.EQUAL_SIGN("="),
                Parser.NameAccessExpression(Lexer.TokenType.IDENTIFIER("source")),
            ),
            expr,
        )

    def test_multi_target_simple(self):
        parser = Parser.Parser("target = target2 = source")
        expr = parser.try_parse_assignment()

        self.assertEqual(
            Parser.AssignmentExpression(
                [
                    Parser.NameAccessExpression(Lexer.TokenType.IDENTIFIER("target")),
                    Parser.NameAccessExpression(Lexer.TokenType.IDENTIFIER("target2")),
                ],
                Lexer.TokenType.EQUAL_SIGN("="),
                Parser.NameAccessExpression(Lexer.TokenType.IDENTIFIER("source")),
            ),
            expr,
        )
