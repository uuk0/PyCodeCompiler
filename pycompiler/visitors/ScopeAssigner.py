from __future__ import annotations

from pycompiler.parser.AbstractSyntaxTreeNode import AbstractSyntaxTreeNode
from pycompiler.parser.ClassDefinitionStatementNode import (
    ClassDefinitionNode,
    StaticClassReferenceNode,
    ClassDefinitionGenericReference,
)
from pycompiler.parser.FunctionDefinitionStatementNode import (
    FunctionDefinitionNode,
    FunctionDefinitionArg,
    FunctionDefinitionArgReference,
    StaticFunctionReferenceNode,
    FunctionDefinitionGenericReference,
)
from pycompiler.parser.ImportStatementNode import ImportStatement, ModuleReferenceNode
from pycompiler.parser.ListConstruction import ListComprehensionNode
from pycompiler.parser.NameAccessNode import NameWriteAccessNode, NameAccessLocalNode
from pycompiler.parser.TypeStatementNode import (
    TypeStatementNode,
    StaticTypeDefinitionReference,
)
from pycompiler.visitors.Scope import Scope
from pycompiler.visitors.AbstractSyntaxTreeVisitor import AbstractASTTreeVisitor


class ScopeAssigner(AbstractASTTreeVisitor):
    def __init__(self, root_scope: Scope):
        self.root_scope = root_scope
        self.scope_stack = [root_scope]

    def push_scope(self, scope: Scope = None):
        self.scope_stack.append(scope or self.scope_stack[-1].create_child())

    def pop_scope(self):
        self.scope_stack.pop(-1)

    def visit_any(self, obj: AbstractSyntaxTreeNode):
        obj.scope = self.scope_stack[-1]
        super().visit_any(obj)

    def visit_write_name_access(self, access: NameWriteAccessNode):
        self.scope_stack[-1].export_name_access(
            access.name, NameAccessLocalNode(access.name)
        )

    def visit_function_definition_node(self, definition: FunctionDefinitionNode):
        self.scope_stack[-1].export_name_access(
            definition.name, StaticFunctionReferenceNode(definition)
        )
        self.push_scope()

        for i, generic_name in enumerate(definition.generics):
            self.scope_stack[-1].export_name_access(
                generic_name, FunctionDefinitionGenericReference(generic_name, i)
            )

        self.visit_any_list(definition.parameters)
        self.visit_any_list(definition.body)
        self.pop_scope()

    def visit_function_definition_arg(self, arg: FunctionDefinitionArg):
        self.scope_stack[-1].export_name_access(
            arg.name, FunctionDefinitionArgReference(arg)
        )
        super().visit_function_definition_arg(arg)

    def visit_import_statement(self, statement: ImportStatement):
        self.scope_stack[-1].export_name_access(
            statement.module.split(".")[0],
            ModuleReferenceNode(
                statement.from_module or statement.module,
                statement.module if statement.from_module else None,
            ),
        )

    def visit_type_statement(self, statement: TypeStatementNode):
        self.scope_stack[-1].export_name_access(
            statement.get_base_name(), StaticTypeDefinitionReference(statement)
        )

        self.push_scope()
        self.visit_any(statement.base_type)
        self.visit_any(statement.real_type)
        self.pop_scope()

    def visit_class_definition(self, definition: ClassDefinitionNode):
        self.scope_stack[-1].export_name_access(
            definition.name, StaticClassReferenceNode(definition)
        )
        self.visit_any_list(definition.parent_references)

        self.push_scope()

        for i, generic_name in enumerate(definition.generics):
            self.scope_stack[-1].export_name_access(
                generic_name, ClassDefinitionGenericReference(generic_name, i)
            )

        self.visit_any_list(definition.body)
        self.pop_scope()

    def visit_list_comprehension(self, comprehension: ListComprehensionNode):
        self.push_scope()
        self.visit_any(comprehension.source_expr)
        self.visit_any(comprehension.assignment_target)
        self.visit_any(comprehension.if_cond)
        self.visit_any(comprehension.base_expr)
        self.pop_scope()
