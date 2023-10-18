from __future__ import annotations

import typing

from pycompiler.Lexer import Token
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeExpressionNode,
    AbstractSyntaxTreeNode,
)


class NameAccessNode(AbstractSyntaxTreeExpressionNode):
    def __init__(self, name: str, token: Token = None):
        self.name = name
        self.token = token

    def get_tokens(self) -> typing.List[Token]:
        return [self.token]

    def copy(self) -> NameAccessNode:
        return NameAccessNode(self.name, self.token)

    def __repr__(self):
        return f"NAME[{self.name}]"

    def __eq__(self, other: NameAccessNode):
        return type(other) is NameAccessNode and self.name == other.name

    def can_be_assignment_target(self) -> bool:
        return True
