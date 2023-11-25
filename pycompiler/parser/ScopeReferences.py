from __future__ import annotations

import typing

from pycompiler.Lexer import Token
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeExpressionNode,
)


class ParentScopeReference(AbstractSyntaxTreeExpressionNode):
    def __init__(self, name: str, token: Token = None):
        super().__init__()
        self.name = name
        self.token = token

    def get_tokens(self) -> list[Token]:
        return [self.token]

    def copy(self) -> ParentScopeReference:
        return ParentScopeReference(self.name, self.token)

    def __repr__(self):
        return f"PARENT-NAME[{self.name}]"

    def __eq__(self, other: ParentScopeReference):
        return type(other) is ParentScopeReference and self.name == other.name

    def can_be_assignment_target(self) -> bool:
        return True


class ChildScopeExported(AbstractSyntaxTreeExpressionNode):
    def __init__(self, name: str, token: Token = None):
        super().__init__()
        self.name = name
        self.token = token

    def get_tokens(self) -> list[Token]:
        return [self.token]

    def copy(self) -> ParentScopeReference:
        return ParentScopeReference(self.name, self.token)

    def __repr__(self):
        return f"NAME-CHILD_EXPOSED[{self.name}]"

    def __eq__(self, other: ParentScopeReference):
        return type(other) is ParentScopeReference and self.name == other.name

    def can_be_assignment_target(self) -> bool:
        return True
