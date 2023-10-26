from __future__ import annotations
import unittest

from pycompiler.parser.Parser import Parser
from pycompiler.parser.ClassDefinitionStatementNode import ClassDefinitionNode
from pycompiler.parser.NameAccessNode import NameAccessNode


class TestClassDefinition(unittest.TestCase):
    def helper(self, code: str, expected: ClassDefinitionNode):
        with self.subTest("direct"):
            self.assertEqual(
                expected, ClassDefinitionNode.try_parse_from_parser(Parser(code))
            )

        with self.subTest("line"):
            parser = Parser(code)
            self.assertEqual(expected, parser.try_parse_code_line_obj())

        with self.subTest("block"):
            parser = Parser(code)
            self.assertEqual([expected], parser.parse_code_block())

        with self.subTest("copy eq"):
            self.assertEqual(expected, expected.copy())
            self.assertIsNot(expected, expected.copy())

    def test_error_on_missing_name(self):
        self.assertRaises(
            SyntaxError, lambda: Parser("class :").try_parse_code_line_obj()
        )

    def test_missing_closing_generic_bracket(self):
        self.assertRaises(
            SyntaxError, lambda: Parser("class x[t:").try_parse_code_line_obj()
        )

    def test_missing_closing_generic_bracket_eof(self):
        self.assertRaises(
            SyntaxError, lambda: Parser("class x[t").try_parse_code_line_obj()
        )

    def test_missing_closing_round_bracket(self):
        self.assertRaises(
            SyntaxError, lambda: Parser("class x(t:").try_parse_code_line_obj()
        )

    def test_missing_closing_round_bracket_eof(self):
        self.assertRaises(
            SyntaxError, lambda: Parser("class x(t").try_parse_code_line_obj()
        )

    def test_missing_colon(self):
        self.assertRaises(
            SyntaxError, lambda: Parser("class x test").try_parse_code_line_obj()
        )

    def test_missing_colon_eof(self):
        self.assertRaises(
            SyntaxError, lambda: Parser("class x").try_parse_code_line_obj()
        )

    def test_missing_code(self):
        self.assertRaises(
            SyntaxError, lambda: Parser("class x:\ntest").try_parse_code_line_obj()
        )

    def test_basic(self):
        self.helper(
            "class xy: test",
            ClassDefinitionNode("xy", None, None, [NameAccessNode("test")]),
        )

    def test_parent(self):
        self.helper(
            "class xy(parent): test",
            ClassDefinitionNode(
                "xy", None, [NameAccessNode("parent")], [NameAccessNode("test")]
            ),
        )

    def test_parent_trailing(self):
        self.helper(
            "class xy(parent,): test",
            ClassDefinitionNode(
                "xy", None, [NameAccessNode("parent")], [NameAccessNode("test")]
            ),
        )

    def test_parent_double(self):
        self.helper(
            "class xy(parent, second): test",
            ClassDefinitionNode(
                "xy",
                None,
                [NameAccessNode("parent"), NameAccessNode("second")],
                [NameAccessNode("test")],
            ),
        )

    def test_parent_double_trailing(self):
        self.helper(
            "class xy(parent, second,): test",
            ClassDefinitionNode(
                "xy",
                None,
                [NameAccessNode("parent"), NameAccessNode("second")],
                [NameAccessNode("test")],
            ),
        )

    def test_generic(self):
        self.helper(
            "class xy[A]: test",
            ClassDefinitionNode("xy", ["A"], None, [NameAccessNode("test")]),
        )

    def test_generic_trailing(self):
        self.helper(
            "class xy[A,]: test",
            ClassDefinitionNode("xy", ["A"], None, [NameAccessNode("test")]),
        )

    def test_generic_double(self):
        self.helper(
            "class xy[A, B]: test",
            ClassDefinitionNode("xy", ["A", "B"], None, [NameAccessNode("test")]),
        )

    def test_generic_double_trailing(self):
        self.helper(
            "class xy[A, B,]: test",
            ClassDefinitionNode("xy", ["A", "B"], None, [NameAccessNode("test")]),
        )

    def test_generic_and_parent(self):
        self.helper(
            "class xy[A](parent): test",
            ClassDefinitionNode(
                "xy", ["A"], [NameAccessNode("parent")], [NameAccessNode("test")]
            ),
        )
