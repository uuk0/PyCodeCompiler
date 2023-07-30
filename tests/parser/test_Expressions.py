from unittest import TestCase
from pycompiler import Parser, Lexer


class TestExpressions(TestCase):
    def test_identifier(self):
        parser = Parser.Parser("test")
        expression = parser.try_parse_expression()
        self.assertEqual(
            Parser.NameAccessExpression(Lexer.TokenType.IDENTIFIER("test")),
            expression,
        )

    def test_attribute(self):
        parser = Parser.Parser("test.attr")
        expression = parser.try_parse_expression()
        self.assertEqual(
            Parser.AttributeExpression(
                Parser.NameAccessExpression(Lexer.TokenType.IDENTIFIER("test")),
                Lexer.TokenType.DOT("."),
                Lexer.TokenType.IDENTIFIER("attr"),
            ),
            expression,
        )

    def test_attribute_double(self):
        parser = Parser.Parser("test.attr.attr2")
        expression = parser.try_parse_expression()
        self.assertEqual(
            Parser.AttributeExpression(
                Parser.AttributeExpression(
                    Parser.NameAccessExpression(Lexer.TokenType.IDENTIFIER("test")),
                    Lexer.TokenType.DOT("."),
                    Lexer.TokenType.IDENTIFIER("attr"),
                ),
                Lexer.TokenType.DOT("."),
                Lexer.TokenType.IDENTIFIER("attr2"),
            ),
            expression,
        )

    def test_subscription(self):
        parser = Parser.Parser("test[attr]")
        expression = parser.try_parse_expression()
        self.assertEqual(
            Parser.SubscriptionExpression(
                Parser.NameAccessExpression(Lexer.TokenType.IDENTIFIER("test")),
                Lexer.TokenType.OPENING_SQUARE_BRACKET("["),
                Parser.NameAccessExpression(Lexer.TokenType.IDENTIFIER("attr")),
                Lexer.TokenType.CLOSING_SQUARE_BRACKET("]"),
            ),
            expression,
        )

    def test_integer(self):
        parser = Parser.Parser("100")
        expression = parser.try_parse_expression()
        self.assertEqual(
            Parser.ConstantAccessExpression(100),
            expression,
        )

    def test_integer_signed(self):
        parser = Parser.Parser("-100")
        expression = parser.try_parse_expression()
        self.assertEqual(
            Parser.ConstantAccessExpression(-100),
            expression,
        )

    def test_float(self):
        parser = Parser.Parser("100.2")
        expression = parser.try_parse_expression()
        self.assertEqual(
            Parser.ConstantAccessExpression(100.2),
            expression,
        )

    def test_float_signed(self):
        parser = Parser.Parser("-100.4")
        expression = parser.try_parse_expression()
        self.assertEqual(
            Parser.ConstantAccessExpression(-100.4),
            expression,
        )


