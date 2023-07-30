from unittest import TestCase
import pycompiler.Parser
import pycompiler.Lexer


class TestCommentParser(TestCase):
    def test_simple(self):
        parser = pycompiler.Parser.Parser("# test comment")
        tree = parser.parse()
        self.assertEqual(
            [pycompiler.Parser.PyCommentNode(pycompiler.Lexer.TokenType.HASHTAG("#"), pycompiler.Lexer.TokenType.REMAINING_STRING(" test comment"))],
            tree,
        )

