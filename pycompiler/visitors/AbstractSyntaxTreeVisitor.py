from __future__ import annotations

import typing
from abc import ABC
from pycompiler.parser.AbstractSyntaxTreeNode import AbstractSyntaxTreeNode

from pycompiler.parser.NameAccessNode import NameAccessNode
from pycompiler.parser.AssignmentExpressionNode import AssignmentExpressionNode
from pycompiler.parser.AttributeAccessExpressionNode import (
    AttributeAccessExpressionNode,
)
from pycompiler.parser.SubscriptionAccessExpressionNode import (
    SubscriptionAccessExpressionNode,
)
from pycompiler.parser.FunctionDefinitionStatementNode import (
    FunctionDefinitionNode,
    FunctionDefinitionArg,
    FunctionDefinitionGenericReference,
    FunctionDefinitionArgReference,
    StaticFunctionReferenceNode,
)
from pycompiler.parser.CallExpression import CallExpression, CallExpressionArgument
from pycompiler.parser.SliceExpressionNode import SliceExpressionNode
from pycompiler.parser.ConstantValueExpressionNode import ConstantValueExpressionNode
from pycompiler.parser.ImportStatementNode import ImportStatement
from pycompiler.parser.TypeStatementNode import TypeStatementNode
from pycompiler.parser.ScopeReferences import ParentScopeReference, ChildScopeExported
from pycompiler.parser.ClassDefinitionStatementNode import (
    ClassDefinitionNode,
    ClassDefinitionGenericReference,
    StaticClassReferenceNode,
)
from pycompiler.parser.WhileStatementNode import WhileStatementNode

from pycompiler.parser.util import ArgType


def _bind_to_datatype(
    datatype: typing.Type[AbstractSyntaxTreeNode],
) -> typing.Callable[
    [typing.Callable[[AbstractSyntaxTreeNode], None]],
    typing.Callable[[AbstractSyntaxTreeNode], None],
]:
    def target(bind_target: typing.Callable):
        _KNOWN_NAME_MAP[datatype] = bind_target.__name__
        return bind_target

    return target


_KNOWN_NAME_MAP: typing.Dict[typing.Type, str] = {}


class AbstractASTTreeVisitor(ABC):
    KNOWN_NAME_MAP: typing.Dict[typing.Type, str] = _KNOWN_NAME_MAP
    BINDING_MAP: typing.Dict[typing.Type, typing.Callable] = {}

    @classmethod
    def __init_subclass__(cls, **kwargs):
        cls.BINDING_MAP = {}
        for t, key in cls.KNOWN_NAME_MAP.items():
            cls.BINDING_MAP[t] = getattr(cls, key)

    def visit_any(self, obj: AbstractSyntaxTreeNode):
        if obj is None:
            return

        if type(obj) not in self.BINDING_MAP:
            raise NotImplementedError(f"failed to find visitor for type {type(obj)}!")

        self.BINDING_MAP[type(obj)](self, obj)

    def visit_any_list(self, objs: typing.List[AbstractSyntaxTreeNode]):
        for node in objs:
            self.visit_any(node)

    @_bind_to_datatype(NameAccessNode)
    def visit_name_access(self, access: NameAccessNode):
        pass

    @_bind_to_datatype(AssignmentExpressionNode)
    def visit_assignment_expression(self, assignment: AssignmentExpressionNode):
        self.visit_any_list(assignment.targets)
        self.visit_any(assignment.base)

    @_bind_to_datatype(AttributeAccessExpressionNode)
    def visit_attribute_access_expression(self, access: AttributeAccessExpressionNode):
        self.visit_any(access.base)

    @_bind_to_datatype(SubscriptionAccessExpressionNode)
    def visit_subscription_access_expression(
        self, expression: SubscriptionAccessExpressionNode
    ):
        self.visit_any(expression.base)
        self.visit_any(expression.inner)

    @_bind_to_datatype(FunctionDefinitionNode)
    def visit_function_definition_node(self, definition: FunctionDefinitionNode):
        self.visit_any_list(definition.parameters)
        self.visit_any_list(definition.body)

    @_bind_to_datatype(FunctionDefinitionArg)
    def visit_function_definition_arg(self, arg: FunctionDefinitionArg):
        if arg.arg_type == ArgType.KEYWORD:
            self.visit_any(arg.default_value)

    @_bind_to_datatype(FunctionDefinitionArgReference)
    def visit_function_definition_arg_ref(self, ref: FunctionDefinitionArgReference):
        pass

    @_bind_to_datatype(FunctionDefinitionGenericReference)
    def visit_function_definition_generic_ref(
        self, ref: FunctionDefinitionGenericReference
    ):
        pass

    @_bind_to_datatype(StaticFunctionReferenceNode)
    def visit_static_function_reference(self, ref: StaticFunctionReferenceNode):
        pass

    @_bind_to_datatype(CallExpression)
    def visit_call_expression(self, call: CallExpression):
        self.visit_any(call.base)
        self.visit_any_list(call.args)

    @_bind_to_datatype(CallExpressionArgument)
    def visit_call_expression_arg(self, call: CallExpressionArgument):
        self.visit_any(call.expr)

    @_bind_to_datatype(SliceExpressionNode)
    def visit_slice_expression(self, expression: SliceExpressionNode):
        self.visit_any(expression.start)
        self.visit_any(expression.stop)
        self.visit_any(expression.step)

    @_bind_to_datatype(ConstantValueExpressionNode)
    def visit_constant_access(self, expression: ConstantValueExpressionNode):
        pass

    @_bind_to_datatype(ImportStatement)
    def visit_import_statement(self, statement: ImportStatement):
        pass

    @_bind_to_datatype(TypeStatementNode)
    def visit_type_statement(self, statement: TypeStatementNode):
        self.visit_any(statement.base_type)
        self.visit_any(statement.real_type)

    @_bind_to_datatype(ParentScopeReference)
    def visit_parent_scope_reference(self, reference: ParentScopeReference):
        pass

    @_bind_to_datatype(ChildScopeExported)
    def visit_child_scope_exported(self, reference: ChildScopeExported):
        pass

    @_bind_to_datatype(ClassDefinitionNode)
    def visit_class_definition(self, definition: ClassDefinitionNode):
        self.visit_any_list(definition.parent_references)
        self.visit_any_list(definition.generics)
        self.visit_any_list(definition.body)

    @_bind_to_datatype(ClassDefinitionGenericReference)
    def visit_class_generic_reference(self, reference: ClassDefinitionGenericReference):
        pass

    @_bind_to_datatype(StaticClassReferenceNode)
    def visit_static_class_reference(self, reference: StaticClassReferenceNode):
        pass

    @_bind_to_datatype(WhileStatementNode)
    def visit_while_statement(self, while_statement: WhileStatementNode):
        self.visit_any(while_statement.condition)
        self.visit_any_list(while_statement.body)
