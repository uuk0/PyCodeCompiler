from unittest import TestCase
from pycompiler import Parser, Lexer, TypeResolver


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
        visitor = TypeResolver.ScopeGeneratorVisitor(scope)

        # sourcery skip: no-loop-in-tests
        for item in expr:
            visitor.visit_any(item)

        self.assertEqual({"test", "a"}, scope.variable_name_stack)

        visitor = TypeResolver.LocalNameValidator()
        try:
            # sourcery skip: no-loop-in-tests
            for item in expr:
                visitor.visit_any(item)
        except NameError:
            pass
        else:
            self.fail()

