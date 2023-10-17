from __future__ import annotations

import typing

from pycompiler.Lexer import Token
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeExpressionNode,
    AbstractSyntaxTreeNode,
)


class AssignmentExpressionNode(AbstractSyntaxTreeNode):
    def __init__(
        self,
        targets: typing.List[AbstractSyntaxTreeExpressionNode],
        base: AbstractSyntaxTreeExpressionNode,
        equal_signs: typing.List[Token] = None,
    ):
        self.targets = targets
        self.base = base
        self.equal_signs = equal_signs

    def get_tokens(self) -> typing.List[Token]:
        return (
            sum((target.get_tokens() for target in self.targets), [])
            + self.equal_signs
            + self.base.get_tokens()
        )

    def __repr__(self):
        return f"ASSIGNMENT({' = '.join(repr(x) for x in self.targets)} = {repr(self.base)})"

    def __eq__(self, other: AssignmentExpressionNode):
        return (
            type(other) is AssignmentExpressionNode
            and self.targets == other.targets
            and self.base == other.base
        )

    def copy(self) -> AssignmentExpressionNode:
        return AssignmentExpressionNode(
            [target.copy() for target in self.targets],
            self.base.copy(),
            self.equal_signs.copy(),
        )

    def can_be_assignment_target(self) -> bool:
        return True
