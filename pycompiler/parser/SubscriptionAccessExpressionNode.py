from __future__ import annotations

import typing

from pycompiler.Lexer import Token
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeExpressionNode,
)


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

    def get_tokens(self) -> typing.List[Token]:
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
