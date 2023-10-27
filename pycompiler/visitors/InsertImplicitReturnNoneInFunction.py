from __future__ import annotations

from pycompiler.parser.FunctionDefinitionStatementNode import FunctionDefinitionNode
from pycompiler.parser.ReturnStatementNode import ReturnStatement
from pycompiler.parser.ConstantValueExpressionNode import ConstantValueExpressionNode
from pycompiler.visitors.AbstractSyntaxTreeVisitor import AbstractASTTreeVisitor


class MergeGenericsIntoReferenceVisitor(AbstractASTTreeVisitor):
    def visit_function_definition_node(self, definition: FunctionDefinitionNode):
        if not definition.body or not isinstance(definition.body[-1], ReturnStatement):
            definition.body.append(ReturnStatement(ConstantValueExpressionNode(None)))
