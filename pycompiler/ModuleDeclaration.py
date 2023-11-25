from __future__ import annotations

import typing
import inspect

from pycompiler.TypeChecking import check_signature_compatible
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeExpressionNode,
    AbstractSyntaxTreeNode,
)
from pycompiler.parser.CallExpression import CallExpression


class ModuleDeclaration:
    def __init__(self, name: str):
        self.name = name
        self.static_attributes: dict[str, AbstractSyntaxTreeExpressionNode] = {}
        self.static_methods: dict[
            str, dict[inspect.Signature, AbstractSyntaxTreeExpressionNode]
        ] = {}
        self.module_object_location: str = None

    def get_constant_on_attribute_access(
        self,
        name: str,
        context: AbstractSyntaxTreeNode = None,
    ) -> tuple[AbstractSyntaxTreeExpressionNode, AbstractSyntaxTreeNode | None] | None:
        if name in self.static_attributes:
            return self.static_attributes[name], None

        methods: dict = self.static_methods.get(name, None)
        if methods is None:
            return

        if isinstance(context, CallExpression):
            signature = context.get_signature()

            if signature in methods:
                return methods[signature], None

            for sig, method in methods.items():
                if check_signature_compatible(sig, signature):
                    return method, None

    def get_constant_on_subscription_access(
        self,
        expr: AbstractSyntaxTreeExpressionNode,
        context: AbstractSyntaxTreeNode = None,
    ) -> tuple[AbstractSyntaxTreeExpressionNode, AbstractSyntaxTreeNode | None] | None:
        pass
