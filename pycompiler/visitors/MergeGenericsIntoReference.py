from __future__ import annotations

from pycompiler.parser.ClassDefinitionStatementNode import (
    StaticClassReferenceNodeWithGeneric,
    StaticClassReferenceNode,
)
from pycompiler.parser.FunctionDefinitionStatementNode import (
    StaticFunctionReferenceNode,
)
from pycompiler.parser.SubscriptionAccessExpressionNode import (
    SubscriptionAccessExpressionNode,
)
from pycompiler.visitors.AbstractSyntaxTreeVisitor import AbstractASTTreeVisitor


class MergeGenericsIntoReferenceVisitor(AbstractASTTreeVisitor):
    def visit_subscription_access_expression(
        self, expression: SubscriptionAccessExpressionNode
    ):
        super().visit_subscription_access_expression(expression)

        if isinstance(expression.base, StaticClassReferenceNode):
            # todo: tuple unpacking!
            if isinstance(expression.inner, tuple):
                expr = None
            else:
                assert (
                    len(expression.base.class_def.generics) == 1
                ), "generic count must match!"
                expr = StaticClassReferenceNodeWithGeneric(
                    expression.base.class_def,
                    [
                        expression.inner,
                    ],
                )

            expression.replace_with(expr)

        elif isinstance(expression.base, StaticFunctionReferenceNode):
            pass  # todo: implement

        elif isinstance(expression.base, StaticClassReferenceNodeWithGeneric):
            raise SyntaxError(
                "applied [] operator ontop of [] operator on generic class"
            )
