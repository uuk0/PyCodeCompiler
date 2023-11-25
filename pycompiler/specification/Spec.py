from __future__ import annotations

from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeNode,
    AbstractSyntaxTreeExpressionNode,
)
from pycompiler.visitors.Scope import Scope

from pycompiler.ModuleDeclaration import ModuleDeclaration


class SpecifiedModule(ModuleDeclaration):
    pass


class SpecifiedClass(AbstractSyntaxTreeNode):
    def __init__(self, name: str, parent: SpecifiedClass | SpecifiedModule = None):
        super().__init__()

        self.name = name
        self.parent = parent

    def define_static_attribute(
        self, name: str, value: AbstractSyntaxTreeExpressionNode
    ):
        pass

    def finish(self):
        Scope.BASE_SCOPE_VALUES[self.name]


class SpecifiedFunction(AbstractSyntaxTreeNode):
    pass
