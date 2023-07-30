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

