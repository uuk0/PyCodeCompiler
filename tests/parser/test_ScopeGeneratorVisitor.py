import typing
from unittest import TestCase
from pycompiler import Parser, Lexer, TypeResolver
from pycompiler.Parser import FunctionDefinitionNode


class TestScopeGeneratorVisitor(TestCase):
    def test_simple(self):
        parser = Parser.Parser("test = hello")
        expr = parser.parse()
        scope = Parser.Scope()
        visitor = TypeResolver.ScopeGeneratorVisitor(scope)

        # sourcery skip: no-loop-in-tests
        for item in expr:
            visitor.visit_any(item)

        self.assertEqual({"test"}, scope.variable_name_stack)

    def test_name_validation_valid(self):
        parser = Parser.Parser("test = 10\na = test")
        expr = parser.parse()

        scope = Parser.Scope()
        visitor = TypeResolver.ScopeGeneratorVisitor(scope)

        # sourcery skip: no-loop-in-tests
        for item in expr:
            visitor.visit_any(item)

        self.assertEqual({"test", "a"}, scope.variable_name_stack)

        visitor = TypeResolver.LocalNameValidator()
        # sourcery skip: no-loop-in-tests
        for item in expr:
            visitor.visit_any(item)

    def test_name_validation_invalid(self):
        parser = Parser.Parser("test = 10\na = test2")
        expr = parser.parse()

        scope = Parser.Scope()
        TypeResolver.ScopeGeneratorVisitor(scope).visit_any_list(expr)

        self.assertEqual({"test", "a"}, scope.variable_name_stack)
        self.assertRaises(NameError, lambda: TypeResolver.LocalNameValidator().visit_any_list(expr))

    def test_function_declaration_exposed(self):
        parser = Parser.Parser("def a(x): return x")
        expr = parser.parse()

        scope = Parser.Scope()
        visitor = TypeResolver.ScopeGeneratorVisitor(scope)
        func_def = typing.cast(FunctionDefinitionNode, expr[0])

        # sourcery skip: no-loop-in-tests
        for item in expr:
            visitor.visit_any(item)

        self.assertEqual({"x"}, func_def.body[0].scope.variable_name_stack)

        TypeResolver.ScopeGeneratorVisitor(scope).visit_any_list(expr)
        TypeResolver.LocalNameValidator().visit_any_list(expr)

    def test_function_declaration_exposed_invalid(self):
        parser = Parser.Parser("def a(x): return b")
        expr = parser.parse()

        scope = Parser.Scope()
        visitor = TypeResolver.ScopeGeneratorVisitor(scope)
        func_def = typing.cast(FunctionDefinitionNode, expr[0])

        # sourcery skip: no-loop-in-tests
        for item in expr:
            visitor.visit_any(item)

        self.assertEqual({"x"}, func_def.body[0].scope.variable_name_stack)

        TypeResolver.ScopeGeneratorVisitor(scope).visit_any_list(expr)
        self.assertRaises(NameError, lambda: TypeResolver.LocalNameValidator().visit_any_list(expr))
