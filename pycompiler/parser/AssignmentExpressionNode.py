from __future__ import annotations

import typing

from pycompiler.Lexer import Token
from pycompiler.emitter.CodeBuilder import CodeBuilder
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeExpressionNode,
    AbstractSyntaxTreeNode,
    ParentAttributeSection,
)


class AssignmentExpressionNode(AbstractSyntaxTreeNode):
    def __init__(
        self,
        targets: list[AbstractSyntaxTreeExpressionNode],
        base: AbstractSyntaxTreeExpressionNode,
        equal_signs: list[Token] = None,
    ):
        super().__init__()
        self.targets = targets
        self.base = base
        self.equal_signs = equal_signs

    def replace_child_with(
        self,
        original: AbstractSyntaxTreeNode,
        new: AbstractSyntaxTreeNode,
        section: ParentAttributeSection,
    ) -> bool:
        if section == ParentAttributeSection.LHS:
            for i, node in enumerate(self.targets):
                if node is original:
                    self.targets[i] = new
                    return True

            return False

        elif section == ParentAttributeSection.BASE:
            self.base = new
            return True

        return False

    def update_child_parent_relation(self):
        for target in self.targets:
            target.parent = self
            target.parent_section = ParentAttributeSection.LHS
            target.update_child_parent_relation()

        self.base.parent = self
        self.base.parent_section = ParentAttributeSection.BASE
        self.base.update_child_parent_relation()

    def get_tokens(self) -> list[Token]:
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

    def push_code(self, builder: CodeBuilder):
        if len(self.targets) == 1:
            value = self.base.push_code(builder)
            self.targets[0].push_write_code(builder, value)
            return

        var = builder.get_temporary()
        value = self.base.push_code(builder)
        builder.push_store_local(value, var)

        for lhs in self.targets:
            lhs.push_write_code(builder, var)
