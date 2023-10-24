from __future__ import annotations

import enum
import typing
from abc import ABC
from pycompiler.Lexer import Token


class ParentAttributeSection(enum.Enum):
    LHS = enum.auto()
    RHS = enum.auto()
    BASE = enum.auto()
    PARAMETER = enum.auto()
    DEFAULT = enum.auto()
    BODY = enum.auto()
    CONDITION = enum.auto()
    ELSE_BLOCK = enum.auto()


class AbstractSyntaxTreeNode(ABC):
    def __init__(self):
        self.scope = None
        self.parent: AbstractSyntaxTreeNode | None = None
        self.parent_section: ParentAttributeSection | None = None

    def replace_with(self, node: AbstractSyntaxTreeNode) -> bool:
        assert self.parent is not None
        status = self.parent.replace_child_with(self, node, self.parent_section)

        if status:
            self.parent.update_child_parent_relation()
            self.parent = None
            self.parent_section = None

        return status

    def replace_child_with(
        self,
        original: AbstractSyntaxTreeNode,
        new: AbstractSyntaxTreeNode,
        section: ParentAttributeSection,
    ) -> bool:
        raise NotImplementedError

    def update_child_parent_relation(self):
        raise NotImplementedError

    def get_tokens(self) -> typing.List[Token]:
        return []

    def __repr__(self):
        raise NotImplementedError

    def __eq__(self, other: AbstractSyntaxTreeNode):
        raise NotImplementedError

    def copy(self) -> AbstractSyntaxTreeNode:
        raise NotImplementedError

    def can_be_assignment_target(self) -> bool:
        return False


class AbstractSyntaxTreeExpressionNode(AbstractSyntaxTreeNode, ABC):
    def __init__(self):
        super().__init__()
        self.result_type = None

    def copy(self) -> AbstractSyntaxTreeExpressionNode:
        raise NotImplementedError
