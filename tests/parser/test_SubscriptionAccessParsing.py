from unittest import TestCase

from pycompiler.parser.Parser import Parser
from pycompiler.parser.NameAccessNode import NameAccessNode
from pycompiler.parser.SubscriptionAccessExpressionNode import (
    SubscriptionAccessExpressionNode,
)


class TestAssignmentParsing(TestCase):
    def test_expression(self):
        parser = Parser("test[test2]")
        self.assertEqual(
            parser.try_parse_expression(),
            SubscriptionAccessExpressionNode(
                NameAccessNode("test"), NameAccessNode("test2")
            ),
        )

    def test_target_expression(self):
        parser = Parser("test[test2]")
        self.assertEqual(
            parser.try_parse_assignment_target(),
            SubscriptionAccessExpressionNode(
                NameAccessNode("test"), NameAccessNode("test2")
            ),
        )

    def test_code_line_expression(self):
        parser = Parser("test[test2]")
        self.assertEqual(
            parser.try_parse_code_line_obj(),
            SubscriptionAccessExpressionNode(
                NameAccessNode("test"), NameAccessNode("test2")
            ),
        )
