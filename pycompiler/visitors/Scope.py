from __future__ import annotations

import typing

from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeNode,
    AbstractSyntaxTreeExpressionNode,
)
from pycompiler.parser.ScopeReferences import ParentScopeReference


class Scope:
    def __init__(self, parent: Scope = None, scope_across_boundaries=False):
        self.parent = parent
        self.scope_across_boundaries = scope_across_boundaries
        self.variable_name_references: typing.Dict[
            str, AbstractSyntaxTreeExpressionNode
        ] = {}
        self.expose_names_to_children: typing.Set[str] = set()

    def create_child(self, scope_across_boundaries=False):
        return Scope(self, scope_across_boundaries=scope_across_boundaries)

    def get_access_node_to_name(self, name: str) -> AbstractSyntaxTreeExpressionNode:
        if name in self.variable_name_references:
            return self.variable_name_references[name]

        if self.scope_across_boundaries:
            self.parent.expose_names_to_children.add(name)
            return ParentScopeReference(name)

        if self.parent is None:
            raise NameError("name not arrival; not found at root!")

        return self.parent.get_access_node_to_name(name)

    def export_name_access(self, name: str, access: AbstractSyntaxTreeExpressionNode):
        self.variable_name_references[name] = access
        return self
