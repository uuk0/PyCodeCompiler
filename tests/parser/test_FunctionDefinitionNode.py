from unittest import TestCase

from pycompiler.parser.Parser import Parser
from pycompiler.parser.NameAccessNode import NameAccessNode
from pycompiler.parser.FunctionDefinitionNode import (
    FunctionDefinitionNode,
    FunctionDefinitionArg,
)
from pycompiler.parser.util import ArgType


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

    def test_generic(self):
        parser = Parser("def test[a]():\n    b")
        self.assertEqual(
            parser.parse_code_block(),
            [
                FunctionDefinitionNode(
                    "test",
                    ["a"],
                    None,
                    [
                        NameAccessNode("b"),
                    ],
                ),
            ],
        )

    def test_generic_trailing(self):
        parser = Parser("def test[a,]():\n    b")
        self.assertEqual(
            parser.parse_code_block(),
            [
                FunctionDefinitionNode(
                    "test",
                    ["a"],
                    None,
                    [
                        NameAccessNode("b"),
                    ],
                ),
            ],
        )

    def test_generic_multi(self):
        parser = Parser("def test[a, c]():\n    b")
        self.assertEqual(
            parser.parse_code_block(),
            [
                FunctionDefinitionNode(
                    "test",
                    ["a", "c"],
                    None,
                    [
                        NameAccessNode("b"),
                    ],
                ),
            ],
        )

    def test_generic_multi_trailing(self):
        parser = Parser("def test[a, c, ]():\n    b")
        self.assertEqual(
            parser.parse_code_block(),
            [
                FunctionDefinitionNode(
                    "test",
                    ["a", "c"],
                    None,
                    [
                        NameAccessNode("b"),
                    ],
                ),
            ],
        )

    def test_parameter(self):
        parser = Parser("def test(a):\n    b")
        self.assertEqual(
            parser.parse_code_block(),
            [
                FunctionDefinitionNode(
                    "test",
                    None,
                    [
                        FunctionDefinitionArg(
                            ArgType.NORMAL,
                            "a",
                        ),
                    ],
                    [
                        NameAccessNode("b"),
                    ],
                ),
            ],
        )

    def test_parameter_trailing(self):
        parser = Parser("def test(a,):\n    b")
        self.assertEqual(
            parser.parse_code_block(),
            [
                FunctionDefinitionNode(
                    "test",
                    None,
                    [
                        FunctionDefinitionArg(
                            ArgType.NORMAL,
                            "a",
                        ),
                    ],
                    [
                        NameAccessNode("b"),
                    ],
                ),
            ],
        )

    def test_parameter_multi(self):
        parser = Parser("def test(a, b):\n    b")
        self.assertEqual(
            parser.parse_code_block(),
            [
                FunctionDefinitionNode(
                    "test",
                    None,
                    [
                        FunctionDefinitionArg(
                            ArgType.NORMAL,
                            "a",
                        ),
                        FunctionDefinitionArg(
                            ArgType.NORMAL,
                            "b",
                        ),
                    ],
                    [
                        NameAccessNode("b"),
                    ],
                ),
            ],
        )

    def test_parameter_multi_trailing(self):
        parser = Parser("def test(a, b,):\n    b")
        self.assertEqual(
            parser.parse_code_block(),
            [
                FunctionDefinitionNode(
                    "test",
                    None,
                    [
                        FunctionDefinitionArg(
                            ArgType.NORMAL,
                            "a",
                        ),
                        FunctionDefinitionArg(
                            ArgType.NORMAL,
                            "b",
                        ),
                    ],
                    [
                        NameAccessNode("b"),
                    ],
                ),
            ],
        )

    def test_generic_and_parameter(self):
        parser = Parser("def test[c](a):\n    b")
        self.assertEqual(
            parser.parse_code_block(),
            [
                FunctionDefinitionNode(
                    "test",
                    ["c"],
                    [
                        FunctionDefinitionArg(
                            ArgType.NORMAL,
                            "a",
                        ),
                    ],
                    [
                        NameAccessNode("b"),
                    ],
                ),
            ],
        )

    def test_parameter_keyword(self):
        parser = Parser("def test(a=c):\n    b")
        self.assertEqual(
            parser.parse_code_block(),
            [
                FunctionDefinitionNode(
                    "test",
                    None,
                    [
                        FunctionDefinitionArg(
                            ArgType.KEYWORD,
                            "a",
                            NameAccessNode("c"),
                        ),
                    ],
                    [
                        NameAccessNode("b"),
                    ],
                ),
            ],
        )

    def test_parameter_star(self):
        parser = Parser("def test(*a):\n    b")
        self.assertEqual(
            parser.parse_code_block(),
            [
                FunctionDefinitionNode(
                    "test",
                    None,
                    [
                        FunctionDefinitionArg(
                            ArgType.STAR,
                            "a",
                        ),
                    ],
                    [
                        NameAccessNode("b"),
                    ],
                ),
            ],
        )

    def test_parameter_star_star(self):
        parser = Parser("def test(**a):\n    b")
        self.assertEqual(
            parser.parse_code_block(),
            [
                FunctionDefinitionNode(
                    "test",
                    None,
                    [
                        FunctionDefinitionArg(
                            ArgType.STAR_STAR,
                            "a",
                        ),
                    ],
                    [
                        NameAccessNode("b"),
                    ],
                ),
            ],
        )
