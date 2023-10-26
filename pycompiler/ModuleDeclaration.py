from __future__ import annotations

import typing
import inspect

from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeExpressionNode,
    AbstractSyntaxTreeNode,
)
from pycompiler.parser.CallExpression import CallExpression


class ModuleDeclaration:
    def __init__(self, name: str):
        self.name = name
        self.static_attributes: typing.Dict[str, AbstractSyntaxTreeExpressionNode] = {}
        self.static_methods: typing.Dict[
            str, typing.Dict[inspect.Signature, AbstractSyntaxTreeExpressionNode]
        ] = {}
        self.module_object_location: str = None

    def get_constant_on_attribute_access(
        self,
        name: str,
        context: AbstractSyntaxTreeNode = None,
    ) -> (
        typing.Tuple[AbstractSyntaxTreeExpressionNode, AbstractSyntaxTreeNode | None]
        | None
    ):
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
                if self.match_signature(sig, signature):
                    return method, None

    def match_signature(
        self, expected: inspect.Signature, arrival: inspect.Signature
    ) -> bool:
        pass

    def get_constant_on_subscription_access(
        self,
        expr: AbstractSyntaxTreeExpressionNode,
        context: AbstractSyntaxTreeNode = None,
    ) -> (
        typing.Tuple[AbstractSyntaxTreeExpressionNode, AbstractSyntaxTreeNode | None]
        | None
    ):
        pass
