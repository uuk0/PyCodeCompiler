from unittest import TestCase

from pycompiler.parser.Parser import Parser
from pycompiler.parser.NameAccessNode import NameAccessNode
from pycompiler.parser.SubscriptionAccessExpressionNode import (
    SubscriptionAccessExpressionNode,
)
from pycompiler.parser.SliceExpressionNode import SliceExpressionNode


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

    def test_code_block_expression(self):
        parser = Parser("test[test2]")
        self.assertEqual(
            parser.parse_code_block(),
            [
                SubscriptionAccessExpressionNode(
                    NameAccessNode("test"), NameAccessNode("test2")
                )
            ],
        )

    def test_slice_expression_single_colon(self):
        parser = Parser("test[test2:]")
        self.assertEqual(
            parser.try_parse_expression(),
            SubscriptionAccessExpressionNode(
                NameAccessNode("test"),
                SliceExpressionNode(NameAccessNode("test2"), None, None),
            ),
        )

    def test_slice_expression_single_colon_after(self):
        parser = Parser("test[:test2]")
        self.assertEqual(
            parser.try_parse_expression(),
            SubscriptionAccessExpressionNode(
                NameAccessNode("test"),
                SliceExpressionNode(None, NameAccessNode("test2"), None),
            ),
        )

    def test_slice_expression_single_colon_twice(self):
        parser = Parser("test[test1:test2]")
        self.assertEqual(
            parser.try_parse_expression(),
            SubscriptionAccessExpressionNode(
                NameAccessNode("test"),
                SliceExpressionNode(
                    NameAccessNode("test1"), NameAccessNode("test2"), None
                ),
            ),
        )

    def test_slice_expression_double_colon_0(self):
        parser = Parser("test[test2::]")
        self.assertEqual(
            parser.try_parse_expression(),
            SubscriptionAccessExpressionNode(
                NameAccessNode("test"),
                SliceExpressionNode(NameAccessNode("test2"), None, None),
            ),
        )

    def test_slice_expression_double_colon_1(self):
        parser = Parser("test[:test2:]")
        self.assertEqual(
            parser.try_parse_expression(),
            SubscriptionAccessExpressionNode(
                NameAccessNode("test"),
                SliceExpressionNode(None, NameAccessNode("test2"), None),
            ),
        )

    def test_slice_expression_double_colon_2(self):
        parser = Parser("test[::test2]")
        self.assertEqual(
            parser.try_parse_expression(),
            SubscriptionAccessExpressionNode(
                NameAccessNode("test"),
                SliceExpressionNode(None, None, NameAccessNode("test2")),
            ),
        )

    def test_slice_expression_double_colon_01(self):
        parser = Parser("test[test1:test2:]")
        self.assertEqual(
            parser.try_parse_expression(),
            SubscriptionAccessExpressionNode(
                NameAccessNode("test"),
                SliceExpressionNode(
                    NameAccessNode("test1"), NameAccessNode("test2"), None
                ),
            ),
        )

    def test_slice_expression_double_colon_02(self):
        parser = Parser("test[test1::test2]")
        self.assertEqual(
            parser.try_parse_expression(),
            SubscriptionAccessExpressionNode(
                NameAccessNode("test"),
                SliceExpressionNode(
                    NameAccessNode("test1"), None, NameAccessNode("test2")
                ),
            ),
        )

    def test_slice_expression_double_colon_12(self):
        parser = Parser("test[:test1:test2]")
        self.assertEqual(
            parser.try_parse_expression(),
            SubscriptionAccessExpressionNode(
                NameAccessNode("test"),
                SliceExpressionNode(
                    None, NameAccessNode("test1"), NameAccessNode("test2")
                ),
            ),
        )

    def test_slice_expression_double_colon_012(self):
        parser = Parser("test[test1:test2:test3]")
        self.assertEqual(
            parser.try_parse_expression(),
            SubscriptionAccessExpressionNode(
                NameAccessNode("test"),
                SliceExpressionNode(
                    NameAccessNode("test1"),
                    NameAccessNode("test2"),
                    NameAccessNode("test3"),
                ),
            ),
        )
