from __future__ import annotations

import typing

from pycompiler.Lexer import Token
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeNode,
    AbstractSyntaxTreeExpressionNode,
    ParentAttributeSection,
)


class AttributeAccessExpressionNode(AbstractSyntaxTreeExpressionNode):
    def __init__(
        self,
        base: AbstractSyntaxTreeExpressionNode,
        name: str,
        dot_token: Token = None,
        name_token: Token = None,
    ):
        super().__init__()
        self.base = base
        self.name = name
        self.dot_token = dot_token
        self.name_token = name_token

    def replace_child_with(
        self,
        original: AbstractSyntaxTreeNode,
        new: AbstractSyntaxTreeNode,
        section: ParentAttributeSection,
    ) -> bool:
        if section != ParentAttributeSection.BASE:
            return False

        self.base = new
        return True

    def update_child_parent_relation(self):
        self.base.parent = self
        self.base.parent_section = ParentAttributeSection.BASE
        self.base.update_child_parent_relation()

    def get_tokens(self) -> list[Token]:
        return self.base.get_tokens() + [self.dot_token, self.name_token]

    def __repr__(self):
        return f"ATTRIBUTE({repr(self.base)} . {self.name})"

    def __eq__(self, other: AttributeAccessExpressionNode):
        return (
            type(other) is AttributeAccessExpressionNode
            and self.base == other.base
            and self.name == other.name
        )

    def copy(self) -> AttributeAccessExpressionNode:
        return AttributeAccessExpressionNode(
            self.base.copy(),
            self.name,
            self.dot_token,
            self.name_token,
        )

    def can_be_assignment_target(self) -> bool:
        return True
