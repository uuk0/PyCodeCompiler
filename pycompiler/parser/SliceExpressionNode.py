from __future__ import annotations

import typing

from pycompiler.Lexer import Token
from pycompiler.emitter.CodeBuilder import CodeBuilder
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeNode,
    AbstractSyntaxTreeExpressionNode,
    ParentAttributeSection,
)
from pycompiler.TypeChecking import SliceWrapper


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
        self.update_result_type()

    def update_result_type(self):
        if self.start is not None:
            self.start.update_result_type()
        if self.stop is not None:
            self.stop.update_result_type()
        if self.step is not None:
            self.step.update_result_type()

        self.result_type = SliceWrapper[
            self.start.result_type if self.start else None,
            self.stop.result_type if self.stop else None,
            self.step.result_type if self.step else None,
        ]

    def replace_child_with(
        self,
        original: AbstractSyntaxTreeNode,
        new: AbstractSyntaxTreeNode,
        section: ParentAttributeSection,
    ) -> bool:
        if section == ParentAttributeSection.LHS:
            if self.start is None:
                return False

            self.start = new
            return True

        if section == ParentAttributeSection.RHS:
            if self.stop is None:
                return False

            self.stop = new
            return True

        if section == ParentAttributeSection.BASE:
            if self.step is None:
                return False

            self.step = new
            return True

        return False

    def update_child_parent_relation(self):
        if self.start:
            self.start.parent = self
            self.start.parent_section = ParentAttributeSection.LHS
            self.start.update_child_parent_relation()

        if self.stop:
            self.stop.parent = self
            self.stop.parent_section = ParentAttributeSection.RHS
            self.stop.update_child_parent_relation()

        if self.step:
            self.step.parent = self
            self.step.parent_section = ParentAttributeSection.BASE
            self.step.update_child_parent_relation()

    def get_tokens(self) -> list[Token]:
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

    def push_code(self, builder: CodeBuilder) -> CodeBuilder.Source:
        start = self.start.push_code(builder) if self.start else builder.PY_NONE
        stop = self.stop.push_code(builder) if self.stop else builder.PY_NONE
        step = self.step.push_code(builder) if self.step else builder.PY_NONE

        # todo: add real function
        return builder.push_call(None, start, stop, step)
