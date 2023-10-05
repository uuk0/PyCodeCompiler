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
    DictConstructor,
    ForLoopStatement,
    IfStatement,
    PrefixOperation,
    InplaceOperator,
    ListComprehension,
    TernaryOperator,
    CapturedLocalAccessExpression,
    WalrusOperatorExpression,
    TupleConstructor,
)

if typing.TYPE_CHECKING:
    from pycompiler.Parser import (
        AbstractASTNode,
        AttributeExpression,
        ReturnStatement,
        PriorityBrackets,
        ListConstructor,
        AssertStatement,
    )


class GetModuleImports(SyntaxTreeVisitor):
    def __init__(self):
        super().__init__()
        self.modules = []

    def visit_import_statement(self, node: ImportStatement):
        super().visit_import_statement(node)

        self.modules.append(node.module)


class GetHeaderRelatedInfo(SyntaxTreeVisitor):
    def __init__(self):
        super().__init__()
        self.function_signatures = []
        self.global_variables = []

    def visit_function_definition(self, node: FunctionDefinitionNode):
        super().visit_function_definition(node)
        self.function_signatures.append(
            f"PyObjectContainer* {node.normal_name}_safeWrap(PyObjectContainer* self, uint8_t argc, "
            f"PyObjectContainer** args, CallStructureInfo* info)"
        )

        if node.local_value_capturing:
            self.function_signatures.append(
                f"PyObjectContainer* {node.normal_name}(PyObjectContainer* {node.get_self_var_name()}{', ' if node.parameters else ''}"
                f"{', '.join(f'PyObjectContainer* {e.normal_name}' for e in node.parameters)})"
            )
        else:
            self.function_signatures.append(
                f"PyObjectContainer* {node.normal_name}("
                f"{', '.join(f'PyObjectContainer* {e.normal_name}' for e in node.parameters)})"
            )

        self.global_variables.append(
            f"PyObjectContainer* function_container_{node.normal_name}"
        )

        if node.is_generator:
            self.function_signatures.append(
                f"PyObjectContainer* {node.normal_name}_ENTRY(PyGeneratorContainer* generator)"
            )

    def visit_class_definition(self, node: ClassDefinitionNode):
        super().visit_class_definition(node)

        self.function_signatures.append(
            f"PyObjectContainer* PY_CLASS_INIT_PY_CLASS_{node.normal_name}(PyClassContainer** cls)"
        )

        if node.is_toplevel_class:
            self.global_variables.append(
                f"PyClassContainer* PY_CLASS_{node.normal_name}"
            )


class GetCapturedNames(SyntaxTreeVisitor):
    def __init__(self):
        super().__init__()
        self.names: typing.List[str] = []

    def visit_name_access(self, access: NameAccessExpression):
        if access.name.text not in access.scope.variable_name_stack:
            if access.name.text not in self.names:
                index = len(access.name.text)
                self.names.append(access.name.text)
            else:
                index = self.names.index(access.name.text)

            access.parent[0].try_replace_child(
                access,
                GlobalCNameAccessExpression(f"locals[{index - 1}]"),  # todo: why -1?
                access.parent[1],
            )


class ModuleReferencesResolver(SyntaxTreeVisitor):
    def __init__(self, modules: typing.Dict):
        super().__init__()
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

    def visit_for_statement(self, for_statement: ForLoopStatement):
        super().visit_for_statement(for_statement)

        for_statement.target.parent = for_statement, ParentAttributeSection.LHS
        for_statement.iterator.parent = for_statement, ParentAttributeSection.RHS

        for line in for_statement.body:
            line.parent = for_statement, ParentAttributeSection.BODY

        for line in for_statement.else_block:
            line.parent = for_statement, ParentAttributeSection.ELSE_BRANCH

    def visit_if_statement(self, if_statement: IfStatement):
        super().visit_if_statement(if_statement)

        if_statement.main_condition.parent = if_statement, ParentAttributeSection.LHS

        for line in if_statement.main_block:
            line.parent = if_statement, ParentAttributeSection.RHS

        for cond, nodes in if_statement.elif_blocks:
            cond.parent = if_statement, ParentAttributeSection.PARAMETER

            for line in nodes:
                line.parent = if_statement, ParentAttributeSection.BODY

        for line in if_statement.else_block or []:
            line.parent = if_statement, ParentAttributeSection.ELSE_BRANCH

    def visit_binary_operator(self, operator: BinaryOperatorExpression):
        super().visit_binary_operator(operator)

        operator.lhs.parent = operator, ParentAttributeSection.LHS
        operator.rhs.parent = operator, ParentAttributeSection.RHS

    def visit_inplace_operator(self, operator: InplaceOperator):
        super().visit_inplace_operator(operator)

        operator.lhs.parent = operator, ParentAttributeSection.LHS
        operator.rhs.parent = operator, ParentAttributeSection.RHS

    def visit_walrus_operator(self, operator: WalrusOperatorExpression):
        super().visit_walrus_operator(operator)

        operator.target.parent = operator, ParentAttributeSection.LHS
        operator.value.parent = operator, ParentAttributeSection.RHS

    def visit_priority_bracket(self, node: PriorityBrackets):
        super().visit_priority_bracket(node)
        node.inner_node.parent = node, ParentAttributeSection.RHS

    def visit_tuple_constructor(self, node: TupleConstructor):
        super().visit_tuple_constructor(node)
        for n in node.items:
            n.parent = node, ParentAttributeSection.RHS

    def visit_list_constructor(self, node: ListConstructor):
        super().visit_list_constructor(node)
        for n in node.items:
            n.parent = node, ParentAttributeSection.RHS

    def visit_dict_constructor(self, node: DictConstructor):
        super().visit_dict_constructor(node)

        for key, value in node.key_value_pairs:
            key.parent = node, ParentAttributeSection.LHS
            value.parent = node, ParentAttributeSection.RHS

    def visit_assert_statement(self, node: AssertStatement):
        super().visit_assert_statement(node)

        node.statement.parent = node, ParentAttributeSection.LHS
        if node.message:
            node.message.parent = node, ParentAttributeSection.RHS

    def visit_prefix_operation(self, operation: PrefixOperation):
        super().visit_prefix_operation(operation)

        operation.value.parent = operation, ParentAttributeSection.RHS

    def visit_list_comprehension(self, comprehension: ListComprehension):
        super().visit_list_comprehension(comprehension)

        comprehension.base_expression.parent = (
            comprehension,
            ParentAttributeSection.BODY,
        )
        comprehension.target_expression.parent = (
            comprehension,
            ParentAttributeSection.LHS,
        )
        comprehension.iterable.parent = comprehension, ParentAttributeSection.RHS
        if comprehension.if_node:
            comprehension.if_node.parent = (
                comprehension,
                ParentAttributeSection.ELSE_BRANCH,
            )

    def visit_ternary_operator(self, operator: TernaryOperator):
        super().visit_ternary_operator(operator)

        operator.lhs.parent = operator, ParentAttributeSection.LHS
        operator.cond.parent = operator, ParentAttributeSection.PARAMETER
        operator.rhs.parent = operator, ParentAttributeSection.RHS


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
        super().__init__()
        self.scope: Scope = scope
        self.enable_name_access_export = False

    def visit_any(self, obj: AbstractASTNode):
        if obj:
            obj.scope = self.scope
            super().visit_any(obj)

    def visit_class_definition(self, node: ClassDefinitionNode):
        outer_scope = self.scope
        outer_scope.expose_type_name(node.name.text, node)
        self.scope = self.scope.copy()
        self.scope.export_locals_to_inner = False
        self.scope.class_name_stack.append(node.name.text)

        self.scope.is_scope_root = True

        for name in node.generics:
            self.scope.export_variable_name(name.text)

        super().visit_class_definition(node)

        self.scope.close(export_local_name=node.name.text)
        self.scope = outer_scope

        if node.is_toplevel_class:
            self.scope.export_variable_name(node.name.text, strong_value=node)
        else:
            self.scope.export_variable_name("PY_CLASS_" + node.normal_name)

    def visit_function_definition(self, node: FunctionDefinitionNode):
        outer_scope = self.scope
        self.scope = self.scope.copy()

        self.scope.is_scope_root = True

        for name in node.generics:
            self.scope.export_variable_name(name.text)

        super().visit_function_definition(node)

        self.scope.close()
        self.scope = outer_scope

        if node.is_top_level:
            self.scope.export_variable_name(node.name.text, strong_value=node)

    def visit_function_definition_parameter(
        self, node: FunctionDefinitionNode.FunctionDefinitionParameter
    ):
        super().visit_function_definition_parameter(node)
        node.scope = self.scope

        self.scope.export_variable_name(node.name.text)

    def visit_assignment(self, assignment: AssignmentExpression):
        self.enable_name_access_export = True
        self.visit_any_list(assignment.lhs)
        self.enable_name_access_export = False
        self.visit_any(assignment.rhs)

    def visit_name_access(self, access: NameAccessExpression):
        super().visit_name_access(access)

        if not access.parent:
            raise ValueError(access)

        if (
            isinstance(
                access.parent[0],
                (
                    AssignmentExpression,
                    WalrusOperatorExpression,
                    ForLoopStatement,
                    ListComprehension,
                ),
            )
            and access.parent[1] == ParentAttributeSection.LHS
        ):
            self.scope.export_variable_name(access.name.text)
        # todo: ensure lhs of assignment-like!
        elif isinstance(access.parent[0], TupleConstructor):
            self.scope.export_variable_name(access.name.text)
        # else:
        #     print(access, access.parent)

    def visit_while_statement(self, while_statement: WhileStatement):
        super().visit_while_statement(while_statement)

        outer_scope = self.scope
        self.scope = self.scope.copy()

        self.visit_any_list(while_statement.body)
        self.visit_any_list(while_statement.else_node)

        self.scope.close()
        self.scope = outer_scope

    def visit_for_statement(self, for_statement: ForLoopStatement):
        self.visit_any(for_statement.iterator),
        self.visit_any(AssignmentExpression([for_statement.target], None, None))
        for_statement.target.scope = self.scope
        self.visit_any_list(for_statement.body),
        self.visit_any_list(for_statement.else_block)

        outer_scope = self.scope
        self.scope = self.scope.copy()

        self.visit_any_list(for_statement.body)
        self.visit_any_list(for_statement.else_block)

        self.scope.close()
        self.scope = outer_scope

    def visit_list_comprehension(self, comprehension: ListComprehension):
        self.visit_any(comprehension.iterable)

        outer_scope = self.scope
        self.scope = self.scope.copy()

        self.visit_any(
            AssignmentExpression([comprehension.target_expression], None, None)
        )
        self.visit_any(comprehension.base_expression)
        self.visit_any(comprehension.if_node)

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

    def visit_yield_statement(self, yield_statement: YieldStatement):
        if not yield_statement.is_yield_from or yield_statement.is_rebuild:
            return
        yield_statement.is_rebuild = True

        name = yield_statement.scope.get_fresh_name("yield_intermediate_value")

        # todo: wrap __iter__ call in condition
        yield_statement.parent[0].try_insert_before(
            yield_statement,
            new_node := AssignmentExpression(
                [NameAccessExpression(TokenType.IDENTIFIER(name))],
                TokenType.EQUAL_SIGN("="),
                CallExpression(
                    ConstantAccessExpression(
                        GlobalCNameAccessExpression(
                            "PY_STD_operator_iter_for_yield_from"
                        )
                    ),
                    [],
                    TokenType.OPENING_ROUND_BRACKET("("),
                    [
                        CallExpression.CallExpressionArgument(
                            yield_statement.yield_expression,
                            CallExpression.ParameterType.NORMAL,
                        ),
                        CallExpression.CallExpressionArgument(
                            NameAccessExpression(TokenType.IDENTIFIER(name)),
                            CallExpression.ParameterType.NORMAL,
                        ),
                    ],
                    TokenType.CLOSING_ROUND_BRACKET(")"),
                ),
            ),
            yield_statement.parent[1],
        )
        yield_statement.yield_expression = NameAccessExpression(
            TokenType.IDENTIFIER(name)
        )

        ResolveParentAttribute().visit_any(new_node)
        ScopeGeneratorVisitor(yield_statement.scope).visit_any(new_node)
        yield_statement.yield_expression.scope = yield_statement.scope

        ResolveParentAttribute().visit_any(yield_statement.parent[0])


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
    def __init__(self):
        super().__init__()
        self.curr_func: FunctionDefinitionNode | None = None

    def visit_function_definition(self, node: FunctionDefinitionNode):
        old = self.curr_func
        self.curr_func = node
        super().visit_function_definition(node)
        self.curr_func = old

    def visit_class_definition(self, node: ClassDefinitionNode):
        old = self.curr_func
        self.curr_func = None
        super().visit_class_definition(node)
        self.curr_func = old

    def visit_name_access(self, access: NameAccessExpression):
        super().visit_name_access(access)

        if access.scope.has_name_access(access.name.text):
            return

        if self.curr_func and self.curr_func.local_capture_node:
            func: FunctionDefinitionNode = self.curr_func
            scope = func.local_capture_node.get_enclosing_scope()

            NameNormalizer().visit_any(self.curr_func.local_capture_node)
            self.visit_any(self.curr_func.local_capture_node)

            if scope.has_name_access(access.name.text):
                if access.name.text not in func.local_value_capturing:
                    func.local_value_capturing.append(access.name.text)

                access.parent[0].try_replace_child(
                    access,
                    CapturedLocalAccessExpression(
                        access.name,
                        func.local_value_capturing.index(access.name.text),
                    ),
                    access.parent[1],
                )
                return

        raise NameError(
            f"Cannot find '{access.name.text}' at {access} in scope {access.scope}"
        )


class ResolveGlobalNames(SyntaxTreeVisitor):
    def visit_name_access(self, access: NameAccessExpression):
        super().visit_name_access(access)

        if global_name := access.scope.get_module_global_variable_name(
            access.name.text
        ):
            # print("global", access.name.text, global_name)
            # print(access.scope.global_scope.variable_name_stack)
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
                self.check_for_overload_on_type(node, "__len__", "len", 1)
            elif node.base.value == Scope.STANDARD_LIBRARY_VALUES["next"][1]:
                self.check_for_overload_on_type(node, "__next__", "next", 1)
            elif node.base.value == Scope.STANDARD_LIBRARY_VALUES["next"][2]:
                self.check_for_overload_on_type(node, "__next__", "next", 2)
            elif isinstance(node.base.value, FunctionDefinitionNode):
                node.static_value_type = node.base.value.return_type
            elif isinstance(node.base.value, GlobalCNameAccessExpression):
                node.static_value_type = node.base.value.data_type

    def check_for_overload_on_type(self, node, bound_name, normal_name, arg_count: int):
        if len(node.args) != arg_count:
            raise ValueError(
                f"{normal_name}(...) expected exactly {arg_count} arg, got {len(node.args)}"
            )

        arg = node.args[0].value
        if arg.static_value_type and isinstance(
            arg.static_value_type, ClassExactDataType
        ):
            if (bound_name, arg_count) in arg.static_value_type.ref.function_table:
                func = arg.static_value_type.ref.function_table[bound_name, arg_count]
                node.base = func
            elif bound_name in arg.static_value_type.ref.function_table:
                func = arg.static_value_type.ref.function_table[bound_name]
                node.base = func
            elif (bound_name, "*") in arg.static_value_type.ref.function_table:
                func = arg.static_value_type.ref.function_table[bound_name, "*"]
                node.base = func

    def visit_binary_operator(self, operator: BinaryOperatorExpression):
        super().visit_binary_operator(operator)

        if (
            operator.lhs.static_value_type
            and isinstance(operator.lhs.static_value_type, ClassExactDataType)
            and operator.operator in BinaryOperatorExpression.PYTHON_OPERATOR_REFS
        ):
            method_name = BinaryOperatorExpression.PYTHON_OPERATOR_REFS[
                operator.operator
            ]

            if method_name in operator.lhs.static_value_type.ref.function_table:
                operator.parent[0].try_replace_child(
                    operator,
                    CallExpression(
                        operator.lhs.static_value_type.ref.function_table[method_name],
                        [],
                        None,
                        [
                            CallExpression.CallExpressionArgument(
                                operator.lhs,
                                CallExpression.ParameterType.NORMAL,
                            ),
                            CallExpression.CallExpressionArgument(
                                operator.rhs,
                                CallExpression.ParameterType.NORMAL,
                            ),
                        ],
                        None,
                    ),
                    operator.parent[1],
                )

    def visit_inplace_operator(self, operator: BinaryOperatorExpression):
        super().visit_inplace_operator(operator)

        if (
            operator.lhs.static_value_type
            and isinstance(operator.lhs.static_value_type, ClassExactDataType)
            and operator.operator in BinaryOperatorExpression.PYTHON_OPERATOR_REFS
        ):
            method_name = BinaryOperatorExpression.PYTHON_OPERATOR_REFS[
                operator.operator
            ]

            if method_name in operator.lhs.static_value_type.ref.function_table:
                operator.parent[0].try_replace_child(
                    operator,
                    AssignmentExpression(
                        [operator.lhs],
                        None,
                        CallExpression(
                            operator.lhs.static_value_type.ref.function_table[
                                method_name
                            ],
                            [],
                            None,
                            [
                                CallExpression.CallExpressionArgument(
                                    operator.lhs,
                                    CallExpression.ParameterType.NORMAL,
                                ),
                                CallExpression.CallExpressionArgument(
                                    operator.rhs,
                                    CallExpression.ParameterType.NORMAL,
                                ),
                            ],
                            None,
                        ),
                    ),
                    operator.parent[1],
                )

    def visit_list_comprehension(self, comprehension: ListComprehension):
        super().visit_list_comprehension(comprehension)

        if comprehension.iterable.static_value_type is not None and isinstance(
            comprehension.iterable.static_value_type, ClassExactDataType
        ):
            if (
                comprehension.iterable.static_value_type.ref
                == Scope.STANDARD_LIBRARY_VALUES["list"]["*"]
            ):
                comprehension.variant = "PY_STD_list_CONSTRUCT_COMPREHENSION_on_list"
                return

            table = comprehension.iterable.static_value_type.ref.function_table
            method = table.get(
                ("__len__", 0), table.get(("__len__", "*"), table.get("__len__", None))
            )

            if method is not None:
                comprehension.len_hint = method

            method = table.get(
                ("__iter__", 0),
                table.get(("__iter__", "*"), table.get("__iter__", None)),
            )
            if method is not None:
                comprehension.iter_hint = method


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
            print("error ResolveStaticNames (no parent)", access)
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
