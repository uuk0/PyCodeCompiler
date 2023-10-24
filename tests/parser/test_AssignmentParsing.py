from unittest import TestCase

from pycompiler.parser.Parser import Parser
from pycompiler.parser.NameAccessNode import NameAccessNode, NameWriteAccessNode
from pycompiler.parser.AssignmentExpressionNode import AssignmentExpressionNode


class TestAssignmentParsing(TestCase):
    def test_expression(self):
        parser = Parser("test = test2")
        self.assertEqual(
            parser.try_parse_assignment(),
            AssignmentExpressionNode(
                [NameWriteAccessNode("test")], NameAccessNode("test2")
            ),
        )

    def test_code_line_expression(self):
        parser = Parser("test = test2")
        self.assertEqual(
            parser.try_parse_code_line_obj(),
            AssignmentExpressionNode(
                [NameWriteAccessNode("test")], NameAccessNode("test2")
            ),
        )

    def test_code_block_expression(self):
        parser = Parser("test = test2")
        self.assertEqual(
            parser.parse_code_block(),
            [
                AssignmentExpressionNode(
                    [NameWriteAccessNode("test")], NameAccessNode("test2")
                )
            ],
        )
