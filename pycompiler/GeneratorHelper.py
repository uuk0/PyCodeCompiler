import typing

from pycompiler.TypeResolver import SyntaxTreeVisitor
from pycompiler.Parser import (
    YieldStatement,
    ClassDefinitionNode,
    FunctionDefinitionNode,
    ReturnStatement,
    GeneratorExitReturnStatement,
    NameAccessExpression,
    GeneratorNameAccessExpression,
)


class GetValidYieldStatements(SyntaxTreeVisitor):
    def __init__(self):
        super().__init__()
        self.statements: typing.List[YieldStatement] = []

    def visit_yield_statement(self, yield_statement: YieldStatement):
        super().visit_yield_statement(yield_statement)

        self.statements.append(yield_statement)

    def visit_class_definition(self, node: ClassDefinitionNode):
        pass

    def visit_function_definition(self, node: FunctionDefinitionNode):
        pass


class LocalNameAccessRewriter(SyntaxTreeVisitor):
    def __init__(self):
        super().__init__()
        self.name_index_table = {}
        self.next_name_id = 0

    def visit_name_access(self, access: NameAccessExpression):
        super().visit_name_access(access)

        if access.name.text not in access.scope.variable_name_stack:
            return

        if access.parent is None:
            print("error LocalNameAccessRewriter", access)
            return

        if access.name.text in self.name_index_table:
            index = self.name_index_table[access.name.text]
        else:
            index = self.next_name_id
            self.next_name_id += 1
            self.name_index_table[access.name.text] = index

        access.parent[0].try_replace_child(
            access,
            GeneratorNameAccessExpression(
                access.name,
                index,
            ),
            access.parent[1],
        )

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
