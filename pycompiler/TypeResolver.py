from __future__ import annotations

import typing
import warnings

from pycompiler.Parser import SyntaxTreeVisitor, Scope, ParentAttributeSection, ConstantAccessExpression, NameAccessExpression


if typing.TYPE_CHECKING:
    from pycompiler.Parser import ClassDefinitionNode, FunctionDefinitionNode, AssignmentExpression, AbstractASTNode, AttributeExpression, SubscriptionExpression


class ResolveParentAttribute(SyntaxTreeVisitor):
    def visit_assignment(self, assignment: AssignmentExpression):
        for target in assignment.lhs:
            target.parent = assignment, ParentAttributeSection.LHS

        assignment.rhs.parent = assignment, ParentAttributeSection.RHS

    def visit_attribute_expression(self, expression: AttributeExpression):
        expression.base.parent = expression, ParentAttributeSection.LHS

    def visit_subscription_expression(self, expression: SubscriptionExpression):
        expression.base.parent = expression, ParentAttributeSection.LHS
        expression.expression.parent = expression, ParentAttributeSection.RHS

    def visit_function_definition(self, node: FunctionDefinitionNode):
        for param in node.parameters:
            param.parent = node

        for body_node in node.body:
            body_node.parent = node

    def visit_function_definition_parameter(self, node: FunctionDefinitionNode.FunctionDefinitionParameter):
        if node.mode == FunctionDefinitionNode.ParameterType.KEYWORD:
            assert node.default is not None

            node.default.parent = node

    def visit_class_definition(self, node: ClassDefinitionNode):
        pass


class ScopeGeneratorVisitor(SyntaxTreeVisitor):
    def __init__(self, scope: Scope):
        self.scope: Scope = scope

    def visit_any(self, obj: AbstractASTNode):
        obj.scope = self.scope
        super().visit_any(obj)

    def visit_class_definition(self, node: ClassDefinitionNode):
        outer_scope = self.scope
        outer_scope.expose_type_name(node.name, node.text)
        self.scope = self.scope.copy()
        self.scope.class_name_stack.append(node.name.text)

        super().visit_class_definition(node)

        self.scope.close(export_local_name=node.name.text)
        self.scope = outer_scope

        self.scope.export_variable_name(node.name.text)
        # todo: generics

    def visit_function_definition(self, node: FunctionDefinitionNode):
        outer_scope = self.scope
        self.scope = self.scope.copy()

        for name in node.generics:
            self.scope.export_variable_name(name.text)

        super().visit_function_definition(node)

        self.scope.close()
        self.scope = outer_scope

        self.scope.export_variable_name(node.name.text)

    def visit_function_definition_parameter(self, node: FunctionDefinitionNode.FunctionDefinitionParameter):
        super().visit_function_definition_parameter(node)

        self.scope.export_variable_name(node.name.text)

    def visit_assignment(self, assignment: AssignmentExpression):
        super().visit_assignment(assignment)

        for target in assignment.lhs:
            if isinstance(target, NameAccessExpression):
                self.scope.export_variable_name(target.name.text)


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

