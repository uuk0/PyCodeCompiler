import typing

from TypeResolver import SyntaxTreeVisitor
from pycompiler.Parser import (
    YieldStatement,
    ClassDefinitionNode,
    FunctionDefinitionNode,
    ReturnStatement,
    GeneratorExitReturnStatement,
)


class GetValidYieldStatements(SyntaxTreeVisitor):
    def __init__(self):
        self.statements: typing.List[YieldStatement] = []

    def visit_yield_statement(self, yield_statement: YieldStatement):
        super().visit_yield_statement(yield_statement)

        self.statements.append(yield_statement)

    def visit_class_definition(self, node: ClassDefinitionNode):
        pass

    def visit_function_definition(self, node: FunctionDefinitionNode):
        pass


class RewriteReturnToGeneratorExit(SyntaxTreeVisitor):
    def visit_return_statement(self, return_statement: ReturnStatement):
        super().visit_return_statement(return_statement)

        return_statement.parent[0].try_replace_child(
            return_statement,
            GeneratorExitReturnStatement(return_statement.return_value),
            return_statement.parent[1],
        )

    def visit_class_definition(self, node: ClassDefinitionNode):
        pass

    def visit_function_definition(self, node: FunctionDefinitionNode):
        pass
