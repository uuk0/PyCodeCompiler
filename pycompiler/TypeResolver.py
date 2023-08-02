from __future__ import annotations

import typing
import warnings

from pycompiler.Parser import SyntaxTreeVisitor, Scope, ParentAttributeSection, ConstantAccessExpression, \
    NameAccessExpression, WhileStatement, FunctionDefinitionNode

if typing.TYPE_CHECKING:
    from pycompiler.Parser import ClassDefinitionNode, AssignmentExpression, AbstractASTNode, AttributeExpression, SubscriptionExpression, ReturnStatement, CallExpression, BinaryOperatorExpression, WalrusOperatorExpression


class ResolveParentAttribute(SyntaxTreeVisitor):
    def visit_assignment(self, assignment: AssignmentExpression):
        super().visit_assignment(assignment)
        for target in assignment.lhs:
            target.parent = assignment, ParentAttributeSection.LHS

        assignment.rhs.parent = assignment, ParentAttributeSection.RHS

    def visit_attribute_expression(self, expression: AttributeExpression):
        super().visit_attribute_expression(expression)
        expression.base.parent = expression, ParentAttributeSection.LHS

    def visit_subscription_expression(self, expression: SubscriptionExpression):
        super().visit_subscription_expression(expression)
        expression.base.parent = expression, ParentAttributeSection.LHS
        expression.expression.parent = expression, ParentAttributeSection.RHS

    def visit_call_expression(self, node: CallExpression):
        super().visit_call_expression(node)

        node.base.parent = node, ParentAttributeSection.LHS
        for arg in node.args:
            arg.parent = node, ParentAttributeSection.RHS

    def visit_call_argument(self, arg: CallExpression.CallExpressionArgument):
        super().visit_call_argument(arg)

        arg.value.parent = arg, ParentAttributeSection.PARAMETER

    def visit_function_definition(self, node: FunctionDefinitionNode):
        super().visit_function_definition(node)

        for param in node.parameters:
            param.parent = node, None

        for body_node in node.body:
            body_node.parent = node, None

    def visit_function_definition_parameter(self, node: FunctionDefinitionNode.FunctionDefinitionParameter):
        super().visit_function_definition_parameter(node)
        if node.mode == FunctionDefinitionNode.ParameterType.KEYWORD:
            assert node.default is not None

            node.default.parent = node, ParentAttributeSection.PARAMETER

    def visit_return_statement(self, return_statement: ReturnStatement):
        super().visit_return_statement(return_statement)
        return_statement.return_value.parent = return_statement, ParentAttributeSection.RHS

    def visit_class_definition(self, node: ClassDefinitionNode):
        super().visit_class_definition(node)

        for parent in node.parents:
            parent.parent = node, ParentAttributeSection.PARAMETER

        for line in node.body:
            line.parent = node, ParentAttributeSection.BODY

    def visit_while_statement(self, while_statement: WhileStatement):
        super().visit_while_statement(while_statement)

        while_statement.condition.parent = while_statement, ParentAttributeSection.LHS

        for line in while_statement.body:
            line.parent = while_statement, ParentAttributeSection.BODY

    def visit_binary_operator(self, operator: BinaryOperatorExpression):
        super().visit_binary_operator(operator)

        operator.lhs = operator, ParentAttributeSection.LHS
        operator.rhs = operator, ParentAttributeSection.RHS

    def visit_walrus_operator(self, operator: WalrusOperatorExpression):
        super().visit_walrus_operator(operator)

        operator.target.parent = operator, ParentAttributeSection.LHS
        operator.value.parent = operator, ParentAttributeSection.RHS


class ScopeGeneratorVisitor(SyntaxTreeVisitor):
    def __init__(self, scope: Scope):
        self.scope: Scope = scope

    def visit_any(self, obj: AbstractASTNode):
        obj.scope = self.scope
        super().visit_any(obj)

    def visit_class_definition(self, node: ClassDefinitionNode):
        outer_scope = self.scope
        outer_scope.expose_type_name(node.name.text, node)
        self.scope = self.scope.copy()
        self.scope.class_name_stack.append(node.name.text)

        for name in node.generics:
            self.scope.export_variable_name(name.text)

        super().visit_class_definition(node)

        self.scope.close(export_local_name=node.name.text)
        self.scope = outer_scope

        self.scope.export_variable_name(node.name.text, strong_value=node)

    def visit_function_definition(self, node: FunctionDefinitionNode):
        outer_scope = self.scope
        self.scope = self.scope.copy()

        for name in node.generics:
            self.scope.export_variable_name(name.text)

        super().visit_function_definition(node)

        self.scope.close()
        self.scope = outer_scope

        self.scope.export_variable_name(node.name.text, strong_value=node)

    def visit_function_definition_parameter(self, node: FunctionDefinitionNode.FunctionDefinitionParameter):
        super().visit_function_definition_parameter(node)
        node.scope = self.scope

        self.scope.export_variable_name(node.name.text)

    def visit_assignment(self, assignment: AssignmentExpression):
        super().visit_assignment(assignment)

        for target in assignment.lhs:
            if isinstance(target, NameAccessExpression):
                self.scope.export_variable_name(target.name.text)

    def visit_while_statement(self, while_statement: WhileStatement):
        self.visit_any(while_statement.condition)

        outer_scope = self.scope
        self.scope = self.scope.copy()

        self.visit_any_list(while_statement.body)

        self.scope.close()
        self.scope = outer_scope

    def visit_walrus_operator(self, operator: WalrusOperatorExpression):
        super().visit_walrus_operator(operator)

        if isinstance(operator.target, NameAccessExpression):
            self.scope.export_variable_name(operator.target.name.text)


class NameNormalizer(SyntaxTreeVisitor):
    def visit_function_definition(self, node: FunctionDefinitionNode):
        super().visit_function_definition(node)
        node.normal_name = node.scope.get_normalised_name(node.name.text)
        node.scope.add_remapped_name(node.name.text, node.normal_name)

    def visit_function_definition_parameter(self, node: FunctionDefinitionNode.FunctionDefinitionParameter):
        super().visit_function_definition_parameter(node)
        node.normal_name = node.scope.get_normalised_name(node.name.text)
        node.scope.add_remapped_name(node.name.text, node.normal_name)

    def visit_class_definition(self, node: ClassDefinitionNode):
        super().visit_class_definition(node)
        node.normal_name = node.scope.get_normalised_name(node.name.text)
        node.scope.add_remapped_name(node.name.text, node.normal_name)


class LocalNameValidator(SyntaxTreeVisitor):
    def visit_name_access(self, access: NameAccessExpression):
        super().visit_name_access(access)

        if not access.scope.has_name_access(access.name.text):
            raise NameError(f"Cannot find {access.name.text} at {access} in scope {access.scope}")


class ResolveStaticNames(SyntaxTreeVisitor):
    def visit_name_access(self, access: NameAccessExpression):
        super().visit_name_access(access)

        try:
            value = access.scope.get_static_value_or_fail(access.name.text)
        except NameError:
            return

        assert access.parent is not None, "should not be reached"

        if not access.parent[0].try_replace_child(access, ConstantAccessExpression(value), access.parent[1]):
            warnings.warn(f"Could not replace node {access} as child of {access.parent[0]} with constant value access to {value}")

    def visit_attribute_expression(self, expression: AttributeExpression):
        super().visit_attribute_expression(expression)

        if isinstance(expression.base, ConstantAccessExpression) and isinstance(expression.base.value, ClassDefinitionNode):
            pass  # todo: check if value is static access-able and replace in that case

    def visit_subscription_expression(self, expression: SubscriptionExpression):
        super().visit_subscription_expression(expression)

        if isinstance(expression.base, ConstantAccessExpression) and isinstance(expression.base.value, ClassDefinitionNode):
            pass  # todo: check for generic at compile time

