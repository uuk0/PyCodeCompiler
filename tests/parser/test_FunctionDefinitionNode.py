from unittest import TestCase

from pycompiler.parser.Parser import Parser
from pycompiler.parser.NameAccessNode import NameAccessNode
from pycompiler.parser.FunctionDefinitionNode import (
    FunctionDefinitionNode,
    FunctionDefinitionArg,
)


class TestFunctionDefinition(TestCase):
    def test_code_line_expression(self):
        parser = Parser("def test(): a")
        self.assertEqual(
            parser.try_parse_code_line_obj(),
            FunctionDefinitionNode(
                "test",
                None,
                None,
                [
                    NameAccessNode("a"),
                ],
            ),
        )

    def test_code_block_expression(self):
        parser = Parser("def test(): a")
        self.assertEqual(
            parser.parse_code_block(),
            [
                FunctionDefinitionNode(
                    "test",
                    None,
                    None,
                    [
                        NameAccessNode("a"),
                    ],
                ),
            ],
        )

    def test_code_line_expression_full_block(self):
        parser = Parser("def test():\n    a")
        self.assertEqual(
            parser.try_parse_code_line_obj(),
            FunctionDefinitionNode(
                "test",
                None,
                None,
                [
                    NameAccessNode("a"),
                ],
            ),
        )

    def test_code_block_expression_full_block(self):
        parser = Parser("def test():\n    a")
        self.assertEqual(
            parser.parse_code_block(),
            [
                FunctionDefinitionNode(
                    "test",
                    None,
                    None,
                    [
                        NameAccessNode("a"),
                    ],
                ),
            ],
        )

    def test_code_line_expression_full_block_multi(self):
        parser = Parser("def test():\n    a\n    b")
        self.assertEqual(
            parser.try_parse_code_line_obj(),
            FunctionDefinitionNode(
                "test",
                None,
                None,
                [
                    NameAccessNode("a"),
                    NameAccessNode("b"),
                ],
            ),
        )

    def test_code_block_expression_full_block_multi(self):
        parser = Parser("def test():\n    a\n    b")
        self.assertEqual(
            parser.parse_code_block(),
            [
                FunctionDefinitionNode(
                    "test",
                    None,
                    None,
                    [
                        NameAccessNode("a"),
                        NameAccessNode("b"),
                    ],
                ),
            ],
        )

    def test_code_line_expression_full_block_exit(self):
        parser = Parser("def test():\n    a\nb")
        self.assertEqual(
            parser.try_parse_code_line_obj(),
            FunctionDefinitionNode(
                "test",
                None,
                None,
                [
                    NameAccessNode("a"),
                ],
            ),
        )

    def test_code_block_expression_full_block_exit(self):
        parser = Parser("def test():\n    a\nb")
        self.assertEqual(
            parser.parse_code_block(),
            [
                FunctionDefinitionNode(
                    "test",
                    None,
                    None,
                    [
                        NameAccessNode("a"),
                    ],
                ),
                NameAccessNode("b"),
            ],
        )
