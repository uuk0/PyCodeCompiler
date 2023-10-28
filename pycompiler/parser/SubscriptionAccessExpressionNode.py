from __future__ import annotations

import typing

from pycompiler.Lexer import Token
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeNode,
    AbstractSyntaxTreeExpressionNode,
    ParentAttributeSection,
)
from pycompiler.TypeChecking import get_type_info


class SubscriptionAccessExpressionNode(AbstractSyntaxTreeExpressionNode):
    def __init__(
        self,
        base: AbstractSyntaxTreeExpressionNode,
        inner: AbstractSyntaxTreeExpressionNode,
        lhs_bracket: Token = None,
        rhs_bracket: Token = None,
    ):
        super().__init__()
        self.rhs_bracket = rhs_bracket
        self.lhs_bracket = lhs_bracket
        self.inner = inner
        self.base = base

    def update_result_type(self):
        self.base.update_result_type()
        t = self.base.get_data_type()
        info = get_type_info(t)
        self.result_type = info.get_subscription_type(self.inner)

    def replace_child_with(
        self,
        original: AbstractSyntaxTreeNode,
        new: AbstractSyntaxTreeNode,
        section: ParentAttributeSection,
    ) -> bool:
        if section == ParentAttributeSection.BASE:
            self.base = new
            return True

        if section == ParentAttributeSection.RHS:
            self.inner = new
            return True

        return False

    def update_child_parent_relation(self):
        self.base.parent = self
        self.base.parent_section = ParentAttributeSection.BASE
        self.base.update_child_parent_relation()

        self.inner.parent = self
        self.inner.parent_section = ParentAttributeSection.RHS
        self.inner.update_child_parent_relation()

    def get_tokens(self) -> list[Token]:
        return (
            self.base.get_tokens()
            + [self.lhs_bracket]
            + self.inner.get_tokens()
            + [self.rhs_bracket]
        )

    def __repr__(self):
        return f"SUBSCRIPTION({self.base}[{self.inner}])"

    def __eq__(self, other: SubscriptionAccessExpressionNode):
        return (
            type(other) is SubscriptionAccessExpressionNode
            and self.base == other.base
            and self.inner == other.inner
        )

    def copy(self) -> SubscriptionAccessExpressionNode:
        return SubscriptionAccessExpressionNode(
            self.base.copy(),
            self.inner.copy(),
            self.lhs_bracket,
            self.rhs_bracket,
        )

    def can_be_assignment_target(self) -> bool:
        return True

    def as_data_type(self):
        base = self.base.as_data_type()
        args = self.inner.as_data_type()
        return (
            base[args]
            if base != NotImplemented and args != NotImplemented
            else NotImplemented
        )
