from __future__ import annotations

import typing

from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeNode,
    AbstractSyntaxTreeExpressionNode,
)
from pycompiler.parser.ScopeReferences import ParentScopeReference
from pycompiler.ModuleDeclaration import ModuleDeclaration
from pycompiler.parser.ConstantValueExpressionNode import ConstantValueExpressionNode


class Scope:
    # builtin functions
    BASE_SCOPE_VALUES: dict[str, AbstractSyntaxTreeExpressionNode] = {
        "None": ConstantValueExpressionNode(None),
        "True": ConstantValueExpressionNode(True),
        "False": ConstantValueExpressionNode(False),
    }

    # any modules
    GLOBAL_MODULES: dict[str, ModuleDeclaration] = {}

    # for the compiler: what modules where discovered and need to be loaded
    PENDING_MODULE_LOOKUPS: set[str] = set()

    def __init__(self, parent: Scope = None, scope_across_boundaries=False):
        self.parent = parent
        self.scope_across_boundaries = scope_across_boundaries
        self.variable_name_references: dict[str, AbstractSyntaxTreeExpressionNode] = {}
        self.expose_names_to_children: set[str] = set()
        self.expected_static_locals: set[str] = set()

    def create_child(self, scope_across_boundaries=False):
        return Scope(self, scope_across_boundaries=scope_across_boundaries)

    def get_access_node_to_name(self, name: str) -> AbstractSyntaxTreeExpressionNode:
        if name in self.variable_name_references:
            return self.variable_name_references[name]

        if self.scope_across_boundaries:
            self.parent.expose_names_to_children.add(name)
            return ParentScopeReference(name)

        if self.parent is None:
            if name in self.BASE_SCOPE_VALUES:
                return self.BASE_SCOPE_VALUES[name]

            raise NameError("name not arrival; not found at root!")

        return self.parent.get_access_node_to_name(name)

    def export_name_access(self, name: str, access: AbstractSyntaxTreeExpressionNode):
        self.variable_name_references[name] = access
        return self
