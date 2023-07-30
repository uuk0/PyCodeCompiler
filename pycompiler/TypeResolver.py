from __future__ import annotations

import typing

from pycompiler.Parser import SyntaxTreeVisitor, Scope


if typing.TYPE_CHECKING:
    from pycompiler.Parser import ClassDefinitionNode, FunctionDefinitionNode


class ScopeGeneratorVisitor(SyntaxTreeVisitor):
    def __init__(self, scope: Scope):
        self.scope: Scope = scope

    def visit_class_definition(self, node: ClassDefinitionNode):
        outer_scope = self.scope
        outer_scope.expose_type_name(node.name, node)
        self.scope = self.scope.copy()
        self.scope.class_name_stack.append(node.name)
        super().visit_class_definition(node)
        self.scope = outer_scope
        # todo: generics

    def visit_function_definition(self, node: FunctionDefinitionNode):
        super().visit_function_definition(node)
        # todo: generics

