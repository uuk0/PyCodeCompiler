from unittest import TestCase

from pycompiler.parser.Parser import Parser
from pycompiler.parser.NameAccessNode import NameAccessNode
from pycompiler.parser.AssignmentExpressionNode import AssignmentExpressionNode


class TestAssignmentParsing(TestCase):
    def test_expression(self):
        parser = Parser("test = test2")
        self.assertEqual(
            parser.try_parse_assignment(),
            AssignmentExpressionNode([NameAccessNode("test")], NameAccessNode("test2")),
        )

    def test_code_line_expression(self):
        parser = Parser("test = test2")
        self.assertEqual(
            parser.try_parse_code_line_obj(),
            AssignmentExpressionNode([NameAccessNode("test")], NameAccessNode("test2")),
        )
