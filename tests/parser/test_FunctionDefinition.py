from unittest import TestCase
from pycompiler import Parser, Lexer, TypeResolver
from pycompiler.Parser import FunctionDefinitionNode, AssignmentExpression, NameAccessExpression, ConstantAccessExpression, PyNewlineNode
from pycompiler.Lexer import TokenType


class TestFunctionDefinition(TestCase):
    def test_simple(self):
        parser = Parser.Parser("def xy(): \n    x = 10")
        expr = parser.parse()
        self.assertEqual([FunctionDefinitionNode(
            TokenType.IDENTIFIER("xy"),
            [],
            [],
            [
                PyNewlineNode(TokenType.NEWLINE("\n")),
                AssignmentExpression(
                    [
                        NameAccessExpression(TokenType.IDENTIFIER("x"))
                    ],
                    TokenType.EQUAL_SIGN("="),
                    ConstantAccessExpression(10),
                ),
            ],
        )], expr)

    def test_simple_singleline(self):
        parser = Parser.Parser("def xy(): x = 10")
        expr = parser.parse()
        self.assertEqual([FunctionDefinitionNode(
            TokenType.IDENTIFIER("xy"),
            [],
            [],
            [
                AssignmentExpression(
                    [
                        NameAccessExpression(TokenType.IDENTIFIER("x"))
                    ],
                    TokenType.EQUAL_SIGN("="),
                    ConstantAccessExpression(10),
                ),
            ],
        )], expr)

    def test_simple_singleline_error(self):
        parser = Parser.Parser("def xy(): x = 10\n    x = 20")
        self.assertRaises(SyntaxError, parser.parse)

    def test_simple_two_inner_lines(self):
        parser = Parser.Parser("def xy(): \n    x = 10\n    y = 20")
        expr = parser.parse()
        self.assertEqual([FunctionDefinitionNode(
            TokenType.IDENTIFIER("xy"),
            [],
            [],
            [
                PyNewlineNode(TokenType.NEWLINE("\n")),
                AssignmentExpression(
                    [
                        NameAccessExpression(TokenType.IDENTIFIER("x"))
                    ],
                    TokenType.EQUAL_SIGN("="),
                    ConstantAccessExpression(10),
                ),
                PyNewlineNode(TokenType.NEWLINE("\n")),
                AssignmentExpression(
                    [
                        NameAccessExpression(TokenType.IDENTIFIER("y"))
                    ],
                    TokenType.EQUAL_SIGN("="),
                    ConstantAccessExpression(20),
                )
            ],
        )], expr)

    def test_generic_simple(self):
        parser = Parser.Parser("def xy[a](): \n    x = 10")
        expr = parser.parse()
        self.assertEqual([FunctionDefinitionNode(
            TokenType.IDENTIFIER("xy"),
            [
                TokenType.IDENTIFIER("a")
            ],
            [],
            [
                PyNewlineNode(TokenType.NEWLINE("\n")),
                AssignmentExpression(
                    [
                        NameAccessExpression(TokenType.IDENTIFIER("x"))
                    ],
                    TokenType.EQUAL_SIGN("="),
                    ConstantAccessExpression(10),
                ),
            ],
        )], expr)

    def test_generic_double(self):
        parser = Parser.Parser("def xy[a, b](): \n    x = 10")
        expr = parser.parse()
        self.assertEqual([FunctionDefinitionNode(
            TokenType.IDENTIFIER("xy"),
            [
                TokenType.IDENTIFIER("a"),
                TokenType.IDENTIFIER("b"),
            ],
            [],
            [
                PyNewlineNode(TokenType.NEWLINE("\n")),
                AssignmentExpression(
                    [
                        NameAccessExpression(TokenType.IDENTIFIER("x"))
                    ],
                    TokenType.EQUAL_SIGN("="),
                    ConstantAccessExpression(10),
                ),
            ],
        )], expr)

    def test_generic_double_trailing(self):
        parser = Parser.Parser("def xy[a, b,](): \n    x = 10")
        expr = parser.parse()
        self.assertEqual([FunctionDefinitionNode(
            TokenType.IDENTIFIER("xy"),
            [
                TokenType.IDENTIFIER("a"),
                TokenType.IDENTIFIER("b"),
            ],
            [],
            [
                PyNewlineNode(TokenType.NEWLINE("\n")),
                AssignmentExpression(
                    [
                        NameAccessExpression(TokenType.IDENTIFIER("x"))
                    ],
                    TokenType.EQUAL_SIGN("="),
                    ConstantAccessExpression(10),
                ),
            ],
        )], expr)

    def test_generic_duplicate(self):
        parser = Parser.Parser("def xy[a, a](): \n    x = 10")
        self.assertRaises(NameError, parser.parse)

    def test_normal_argument(self):
        parser = Parser.Parser("def xy(a): \n    x = 10")
        expr = parser.parse()
        self.assertEqual([FunctionDefinitionNode(
            TokenType.IDENTIFIER("xy"),
            [],
            [
                FunctionDefinitionNode.FunctionDefinitionParameter(
                    TokenType.IDENTIFIER("a"),
                    FunctionDefinitionNode.ParameterType.NORMAL,
                ),
            ],
            [
                PyNewlineNode(TokenType.NEWLINE("\n")),
                AssignmentExpression(
                    [
                        NameAccessExpression(TokenType.IDENTIFIER("x"))
                    ],
                    TokenType.EQUAL_SIGN("="),
                    ConstantAccessExpression(10),
                ),
            ],
        )], expr)

    def test_normal_argument_generic(self):
        parser = Parser.Parser("def xy[b](a): \n    x = 10")
        expr = parser.parse()
        self.assertEqual([FunctionDefinitionNode(
            TokenType.IDENTIFIER("xy"),
            [
                TokenType.IDENTIFIER("b")
            ],
            [
                FunctionDefinitionNode.FunctionDefinitionParameter(
                    TokenType.IDENTIFIER("a"),
                    FunctionDefinitionNode.ParameterType.NORMAL,
                ),
            ],
            [
                PyNewlineNode(TokenType.NEWLINE("\n")),
                AssignmentExpression(
                    [
                        NameAccessExpression(TokenType.IDENTIFIER("x"))
                    ],
                    TokenType.EQUAL_SIGN("="),
                    ConstantAccessExpression(10),
                ),
            ],
        )], expr)

    def test_normal_argument_generic_collision(self):
        parser = Parser.Parser("def xy[a](a): \n    x = 10")
        self.assertRaises(NameError, parser.parse)

    def test_normal_argument_double(self):
        parser = Parser.Parser("def xy(a, b): \n    x = 10")
        expr = parser.parse()
        self.assertEqual([FunctionDefinitionNode(
            TokenType.IDENTIFIER("xy"),
            [],
            [
                FunctionDefinitionNode.FunctionDefinitionParameter(
                    TokenType.IDENTIFIER("a"),
                    FunctionDefinitionNode.ParameterType.NORMAL,
                ),
                FunctionDefinitionNode.FunctionDefinitionParameter(
                    TokenType.IDENTIFIER("b"),
                    FunctionDefinitionNode.ParameterType.NORMAL,
                ),
            ],
            [
                PyNewlineNode(TokenType.NEWLINE("\n")),
                AssignmentExpression(
                    [
                        NameAccessExpression(TokenType.IDENTIFIER("x"))
                    ],
                    TokenType.EQUAL_SIGN("="),
                    ConstantAccessExpression(10),
                ),
            ],
        )], expr)

    def test_star_argument(self):
        parser = Parser.Parser("def xy(*a): \n    x = 10")
        expr = parser.parse()
        self.assertEqual([FunctionDefinitionNode(
            TokenType.IDENTIFIER("xy"),
            [],
            [
                FunctionDefinitionNode.FunctionDefinitionParameter(
                    TokenType.IDENTIFIER("a"),
                    FunctionDefinitionNode.ParameterType.STAR,
                ),
            ],
            [
                PyNewlineNode(TokenType.NEWLINE("\n")),
                AssignmentExpression(
                    [
                        NameAccessExpression(TokenType.IDENTIFIER("x"))
                    ],
                    TokenType.EQUAL_SIGN("="),
                    ConstantAccessExpression(10),
                ),
            ],
        )], expr)

    def test_star_star_argument(self):
        parser = Parser.Parser("def xy(**a): \n    x = 10")
        expr = parser.parse()
        self.assertEqual([FunctionDefinitionNode(
            TokenType.IDENTIFIER("xy"),
            [],
            [
                FunctionDefinitionNode.FunctionDefinitionParameter(
                    TokenType.IDENTIFIER("a"),
                    FunctionDefinitionNode.ParameterType.STAR_STAR,
                ),
            ],
            [
                PyNewlineNode(TokenType.NEWLINE("\n")),
                AssignmentExpression(
                    [
                        NameAccessExpression(TokenType.IDENTIFIER("x"))
                    ],
                    TokenType.EQUAL_SIGN("="),
                    ConstantAccessExpression(10),
                ),
            ],
        )], expr)

    def test_keyword_argument(self):
        parser = Parser.Parser("def xy(a=10): \n    x = 10")
        expr = parser.parse()
        self.assertEqual([FunctionDefinitionNode(
            TokenType.IDENTIFIER("xy"),
            [],
            [
                FunctionDefinitionNode.FunctionDefinitionParameter(
                    TokenType.IDENTIFIER("a"),
                    FunctionDefinitionNode.ParameterType.KEYWORD,
                    default=ConstantAccessExpression(10),
                ),
            ],
            [
                PyNewlineNode(TokenType.NEWLINE("\n")),
                AssignmentExpression(
                    [
                        NameAccessExpression(TokenType.IDENTIFIER("x"))
                    ],
                    TokenType.EQUAL_SIGN("="),
                    ConstantAccessExpression(10),
                ),
            ],
        )], expr)

