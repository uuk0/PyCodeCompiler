from unittest import TestCase

from pycompiler.parser.Parser import Parser
from pycompiler.parser.NameAccessNode import NameAccessNode
from pycompiler.parser.WhileStatementNode import WhileStatementNode
from pycompiler.parser.util import ArgType


class TestWhileStatement(TestCase):
    def helper(self, code: str, expected: WhileStatementNode):
        parser = Parser(code)
        self.assertEqual(parser.try_parse_code_line_obj(), expected)
        parser = Parser(code)
        self.assertEqual(parser.parse_code_block(), [expected])

    def test_basic(self):
        self.helper(
            "while test: test",
            WhileStatementNode(NameAccessNode("test"), [NameAccessNode("test")]),
        )

    def test_basic_break_block(self):
        self.helper(
            "while test:\n    test",
            WhileStatementNode(NameAccessNode("test"), [NameAccessNode("test")]),
        )
