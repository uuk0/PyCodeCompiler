from __future__ import annotations

import typing
import unittest

from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeExpressionNode,
    AbstractSyntaxTreeNode,
)
from pycompiler.parser.OperatorExpressionNode import (
    BinaryOperator,
    SingletonOperator,
    BinaryInplaceOperator,
    OperatorType,
)
from pycompiler.parser.NameAccessNode import NameAccessNode
from pycompiler.parser.AttributeAccessExpressionNode import (
    AttributeAccessExpressionNode,
)
from pycompiler.visitors.OperatorPrioritiesRewriter import OperatorPrioritiesRewriter
from pycompiler.visitors.Scope import Scope
from pycompiler.visitors.ScopeAssigner import ScopeAssigner


class TestOperatorRewriter(unittest.TestCase):
    def apply(
        self, node: AbstractSyntaxTreeExpressionNode
    ) -> AbstractSyntaxTreeExpressionNode:
        base = AttributeAccessExpressionNode(node, "test")
        base.update_child_parent_relation()
        scope = Scope()
        ScopeAssigner(scope).visit_any(base)
        OperatorPrioritiesRewriter().visit_any(base)
        return base.base

    def test_basic(self):
        node = BinaryOperator(
            OperatorType.BINARY_STAR,
            NameAccessNode("lhs"),
            BinaryOperator(
                OperatorType.BINARY_PLUS,
                NameAccessNode("rhs0"),
                NameAccessNode("rhs1"),
            ),
        )
        self.assertEqual(
            BinaryOperator(
                OperatorType.BINARY_PLUS,
                BinaryOperator(
                    OperatorType.BINARY_STAR,
                    NameAccessNode("lhs"),
                    NameAccessNode("rhs0"),
                ),
                NameAccessNode("rhs1"),
            ),
            self.apply(node),
        )

    def test_basic_2(self):
        node = BinaryOperator(
            OperatorType.BINARY_STAR_STAR,
            NameAccessNode("lhs"),
            BinaryOperator(
                OperatorType.BINARY_PLUS,
                NameAccessNode("rhs0"),
                NameAccessNode("rhs1"),
            ),
        )
        self.assertEqual(
            BinaryOperator(
                OperatorType.BINARY_PLUS,
                BinaryOperator(
                    OperatorType.BINARY_STAR_STAR,
                    NameAccessNode("lhs"),
                    NameAccessNode("rhs0"),
                ),
                NameAccessNode("rhs1"),
            ),
            self.apply(node),
        )

    def test_basic_3(self):
        node = SingletonOperator(
            OperatorType.SINGLE_MINUS,
            BinaryOperator(
                OperatorType.BINARY_PLUS, NameAccessNode("lhs"), NameAccessNode("rhs")
            ),
        )
        self.assertEqual(
            BinaryOperator(
                OperatorType.BINARY_PLUS,
                SingletonOperator(
                    OperatorType.SINGLE_MINUS,
                    NameAccessNode("lhs"),
                ),
                NameAccessNode("rhs"),
            ),
            self.apply(node),
        )
