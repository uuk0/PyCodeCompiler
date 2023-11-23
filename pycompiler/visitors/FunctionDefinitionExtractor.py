from __future__ import annotations

import typing

from pycompiler.visitors.AbstractSyntaxTreeVisitor import AbstractASTTreeVisitor
from pycompiler.parser.FunctionDefinitionStatementNode import (
    FunctionDefinitionNode,
    StaticFunctionReferenceNode,
)
from pycompiler.parser.AssignmentExpressionNode import AssignmentExpressionNode
from pycompiler.parser.NameAccessNode import NameAccessNode


class FunctionDefinitionExtractor(AbstractASTTreeVisitor):
    def __init__(self):
        self.definitions: typing.List[FunctionDefinitionNode] = []

    def visit_function_definition_node(self, definition: FunctionDefinitionNode):
        super().visit_function_definition_node(definition)

        self.definitions.append(definition)
        definition.replace_with(
            AssignmentExpressionNode(
                [NameAccessNode(definition.name)],
                StaticFunctionReferenceNode(definition),
            )
        )
