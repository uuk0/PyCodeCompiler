from __future__ import annotations

from pycompiler.parser.NameAccessNode import NameAccessNode, NameWriteAccessNode
from pycompiler.visitors.AbstractSyntaxTreeVisitor import AbstractASTTreeVisitor
from pycompiler import options


class NameResolver(AbstractASTTreeVisitor):
    def visit_name_access(self, access: NameAccessNode):
        if not access.replace_with(
            access.scope.get_access_node_to_name(access.name).copy()
        ):
            raise RuntimeError(f"failed to replace parent of {access}: {access.parent}")

    def visit_write_name_access(self, access: NameWriteAccessNode):
        if (
            not options.ENABLE_BUILTIN_SHADOWING
            and access.name in access.scope.BASE_SCOPE_VALUES
        ):
            raise NameError(f"Name {access.name} shadows outer builtin!")
