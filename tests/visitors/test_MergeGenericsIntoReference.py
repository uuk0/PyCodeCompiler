from __future__ import annotations

import unittest

from pycompiler.parser.ClassDefinitionStatementNode import (
    ClassDefinitionNode,
    StaticClassReferenceNodeWithGeneric,
    StaticClassReferenceNode,
)
from pycompiler.parser.SubscriptionAccessExpressionNode import (
    SubscriptionAccessExpressionNode,
)
from pycompiler.parser.NameAccessNode import NameAccessNode
from pycompiler.parser.AttributeAccessExpressionNode import (
    AttributeAccessExpressionNode,
)

from pycompiler.visitors.MergeGenericsIntoReference import (
    MergeGenericsIntoReferenceVisitor,
)


SINGLE_GENERIC_CLASS = ClassDefinitionNode("single_generic", ["T"], [], [])


class TestClasses(unittest.TestCase):
    def test_basic(self):
        expr = AttributeAccessExpressionNode(
            SubscriptionAccessExpressionNode(
                StaticClassReferenceNode(SINGLE_GENERIC_CLASS), NameAccessNode("U")
            ),
            "test",
        )
        expr.update_child_parent_relation()

        MergeGenericsIntoReferenceVisitor().visit_any(expr)

        self.assertIsInstance(expr.base, StaticClassReferenceNodeWithGeneric)
        self.assertEqual(expr.base.generic_annotations, [NameAccessNode("U")])

    def test_error_on_double_access(self):
        expr = AttributeAccessExpressionNode(
            SubscriptionAccessExpressionNode(
                SubscriptionAccessExpressionNode(
                    StaticClassReferenceNode(SINGLE_GENERIC_CLASS), NameAccessNode("U")
                ),
                NameAccessNode("X"),
            ),
            "test",
        )
        expr.update_child_parent_relation()
        self.assertRaises(
            SyntaxError, lambda: MergeGenericsIntoReferenceVisitor().visit_any(expr)
        )
