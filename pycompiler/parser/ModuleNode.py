from __future__ import annotations

import typing

from pycompiler.Lexer import Token
from pycompiler.emitter.CodeBuilder import CodeBuilder
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeNode,
    ParentAttributeSection,
)


class ModuleNode(AbstractSyntaxTreeNode):
    def __init__(self, nodes: typing.List[AbstractSyntaxTreeNode]):
        super().__init__()
        self.nodes = nodes

    def replace_child_with(
        self,
        original: AbstractSyntaxTreeNode,
        new: AbstractSyntaxTreeNode,
        section: ParentAttributeSection,
    ) -> bool:
        if section != ParentAttributeSection.BODY:
            return False

        for i, node in enumerate(self.nodes):
            if node is original:
                self.nodes[i] = new
                return True

        return False

    def update_child_parent_relation(self):
        for node in self.nodes:
            node.parent = self
            node.parent_section = ParentAttributeSection.BODY

    def get_tokens(self) -> list[Token]:
        return sum((node.get_tokens() for node in self.nodes), [])

    def __repr__(self):
        return f"MODULE({repr(self.nodes)[1:-1]})"

    def __eq__(self, other: ModuleNode):
        return type(other) is ModuleNode and self.nodes == other.nodes

    def copy(self) -> AbstractSyntaxTreeNode:
        return ModuleNode([node.copy() for node in self.nodes])
