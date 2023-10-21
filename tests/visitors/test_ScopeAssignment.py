from __future__ import annotations

import typing
import unittest

from pycompiler.visitors.ScopeAssigner import ScopeAssigner
from pycompiler.visitors.Scope import Scope

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
)
from pycompiler.parser.util import ArgType
from pycompiler.parser.CallExpression import CallExpression, CallExpressionArgument
from pycompiler.parser.SliceExpressionNode import SliceExpressionNode
from pycompiler.parser.ConstantValueExpressionNode import ConstantValueExpressionNode
from pycompiler.parser.ImportStatementNode import ImportStatement
from pycompiler.parser.TypeStatementNode import TypeStatementNode
from pycompiler.parser.ScopeReferences import ParentScopeReference, ChildScopeExported
from pycompiler.parser.ClassDefinitionStatementNode import (
    ClassDefinitionNode,
    ClassDefinitionGenericReference,
)


class TestScopeAssignment(unittest.TestCase):
    def helper(
        self,
        node: AbstractSyntaxTreeNode,
        *children: typing.Callable[[AbstractSyntaxTreeNode], AbstractSyntaxTreeNode],
    ):
        scope = Scope()
        visitor = ScopeAssigner(scope)
        visitor.visit_any(node)
        self.assertEqual(node.scope, scope, "base scope")

        for i, child in enumerate(children):
            with self.subTest(f"child scope {i}"):
                self.assertEqual(child(node).scope, scope)

    def test_name_access(self):
        self.helper(NameAccessNode("test"))

    def test_assignment(self):
        self.helper(
            AssignmentExpressionNode(
                [
                    NameAccessNode("target"),
                ],
                NameAccessNode("source"),
            ),
            lambda node: node.targets[0],
            lambda node: node.base,
        )

    def test_attribute_access(self):
        self.helper(
            AttributeAccessExpressionNode(
                NameAccessNode("inner"),
                "attr",
            ),
            lambda node: node.base,
        )

    def test_subscription_access(self):
        self.helper(
            SubscriptionAccessExpressionNode(
                NameAccessNode("inner"),
                NameAccessNode("index"),
            ),
            lambda node: node.base,
            lambda node: node.inner,
        )

    def test_function_definition(self):
        self.helper(
            FunctionDefinitionNode(
                "test",
                None,
                [
                    FunctionDefinitionArg(ArgType.NORMAL, "a"),
                ],
                [
                    NameAccessNode("test"),
                ],
            ),
            # lambda node: node.parameters[0], # subscope
            # lambda node: node.body[0],  # subscope
        )

    def test_generic_reference(self):
        self.helper(FunctionDefinitionGenericReference("test", 0))

    def test_parameter_reference(self):
        self.helper(
            FunctionDefinitionArgReference(FunctionDefinitionArg(ArgType.NORMAL, "tst"))
        )

    def test_parameter(self):
        self.helper(
            FunctionDefinitionArg(ArgType.KEYWORD, "test", NameAccessNode("test")),
            lambda node: node.default_value,
        )

    def test_call_expression(self):
        self.helper(
            CallExpression(
                NameAccessNode("test"),
                [CallExpressionArgument(ArgType.NORMAL, NameAccessNode("test"))],
            ),
            lambda node: node.base,
            lambda node: node.args[0],
        )

    def test_call_parameter(self):
        self.helper(
            CallExpressionArgument(ArgType.NORMAL, NameAccessNode("test")),
            lambda node: node.expr,
        )

    def test_slice_expression(self):
        self.helper(
            SliceExpressionNode(
                NameAccessNode("start"), NameAccessNode("stop"), NameAccessNode("step")
            ),
            lambda node: node.start,
            lambda node: node.stop,
            lambda node: node.step,
        )

    def test_constant_value(self):
        self.helper(ConstantValueExpressionNode(10))

    def test_import(self):
        self.helper(ImportStatement("test"))

    def test_type_statement(self):
        self.helper(
            TypeStatementNode(NameAccessNode("lhs"), NameAccessNode("rhs")),
            # lambda node: node.base_type,
            # lambda node: node.real_type,
        )

    def test_parent_scope_reference(self):
        self.helper(ParentScopeReference("test"))

    def test_child_exposed_reference(self):
        self.helper(ChildScopeExported("test"))

    def test_class_definition(self):
        self.helper(
            ClassDefinitionNode(
                "test",
                None,
                [NameAccessNode("parent")],
                [NameAccessNode("body")],
            ),
            lambda node: node.parent_references[0],
            # lambda node: node.body[0],
        )
