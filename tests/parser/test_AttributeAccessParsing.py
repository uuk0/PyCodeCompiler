from unittest import TestCase

from pycompiler.parser.Parser import Parser
from pycompiler.parser.NameAccessNode import NameAccessNode
from pycompiler.parser.AttributeAccessExpressionNode import (
    AttributeAccessExpressionNode,
)


class TestAssignmentParsing(TestCase):
    def test_expression(self):
        parser = Parser("test.test2")
        self.assertEqual(
            parser.try_parse_expression(),
            AttributeAccessExpressionNode(NameAccessNode("test"), "test2"),
        )

    def test_target_expression(self):
        parser = Parser("test.test2")
        self.assertEqual(
            parser.try_parse_assignment_target(),
            AttributeAccessExpressionNode(NameAccessNode("test"), "test2"),
        )

    def test_code_line_expression(self):
        parser = Parser("test.test2")
        self.assertEqual(
            parser.try_parse_code_line_obj(),
            AttributeAccessExpressionNode(NameAccessNode("test"), "test2"),
        )

    def test_code_block_expression(self):
        parser = Parser("test.test2")
        self.assertEqual(
            parser.parse_code_block(),
            [AttributeAccessExpressionNode(NameAccessNode("test"), "test2")],
        )
