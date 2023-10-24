from __future__ import annotations

from pycompiler.parser.NameAccessNode import NameAccessNode
from pycompiler.visitors.AbstractSyntaxTreeVisitor import AbstractASTTreeVisitor


class NameResolver(AbstractASTTreeVisitor):
    def visit_name_access(self, access: NameAccessNode):
        access.replace_with(access.scope.get_access_node_to_name(access.name))
