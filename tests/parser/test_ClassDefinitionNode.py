from __future__ import annotations
import unittest

from pycompiler.parser.Parser import Parser
from pycompiler.parser.ClassDefinitionStatementNode import ClassDefinitionNode
from pycompiler.parser.NameAccessNode import NameAccessNode


class TestClassDefinition(unittest.TestCase):
    def helper(self, code: str, expected: ClassDefinitionNode):
        parser = Parser(code)
        self.assertEqual(parser.try_parse_code_line_obj(), expected)
        parser = Parser(code)
        self.assertEqual(parser.parse_code_block(), [expected])

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
