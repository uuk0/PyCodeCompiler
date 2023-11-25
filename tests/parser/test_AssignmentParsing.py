from unittest import TestCase

from pycompiler.parser.Parser import Parser
from pycompiler.parser.NameAccessNode import NameAccessNode, NameWriteAccessNode
from pycompiler.parser.AssignmentExpressionNode import AssignmentExpressionNode


class TestAssignmentParsing(TestCase):
    def helper(self, code: str, expected: AssignmentExpressionNode):
        with self.subTest("direct"):
            parser = Parser(code)
            self.assertEqual(expected, parser.try_parse_assignment())

        with self.subTest("line"):
            parser = Parser(code)
            self.assertEqual(expected, parser.try_parse_code_line_obj())

        with self.subTest("code block"):
            parser = Parser(code)
            self.assertEqual([expected], parser.parse_code_block())

        with self.subTest("copy equals original"):
            parser = Parser(code)
            expr = parser.try_parse_assignment()
            self.assertEqual(expr, expr.copy())
            self.assertIsNot(expr, expr.copy())

    def test_error_missing_rhs(self):
        self.assertRaises(SyntaxError, lambda: Parser("test =").try_parse_assignment())

    def test_error_missing_rhs_two_lhs(self):
        self.assertRaises(
            SyntaxError, lambda: Parser("test = test2 =").try_parse_assignment()
        )

    def test_error_invalid_continue(self):
        self.assertRaises(
            SyntaxError, lambda: Parser("test = .").try_parse_assignment()
        )

    def test_basic(self):
        self.helper(
            "test = test2",
            AssignmentExpressionNode(
                [NameWriteAccessNode("test")], NameAccessNode("test2")
            ),
        )

    def test_multi_lhs(self):
        self.helper(
            "test = test2 = test3",
            AssignmentExpressionNode(
                [
                    NameWriteAccessNode("test"),
                    NameWriteAccessNode("test2"),
                ],
                NameAccessNode("test3"),
            ),
        )
