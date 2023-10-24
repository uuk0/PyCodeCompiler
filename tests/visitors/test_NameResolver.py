from __future__ import annotations

import unittest

from pycompiler.parser.NameAccessNode import (
    NameWriteAccessNode,
    NameAccessNode,
    NameAccessLocalNode,
)
from pycompiler.parser.AssignmentExpressionNode import AssignmentExpressionNode
from pycompiler.parser.TypeStatementNode import (
    TypeStatementNode,
    StaticTypeDefinitionReference,
)
from pycompiler.parser.FunctionDefinitionStatementNode import (
    FunctionDefinitionNode,
    StaticFunctionReferenceNode,
    FunctionDefinitionArgReference,
    FunctionDefinitionArg,
    FunctionDefinitionGenericReference,
)
from pycompiler.parser.util import ArgType
from pycompiler.parser.ClassDefinitionStatementNode import (
    ClassDefinitionNode,
    StaticClassReferenceNode,
    ClassDefinitionGenericReference,
)

from pycompiler.visitors.NameResolver import NameResolver
from pycompiler.visitors.ScopeAssigner import ScopeAssigner
from pycompiler.visitors.Scope import Scope


class TestNameResolver(unittest.TestCase):
    def test_assignment(self):
        scope = Scope()
        node = AssignmentExpressionNode(
            [
                access := NameWriteAccessNode("test"),
            ],
            NameAccessNode("test"),
        )
        node.update_child_parent_relation()
        ScopeAssigner(scope).visit_any(node)
        NameResolver().visit_any(node)

        self.assertEqual(NameAccessLocalNode("test"), node.base)

    def test_type_statement(self):
        scope = Scope()
        node = TypeStatementNode(NameAccessNode("test"), NameAccessNode("test"))
        node.update_child_parent_relation()
        ScopeAssigner(scope).visit_any(node)
        NameResolver().visit_any(node)
        self.assertEqual(node.real_type, StaticTypeDefinitionReference(node))

    def test_function_definition(self):
        scope = Scope()
        node = FunctionDefinitionNode("test", [], [], [NameAccessNode("test")])
        node.update_child_parent_relation()
        ScopeAssigner(scope).visit_any(node)
        NameResolver().visit_any(node)
        self.assertEqual(node.body[0], StaticFunctionReferenceNode(node))

    def test_function_definition_arg_reference(self):
        scope = Scope()
        node = FunctionDefinitionNode(
            "test",
            [],
            [arg := FunctionDefinitionArg(ArgType.NORMAL, "arg")],
            [NameAccessNode("arg")],
        )
        node.update_child_parent_relation()
        ScopeAssigner(scope).visit_any(node)
        NameResolver().visit_any(node)
        self.assertEqual(node.body[0], FunctionDefinitionArgReference(arg))

    def test_function_generic_reference(self):
        scope = Scope()
        node = FunctionDefinitionNode("test", ["gen"], [], [NameAccessNode("gen")])
        node.update_child_parent_relation()
        ScopeAssigner(scope).visit_any(node)
        NameResolver().visit_any(node)
        self.assertEqual(node.body[0], FunctionDefinitionGenericReference("gen", 0))

    def test_class_definition(self):
        scope = Scope()
        node = ClassDefinitionNode("test", [], [], [NameAccessNode("test")])
        node.update_child_parent_relation()
        ScopeAssigner(scope).visit_any(node)
        NameResolver().visit_any(node)
        self.assertEqual(node.body[0], StaticClassReferenceNode(node))

    def test_class_definition_generic_reference(self):
        scope = Scope()
        node = ClassDefinitionNode("test", ["gen"], [], [NameAccessNode("gen")])
        node.update_child_parent_relation()
        ScopeAssigner(scope).visit_any(node)
        NameResolver().visit_any(node)
        self.assertEqual(node.body[0], ClassDefinitionGenericReference("gen", 0))
