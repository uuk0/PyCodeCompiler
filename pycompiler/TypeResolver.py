from __future__ import annotations

import typing
import warnings

from pycompiler.Lexer import TokenType
from pycompiler.Parser import (
    SyntaxTreeVisitor,
    Scope,
    ParentAttributeSection,
    ConstantAccessExpression,
    NameAccessExpression,
    WhileStatement,
    FunctionDefinitionNode,
    StandardLibraryClass,
    SubscriptionExpression,
    BinaryOperatorExpression,
    GlobalCNameAccessExpression,
    ClassExactDataType,
    ClassDefinitionNode,
    CallExpression,
    AssignmentExpression,
    ImportStatement,
    ModuleReference,
    StandardLibraryModuleReference,
    PyNewlineNode,
    YieldStatement,
)

if typing.TYPE_CHECKING:
    from pycompiler.Parser import (
        AbstractASTNode,
        AttributeExpression,
        ReturnStatement,
        WalrusOperatorExpression,
        PriorityBrackets,
        TupleConstructor,
        ListConstructor,
        AssertStatement,
    )


class GetModuleImports(SyntaxTreeVisitor):
    def __init__(self):
        self.modules = []

    def visit_import_statement(self, node: ImportStatement):
        super().visit_import_statement(node)

        self.modules.append(node.module)


class GetHeaderRelatedInfo(SyntaxTreeVisitor):
    def __init__(self):
        self.function_signatures = []
        self.global_variables = []

    def visit_function_definition(self, node: FunctionDefinitionNode):
        super().visit_function_definition(node)
        self.function_signatures.append(
            f"PyObjectContainer* {node.normal_name}_safeWrap(PyObjectContainer* self, uint8_t argc, "
            f"PyObjectContainer** args, CallStructureInfo* info)"
        )
        self.function_signatures.append(
            f"PyObjectContainer* {node.normal_name}("
            f"{', '.join(f'PyObjectContainer* {e.normal_name}' for e in node.parameters)})"
        )

        if node.is_generator:
            self.function_signatures.append(
                f"PyObjectContainer* {node.normal_name}_ENTRY(PyGeneratorContainer* generator)"
            )

    def visit_class_definition(self, node: ClassDefinitionNode):
        super().visit_class_definition(node)

        self.function_signatures.append(
            f"void PY_CLASS_INIT_PY_CLASS_{node.normal_name}(void)"
        )
        self.global_variables.append(f"PyClassContainer* PY_CLASS_{node.normal_name}")


class ModuleReferencesResolver(SyntaxTreeVisitor):
    def __init__(self, modules: typing.Dict):
        self.modules = modules

    def visit_module_reference(self, module: ModuleReference):
        super().visit_module_reference(module)

        if module.name in self.modules:
            module.base_scope = self.modules[module.name]


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

    def visit_function_definition_parameter(
        self, node: FunctionDefinitionNode.FunctionDefinitionParameter
    ):
        super().visit_function_definition_parameter(node)

        if node.mode == FunctionDefinitionNode.ParameterType.KEYWORD:
            assert node.default is not None

            node.default.parent = node, ParentAttributeSection.PARAMETER

    def visit_return_statement(self, return_statement: ReturnStatement):
        super().visit_return_statement(return_statement)
        return_statement.return_value.parent = (
            return_statement,
            ParentAttributeSection.RHS,
        )

    def visit_yield_statement(self, yield_statement: YieldStatement):
        super().visit_yield_statement(yield_statement)
        yield_statement.yield_expression.parent = (
            yield_statement,
            ParentAttributeSection.RHS,
        )

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

        for line in while_statement.else_node:
            line.parent = while_statement, ParentAttributeSection.ELSE_BRANCH

    def visit_binary_operator(self, operator: BinaryOperatorExpression):
        super().visit_binary_operator(operator)

        operator.lhs.parent = operator, ParentAttributeSection.LHS
        operator.rhs.parent = operator, ParentAttributeSection.RHS

    def visit_walrus_operator(self, operator: WalrusOperatorExpression):
        super().visit_walrus_operator(operator)

        operator.target.parent = operator, ParentAttributeSection.LHS
        operator.value.parent = operator, ParentAttributeSection.RHS

    def visit_priority_bracket(self, node: PriorityBrackets):
        super().visit_priority_bracket(node)
        node.inner_node.parent = node

    def visit_tuple_constructor(self, node: TupleConstructor):
        super().visit_tuple_constructor(node)
        for n in node.items:
            n.parent = node

    def visit_list_constructor(self, node: ListConstructor):
        super().visit_list_constructor(node)
        for n in node.items:
            n.parent = node

    def visit_assert_statement(self, node: AssertStatement):
        super().visit_assert_statement(node)

        node.statement.parent = node
        if node.message:
            node.message.parent = node


class BinaryOperatorPriorityRewriter(SyntaxTreeVisitor):
    def visit_binary_operator(self, operator: BinaryOperatorExpression):
        lhs_inst = isinstance(operator.lhs, BinaryOperatorExpression)
        rhs_inst = isinstance(operator.rhs, BinaryOperatorExpression)

        if (
            lhs_inst
            and rhs_inst
            and (
                BinaryOperatorExpression.PRIORITIES[operator.lhs.operator]
                < BinaryOperatorExpression.PRIORITIES[operator.operator]
            )
            and (
                BinaryOperatorExpression.PRIORITIES[operator.rhs.operator]
                < BinaryOperatorExpression.PRIORITIES[operator.operator]
            )
        ):
            lhs = operator.lhs.lhs
            rhs = BinaryOperatorExpression(
                BinaryOperatorExpression(
                    operator.lhs.rhs,
                    operator.operator.operator.rhs.lhs,
                ),
                operator.rhs.operator,
                operator.rhs.rhs,
            )
            rhs.parent = operator, ParentAttributeSection.RHS
            lhs.parent = operator, ParentAttributeSection.LHS
            rhs.lhs.parent = operator, ParentAttributeSection.LHS
            rhs.rhs.parent = operator, ParentAttributeSection.RHS
            operator.operator = operator.lhs.operator
            operator.lhs = lhs
            operator.rhs = rhs

            # Need to sort out the lowest layer also
            self.visit_binary_operator(operator)
            return

        elif lhs_inst and (
            BinaryOperatorExpression.PRIORITIES[operator.lhs.operator]
            < BinaryOperatorExpression.PRIORITIES[operator.operator]
        ):
            lhs = operator.lhs.lhs
            rhs = BinaryOperatorExpression(
                operator.lhs.rhs, operator.operator, operator.rhs
            )
            lhs.parent = operator, ParentAttributeSection.LHS
            rhs.parent = operator, ParentAttributeSection.RHS
            rhs.lhs.parent = rhs, ParentAttributeSection.LHS
            rhs.rhs.parent = rhs, ParentAttributeSection.RHS
            operator.operator = operator.lhs.operator
            operator.lhs = lhs
            operator.rhs = rhs

        elif rhs_inst and (
            BinaryOperatorExpression.PRIORITIES[operator.rhs.operator]
            < BinaryOperatorExpression.PRIORITIES[operator.operator]
        ):
            rhs = operator.rhs.rhs
            lhs = BinaryOperatorExpression(
                operator.lhs, operator.operator, operator.rhs.lhs
            )
            lhs.parent = operator, ParentAttributeSection.LHS
            rhs.parent = operator, ParentAttributeSection.RHS
            lhs.lhs.parent = lhs, ParentAttributeSection.LHS
            lhs.lhs.parent = lhs, ParentAttributeSection.RHS
            operator.operator = operator.rhs.operator
            operator.lhs = lhs
            operator.rhs = rhs

        super().visit_binary_operator(operator)


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

    def visit_function_definition_parameter(
        self, node: FunctionDefinitionNode.FunctionDefinitionParameter
    ):
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
        self.visit_any_list(while_statement.else_node)

        self.scope.close()
        self.scope = outer_scope

    def visit_walrus_operator(self, operator: WalrusOperatorExpression):
        super().visit_walrus_operator(operator)

        if isinstance(operator.target, NameAccessExpression):
            self.scope.export_variable_name(operator.target.name.text)

    def visit_import_statement(self, node: ImportStatement):
        super().visit_import_statement(node)

        self.scope.export_variable_name(
            (node.as_name or node.module).split(".")[0],
            strong_value=ModuleReference(node.module),
        )


class NameNormalizer(SyntaxTreeVisitor):
    def visit_function_definition(self, node: FunctionDefinitionNode):
        super().visit_function_definition(node)
        node.normal_name = node.scope.get_normalised_name(node.name.text)
        node.scope.add_remapped_name(node.name.text, node.normal_name)

    def visit_function_definition_parameter(
        self, node: FunctionDefinitionNode.FunctionDefinitionParameter
    ):
        super().visit_function_definition_parameter(node)
        node.normal_name = node.scope.get_normalised_name(node.name.text)
        node.scope.add_remapped_name(node.name.text, node.normal_name)

    def visit_class_definition(self, node: ClassDefinitionNode):
        super().visit_class_definition(node)

        if isinstance(node, StandardLibraryClass):
            return

        node.normal_name = node.scope.get_normalised_name(node.name.text)
        node.scope.add_remapped_name(node.name.text, node.normal_name)


class GenericFuncCallInliner(SyntaxTreeVisitor):
    def visit_call_expression(self, node: CallExpression):
        super().visit_call_expression(node)

        if (
            isinstance(node.base, SubscriptionExpression)
            and isinstance(node.base.base, ConstantAccessExpression)
            and isinstance(node.base.base.value, FunctionDefinitionNode)
        ):
            node.base = (
                node.base.base
            )  # todo: add generic information to CallExpression!


class LocalNameValidator(SyntaxTreeVisitor):
    def visit_name_access(self, access: NameAccessExpression):
        super().visit_name_access(access)

        if not access.scope.has_name_access(access.name.text):
            raise NameError(
                f"Cannot find '{access.name.text}' at {access} in scope {access.scope}"
            )


class ResolveGlobalNames(SyntaxTreeVisitor):
    def visit_name_access(self, access: NameAccessExpression):
        super().visit_name_access(access)

        if global_name := access.scope.get_module_global_variable_name(
            access.name.text
        ):
            access.parent[0].try_replace_child(
                access, GlobalCNameAccessExpression(global_name), access.parent[1]
            )


class ResolveKnownDataTypes(SyntaxTreeVisitor):
    def visit_assignment(self, assignment: AssignmentExpression):
        super().visit_assignment(assignment)

        if assignment.rhs.static_value_type is not None:
            for target in assignment.lhs:
                if isinstance(target, NameAccessExpression):
                    assignment.scope.set_local_var_type_or_clear(
                        target.name.text, assignment.rhs.static_value_type
                    )

                # todo: try to do some stuff / at least invalidate from here down

    def visit_call_expression(self, node: CallExpression):
        super().visit_call_expression(node)

        if isinstance(node.base, ConstantAccessExpression):
            if (
                isinstance(node.base.value, FunctionDefinitionNode)
                and node.base.value.is_generator
            ):
                node.static_value_type = node.base.value.static_value_type
            elif isinstance(node.base.value, ClassDefinitionNode):
                node.static_value_type = ClassExactDataType(node.base.value)
            elif node.base.value == Scope.STANDARD_LIBRARY_VALUES["len"][1]:
                self.check_for_overload_on_type(node, "__len__", "len")

    def check_for_overload_on_type(self, node, bound_name, normal_name):
        if len(node.args) != 1:
            raise ValueError(
                f"{normal_name}(...) expected exactly 1 arg, got {len(node.args)}"
            )

        arg = node.args[0].value
        if (
            arg.static_value_type
            and isinstance(arg.static_value_type, ClassExactDataType)
            and bound_name in arg.static_value_type.ref.function_table
        ):
            func = arg.static_value_type.ref.function_table[bound_name]
            node.base = func


class ResolveLocalVariableAccessTypes(SyntaxTreeVisitor):
    DIRTY = False

    def visit_name_access(self, access: NameAccessExpression):
        super().visit_name_access(access)

        data_type = access.scope.variable_type_map.get(access.name.text, None)

        if data_type is not None and access.static_value_type != data_type:
            ResolveLocalVariableAccessTypes.DIRTY = True
            access.static_value_type = data_type


class ResolveClassFunctionNode(SyntaxTreeVisitor):
    def visit_attribute_expression(self, expression: AttributeExpression):
        if (
            expression.base.static_value_type
            and isinstance(expression.base.static_value_type, ClassExactDataType)
            and isinstance(expression.parent[0], CallExpression)
        ):
            data_type = expression.base.static_value_type.ref
            target = None

            if expression.attribute.text in data_type.function_table:
                target = data_type.function_table[expression.attribute.text]
            elif (
                expression.attribute.text,
                len(expression.parent[0].args),
            ) in data_type.function_table:
                target = data_type.function_table[
                    expression.attribute.text, len(expression.parent[0].args)
                ]

            if target:
                expression.parent[0].args.insert(
                    0,
                    CallExpression.CallExpressionArgument(
                        expression.base, CallExpression.ParameterType.NORMAL
                    ),
                )
                expression.parent[0].try_replace_child(
                    expression,
                    target.copy(),
                    expression.parent[1],
                )

        elif (
            isinstance(expression.base, ConstantAccessExpression)
            and isinstance(
                expression.base.value, (ModuleReference, StandardLibraryModuleReference)
            )
            and expression.attribute.text in expression.base.value.base_scope
        ):
            expression.parent[0].try_replace_child(
                expression,
                expression.base.value.base_scope[expression.attribute.text].copy(),
                expression.parent[1],
            )

    def visit_subscription_expression(self, expression: SubscriptionExpression):
        if not expression.base.static_value_type or not isinstance(
            expression.base.static_value_type, ClassExactDataType
        ):
            return

        data_type = expression.base.static_value_type.ref

        if isinstance(expression.parent[0], AssignmentExpression):
            if "__setitem__" in data_type.function_table:
                print(expression.parent[0].parent[0])
                expression.parent[0].parent[0].try_replace_child(
                    expression.parent[0],
                    CallExpression(
                        data_type.function_table["__setitem__"].copy(),
                        [],
                        TokenType.OPENING_ROUND_BRACKET("("),
                        [
                            CallExpression.CallExpressionArgument(
                                expression.base, CallExpression.ParameterType.NORMAL
                            ),
                            CallExpression.CallExpressionArgument(
                                expression.expression,
                                CallExpression.ParameterType.NORMAL,
                            ),
                            CallExpression.CallExpressionArgument(
                                expression.parent[0].rhs,
                                CallExpression.ParameterType.NORMAL,
                            ),
                        ],
                        TokenType.CLOSING_ROUND_BRACKET(")"),
                    ),
                    expression.parent[0].parent[1],
                )

        elif "__getitem__" in data_type.function_table:
            expression.parent[0].try_replace_child(
                expression,
                CallExpression(
                    data_type.function_table["__getitem__"].copy(),
                    [],
                    TokenType.OPENING_ROUND_BRACKET("("),
                    [
                        CallExpression.CallExpressionArgument(
                            expression.base, CallExpression.ParameterType.NORMAL
                        ),
                        CallExpression.CallExpressionArgument(
                            expression.expression, CallExpression.ParameterType.NORMAL
                        ),
                    ],
                    TokenType.CLOSING_ROUND_BRACKET(")"),
                ),
                expression.parent[1],
            )


class ResolveStaticNames(SyntaxTreeVisitor):
    def visit_name_access(self, access: NameAccessExpression):
        super().visit_name_access(access)

        if access.parent is None:
            print("error ResolveStaticNames", access)
            return

        arg_count = -1

        if isinstance(access.parent[0], CallExpression):
            arg_count = len(access.parent[0].args)

        try:
            value = access.scope.get_static_value_or_fail(
                access.name.text, arg_count=arg_count
            )
        except NameError:
            return

        assert access.parent is not None, "should not be reached"

        if not access.parent[0].try_replace_child(
            access, ConstantAccessExpression(value), access.parent[1]
        ):
            warnings.warn(
                f"Could not replace node {access} as child of {access.parent[0]} with constant value access to {value}"
            )

    def visit_attribute_expression(self, expression: AttributeExpression):
        super().visit_attribute_expression(expression)

        if isinstance(expression.base, ConstantAccessExpression) and isinstance(
            expression.base.value, ClassDefinitionNode
        ):
            pass  # todo: check if value is static access-able and replace in that case
        elif expression.base.static_value_type and isinstance(
            expression.base.static_value_type, ClassExactDataType
        ):
            pass

    def visit_subscription_expression(self, expression: SubscriptionExpression):
        super().visit_subscription_expression(expression)

        if isinstance(expression.base, ConstantAccessExpression) and isinstance(
            expression.base.value, ClassDefinitionNode
        ):
            pass  # todo: check for generic at compile time
