from unittest import TestCase

from pycompiler.parser.Parser import Parser
from pycompiler.parser.TypeStatementNode import TypeStatementNode
from pycompiler.parser.NameAccessNode import NameAccessNode
from pycompiler.parser.SubscriptionAccessExpressionNode import (
    SubscriptionAccessExpressionNode,
)
from pycompiler.parser.AttributeAccessExpressionNode import (
    AttributeAccessExpressionNode,
)


class TestAssignmentParsing(TestCase):
    def helper(self, code: str, expected: TypeStatementNode):
        parser = Parser(code)
        self.assertEqual(parser.try_parse_code_line_obj(), expected)
        parser = Parser(code)
        self.assertEqual(parser.parse_code_block(), [expected])

    def test_basic_rename(self):
        self.helper(
            "type a = b", TypeStatementNode(NameAccessNode("a"), NameAccessNode("b"))
        )

    def test_lhs_generic(self):
        self.helper(
            "type a[k] = b",
            TypeStatementNode(
                SubscriptionAccessExpressionNode(
                    NameAccessNode("a"), NameAccessNode("k")
                ),
                NameAccessNode("b"),
            ),
        )

    def test_rhs_dot(self):
        self.helper(
            "type a = b.c",
            TypeStatementNode(
                NameAccessNode("a"),
                AttributeAccessExpressionNode(NameAccessNode("b"), "c"),
            ),
        )

    def test_rhs_generic(self):
        self.helper(
            "type a = b[c]",
            TypeStatementNode(
                NameAccessNode("a"),
                SubscriptionAccessExpressionNode(
                    NameAccessNode("b"), NameAccessNode("c")
                ),
            ),
        )
