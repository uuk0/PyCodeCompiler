from __future__ import annotations

import typing

from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeExpressionNode,
    ParentAttributeSection,
)
from pycompiler.TypeChecking import merge_type_declarations


class ListConstructorNode(AbstractSyntaxTreeExpressionNode):
    def __init__(self, items: typing.List[AbstractSyntaxTreeExpressionNode]):
        super().__init__()
        self.items = items
        self.result_type = list

    def update_result_type(self):
        for e in self.items:
            e.update_result_type()
        entry_types = [e.result_type for e in self.items]
        if not entry_types:
            self.result_type = list
        elif len(entry_types) == 1:
            self.result_type = list[entry_types[0]]
        else:
            t = merge_type_declarations(entry_types[0], entry_types[1])
            for e in entry_types[2:]:
                t = merge_type_declarations(t, e)
            self.result_type = list[t]

    def replace_child_with(
        self,
        original: AbstractSyntaxTreeExpressionNode,
        new: AbstractSyntaxTreeExpressionNode,
        section: ParentAttributeSection,
    ) -> bool:
        if section != ParentAttributeSection.RHS:
            return False

        for i, item in enumerate(self.items):
            if item is original:
                self.items[i] = new
                return True

        return False

    def update_child_parent_relation(self):
        for item in self.items:
            item.parent = self
            item.parent_section = ParentAttributeSection.RHS
            item.update_child_parent_relation()

    def __repr__(self):
        return repr(self.items)

    def __eq__(self, other: ListConstructorNode):
        return type(other) is ListConstructorNode and self.items == other.items

    def copy(self) -> ListConstructorNode:
        return ListConstructorNode([e.copy() for e in self.items])


class ListComprehensionNode(AbstractSyntaxTreeExpressionNode):
    def __init__(
        self,
        base_expr: AbstractSyntaxTreeExpressionNode,
        assignment_target: AbstractSyntaxTreeExpressionNode,
        source_expr: AbstractSyntaxTreeExpressionNode,
        if_cond: AbstractSyntaxTreeExpressionNode = None,
    ):
        super().__init__()
        self.base_expr = base_expr
        self.assignment_target = assignment_target
        self.source_expr = source_expr
        self.if_cond = if_cond
        self.result_type = list[self.base_expr.result_type]

    def update_result_type(self):
        self.base_expr.update_result_type()
        self.result_type = list[self.base_expr.result_type]

    def replace_child_with(
        self,
        original: AbstractSyntaxTreeExpressionNode,
        new: AbstractSyntaxTreeExpressionNode,
        section: ParentAttributeSection,
    ) -> bool:
        if section == ParentAttributeSection.BODY:
            self.base_expr = new
            return True

        elif section == ParentAttributeSection.BASE:
            self.assignment_target = new
            return True

        elif section == ParentAttributeSection.RHS:
            self.assignment_target = new
            return True

        elif section == ParentAttributeSection.CONDITION and self.if_cond is not None:
            self.if_cond = new
            return True

        return False

    def update_child_parent_relation(self):
        self.base_expr.parent = self
        self.base_expr.parent_section = ParentAttributeSection.BODY
        self.base_expr.update_child_parent_relation()

        self.assignment_target.parent = self
        self.assignment_target.parent_section = ParentAttributeSection.BASE
        self.assignment_target.update_child_parent_relation()

        self.source_expr.parent = self
        self.source_expr.parent_section = ParentAttributeSection.RHS
        self.source_expr.update_child_parent_relation()

        if self.if_cond is not None:
            self.if_cond.parent = self
            self.if_cond.parent_section = ParentAttributeSection.CONDITION
            self.if_cond.update_child_parent_relation()

    def __repr__(self):
        return (
            f"[{self.base_expr} for {self.assignment_target} in {self.source_expr}"
            f"{'' if self.if_cond is None else f' if {self.if_cond}'}]"
        )

    def __eq__(self, other: ListComprehensionNode):
        return (
            type(other) is ListComprehensionNode
            and self.base_expr == other.base_expr
            and self.assignment_target == other.assignment_target
            and self.source_expr == other.source_expr
            and self.if_cond == other.if_cond
        )

    def copy(self) -> ListComprehensionNode:
        return ListComprehensionNode(
            self.base_expr.copy(),
            self.assignment_target.copy(),
            self.source_expr.copy(),
            self.if_cond.copy() if self.if_cond else None,
        )
