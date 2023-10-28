from __future__ import annotations

import typing

from pycompiler.Lexer import Token
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeExpressionNode,
    AbstractSyntaxTreeNode,
)


class NameAccessNode(AbstractSyntaxTreeExpressionNode):
    def __init__(self, name: str, token: Token = None):
        super().__init__()
        self.name = name
        self.token = token

    def get_tokens(self) -> list[Token]:
        return [self.token]

    def copy(self) -> NameAccessNode:
        return NameAccessNode(self.name, self.token)

    def __repr__(self):
        return f"NAME[{self.name}]"

    def __eq__(self, other: NameAccessNode):
        return type(other) is NameAccessNode and self.name == other.name


class NameWriteAccessNode(AbstractSyntaxTreeExpressionNode):
    def __init__(self, name: str, token: Token = None):
        super().__init__()
        self.name = name
        self.token = token

    def update_result_type(self):
        pass  # todo: validate type compatibility with scope type!

    def get_tokens(self) -> list[Token]:
        return [self.token]

    def copy(self) -> NameWriteAccessNode:
        return NameWriteAccessNode(self.name, self.token)

    def __repr__(self):
        return f"NAME_W[{self.name}]"

    def __eq__(self, other: NameWriteAccessNode):
        return type(other) is NameWriteAccessNode and self.name == other.name

    def can_be_assignment_target(self) -> bool:
        return True


class NameAccessLocalNode(AbstractSyntaxTreeExpressionNode):
    def __init__(self, name: str, token: Token = None):
        super().__init__()
        self.name = name
        self.token = token

    def update_result_type(self):
        pass  # todo: poll type from scope

    def get_tokens(self) -> list[Token]:
        return [self.token]

    def copy(self) -> NameAccessLocalNode:
        return NameAccessLocalNode(self.name, self.token)

    def __repr__(self):
        return f"NAME-LOCAL[{self.name}]"

    def __eq__(self, other: NameAccessLocalNode):
        return type(other) is NameAccessLocalNode and self.name == other.name
