from unittest import TestCase

from pycompiler.parser.Parser import Parser
from pycompiler.parser.NameAccessNode import NameAccessNode
from pycompiler.parser.CallExpression import CallExpression, CallExpressionArgument
from pycompiler.parser.util import ArgType


class TestAssignmentParsing(TestCase):
    def test_expression(self):
        parser = Parser("test()")
        self.assertEqual(
            parser.try_parse_expression(),
            CallExpression(NameAccessNode("test"), []),
        )

    def test_code_line_expression(self):
        parser = Parser("test()")
        self.assertEqual(
            parser.try_parse_code_line_obj(),
            CallExpression(NameAccessNode("test"), []),
        )

    def test_code_block_expression(self):
        parser = Parser("test()")
        self.assertEqual(
            parser.parse_code_block(),
            [CallExpression(NameAccessNode("test"), [])],
        )

    def test_expression_arg(self):
        parser = Parser("test(a)")
        self.assertEqual(
            parser.try_parse_expression(),
            CallExpression(
                NameAccessNode("test"),
                [CallExpressionArgument(ArgType.NORMAL, NameAccessNode("a"))],
            ),
        )

    def test_expression_arg_trailing(self):
        parser = Parser("test(a,)")
        self.assertEqual(
            parser.try_parse_expression(),
            CallExpression(
                NameAccessNode("test"),
                [CallExpressionArgument(ArgType.NORMAL, NameAccessNode("a"))],
            ),
        )

    def test_expression_arg_multi(self):
        parser = Parser("test(a, b)")
        self.assertEqual(
            parser.try_parse_expression(),
            CallExpression(
                NameAccessNode("test"),
                [
                    CallExpressionArgument(ArgType.NORMAL, NameAccessNode("a")),
                    CallExpressionArgument(ArgType.NORMAL, NameAccessNode("b")),
                ],
            ),
        )

    def test_expression_arg_multi_trailing(self):
        parser = Parser("test(a, b,)")
        self.assertEqual(
            parser.try_parse_expression(),
            CallExpression(
                NameAccessNode("test"),
                [
                    CallExpressionArgument(ArgType.NORMAL, NameAccessNode("a")),
                    CallExpressionArgument(ArgType.NORMAL, NameAccessNode("b")),
                ],
            ),
        )

    def test_expression_keyword(self):
        parser = Parser("test(a=b)")
        self.assertEqual(
            parser.try_parse_expression(),
            CallExpression(
                NameAccessNode("test"),
                [CallExpressionArgument(ArgType.KEYWORD, NameAccessNode("b"), "a")],
            ),
        )

    def test_expression_star(self):
        parser = Parser("test(*a)")
        self.assertEqual(
            parser.try_parse_expression(),
            CallExpression(
                NameAccessNode("test"),
                [CallExpressionArgument(ArgType.STAR, NameAccessNode("a"))],
            ),
        )

    def test_expression_star_star(self):
        parser = Parser("test(**a)")
        self.assertEqual(
            parser.try_parse_expression(),
            CallExpression(
                NameAccessNode("test"),
                [CallExpressionArgument(ArgType.STAR_STAR, NameAccessNode("a"))],
            ),
        )
