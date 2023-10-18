from __future__ import annotations

import typing

from pycompiler.Lexer import Token
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeExpressionNode,
)


class SliceExpressionNode(AbstractSyntaxTreeExpressionNode):
    def __init__(
        self,
        start: AbstractSyntaxTreeExpressionNode | None,
        stop: AbstractSyntaxTreeExpressionNode | None,
        step: AbstractSyntaxTreeExpressionNode | None,
        lhs_colon_token: Token | None = None,
        rhs_colon_token: Token | None = None,
    ):
        super().__init__()
        self.start = start
        self.stop = stop
        self.step = step
        self.lhs_colon_token = lhs_colon_token
        self.rhs_colon_token = rhs_colon_token

    def get_tokens(self) -> typing.List[Token]:
        return (
            (self.start.get_tokens() if self.start else [])
            + (self.stop.get_tokens() if self.stop else [])
            + (self.step.get_tokens() if self.step else [])
        )

    def __repr__(self):
        return f"SLICE({self.start or ''}:{self.stop or ''}:{self.step or ''})"

    def __eq__(self, other: SliceExpressionNode):
        return (
            type(other) is SliceExpressionNode
            and self.start == other.start
            and self.stop == other.stop
            and self.step == other.step
        )

    def copy(self) -> SliceExpressionNode:
        return SliceExpressionNode(
            self.start.copy() if self.start else None,
            self.stop.copy() if self.start else None,
            self.step.copy() if self.start else None,
            self.lhs_colon_token,
            self.rhs_colon_token,
        )
