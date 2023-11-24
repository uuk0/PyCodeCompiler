from __future__ import annotations

import typing

from pycompiler.parser.NameAccessNode import (
    NameAccessModuleNode,
    NameAccessLocalNode,
    NameWriteAccessNode,
    NameWriteAccessModuleNode,
)
from pycompiler.visitors.AbstractSyntaxTreeVisitor import AbstractASTTreeVisitor


class Local2ModuleRewriter(AbstractASTTreeVisitor):
    def visit_local_name_access(self, access: NameAccessLocalNode):
        access.replace_with(NameAccessModuleNode(access.name, access.token))

    def visit_write_name_access(self, access: NameWriteAccessNode):
        access.replace_with(NameWriteAccessModuleNode(access.name, access.token))
