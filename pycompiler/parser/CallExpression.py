from __future__ import annotations

import inspect
import typing

from pycompiler.Lexer import Token, TokenType
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeNode,
    AbstractSyntaxTreeExpressionNode,
    ParentAttributeSection,
)
from pycompiler.parser.util import ArgType

if typing.TYPE_CHECKING:
    from pycompiler.parser.Parser import Parser


class CallExpressionArgument(AbstractSyntaxTreeExpressionNode):
    def __init__(
        self,
        arg_type: ArgType,
        expr: AbstractSyntaxTreeExpressionNode,
        keyword: str = None,
        keyword_token: Token = None,
        equal_sign: Token = None,
    ):
        super().__init__()
        self.arg_type = arg_type
        self.expr = expr
        self.keyword = keyword
        self.keyword_token = keyword_token
        self.equal_sign = equal_sign

    def replace_child_with(
        self,
        original: AbstractSyntaxTreeNode,
        new: AbstractSyntaxTreeNode,
        section: ParentAttributeSection,
    ) -> bool:
        if section != ParentAttributeSection.BASE:
            return False

        self.expr = new
        return True

    def update_child_parent_relation(self):
        self.expr.parent = self
        self.expr.parent_section = ParentAttributeSection.BASE
        self.expr.update_child_parent_relation()

    def get_tokens(self) -> list[Token]:
        return [self.keyword_token, self.equal_sign] + self.expr.get_tokens()

    def __repr__(self):
        if self.arg_type == ArgType.NORMAL:
            return repr(self.expr)
        elif self.arg_type == ArgType.STAR:
            return f"*{repr(self.expr)}"
        elif self.arg_type == ArgType.STAR_STAR:
            return f"**{repr(self.expr)}"
        elif self.arg_type == ArgType.KEYWORD:
            return f"{self.keyword} = {repr(self.expr)}"

        raise RuntimeError

    def __eq__(self, other: CallExpressionArgument):
        return (
            type(other) is CallExpressionArgument
            and self.arg_type == other.arg_type
            and self.expr == other.expr
            and self.keyword == other.keyword
        )

    def copy(self) -> AbstractSyntaxTreeNode:
        return CallExpressionArgument(
            self.arg_type,
            self.expr.copy(),
            self.keyword,
            self.keyword_token,
            self.equal_sign,
        )

    def can_be_assignment_target(self) -> bool:
        return True

    def get_type_annotation(self):
        return self.expr.get_data_type()


class CallExpression(AbstractSyntaxTreeExpressionNode):
    @classmethod
    def parse_from_parser(
        cls,
        parser: Parser,
        base: AbstractSyntaxTreeExpressionNode,
        opening_bracket: Token = None,
    ):
        closing_bracket: Token | None = None
        args = []
        commas = []
        while True:
            parser.push_state()
            token = parser.lexer.parse_token()

            if token is None:
                parser.lexer.raise_positioned_syntax_error(
                    "expected ')' or <expression> after '(' or ','"
                )

            if token.token_type == TokenType.CLOSING_ROUND_BRACKET:
                closing_bracket = token
                break

            if token.token_type == TokenType.IDENTIFIER:
                next_token = parser.lexer.parse_token()

                if next_token.token_type == TokenType.EQUAL_SIGN:
                    parser.pop_state()

                    expr = parser.try_parse_expression()

                    if expr is None:
                        parser.lexer.raise_positioned_syntax_error(
                            "expected <expression> after '='"
                        )

                    args.append(
                        CallExpressionArgument(
                            ArgType.KEYWORD,
                            expr,
                            token.text,
                            token,
                            next_token,
                        )
                    )

                    parser.push_state()
                    token = parser.lexer.parse_token()
                    if token.token_type == TokenType.COMMA:
                        commas.append(token)
                        parser.pop_state()
                        continue

                    elif token.token_type != TokenType.CLOSING_ROUND_BRACKET:
                        parser.lexer.raise_positioned_syntax_error_on_token(
                            token, "expected ',' or ')' after <keyword parameter>"
                        )

                    closing_bracket = token
                    parser.pop_state()
                    break

            if token.token_type == TokenType.STAR:
                parser.pop_state()
                parser.push_state()
                next_token = parser.lexer.parse_token()

                if next_token is None:
                    parser.lexer.raise_positioned_syntax_error(
                        "expected <expression> or '*' after '*' in <parameter>"
                    )

                if next_token.token_type == TokenType.STAR:
                    parser.pop_state()
                    expr = parser.try_parse_expression()

                    if expr is None:
                        parser.lexer.raise_positioned_syntax_error(
                            "expected <expression> after '**' in <parameter>"
                        )

                    args.append(
                        CallExpressionArgument(
                            ArgType.STAR_STAR,
                            expr,
                        )
                    )
                else:
                    parser.rollback_state()
                    expr = parser.try_parse_expression()

                    if expr is None:
                        parser.lexer.raise_positioned_syntax_error(
                            "expected <expression> or '*' after '*' in <parameter>"
                        )

                    args.append(
                        CallExpressionArgument(
                            ArgType.STAR,
                            expr,
                        )
                    )

            else:
                parser.rollback_state()
                expr = parser.try_parse_expression()

                if expr is None:
                    parser.lexer.raise_positioned_syntax_error(
                        "expected <expression>, '*' or '**' in <parameter list>"
                    )

                args.append(
                    CallExpressionArgument(
                        ArgType.NORMAL,
                        expr,
                    )
                )

            parser.push_state()
            token = parser.lexer.parse_token()

            if token is None:
                parser.rollback_state()
                parser.lexer.raise_positioned_syntax_error(
                    "expected ',' or ')' after <parameter>, got EOF"
                )

            if token.token_type == TokenType.COMMA:
                commas.append(token)
                parser.pop_state()
                continue

            elif token.token_type != TokenType.CLOSING_ROUND_BRACKET:
                parser.lexer.raise_positioned_syntax_error_on_token(
                    token, "expected ',' or ')' after <keyword parameter>"
                )

            closing_bracket = token
            parser.pop_state()
            break

        return cls(
            base,
            args,
            (opening_bracket, closing_bracket),
            commas,
        )

    def __init__(
        self,
        base: AbstractSyntaxTreeExpressionNode,
        args: list[CallExpressionArgument],
        brackets: tuple[Token, Token] = None,
        commas: list[Token] = None,
    ):
        super().__init__()
        self.base = base
        self.args = args
        self.brackets = brackets or (None, None)
        self.commas = commas or []

    def update_result_type(self):
        # todo: generic reference!
        from pycompiler.parser.FunctionDefinitionStatementNode import (
            StaticFunctionReferenceNode,
        )

        if isinstance(self.base, StaticFunctionReferenceNode):
            self.base.func_def.update_result_type()
            self.result_type = self.base.func_def.return_type

    def replace_child_with(
        self,
        original: AbstractSyntaxTreeNode,
        new: AbstractSyntaxTreeNode,
        section: ParentAttributeSection,
    ) -> bool:
        if section == ParentAttributeSection.BASE:
            self.base = new
            return True

        if section == ParentAttributeSection.PARAMETER:
            for i, arg in enumerate(self.args):
                if arg is original:
                    self.args[i] = new
                    return True

            return False

        return False

    def update_child_parent_relation(self):
        self.base.parent = self
        self.base.parent_section = ParentAttributeSection.BASE
        self.base.update_child_parent_relation()

        for arg in self.args:
            arg.parent = self
            arg.parent_section = ParentAttributeSection.PARAMETER
            arg.update_child_parent_relation()

    def get_tokens(self) -> list[Token]:
        return (
            self.base.get_tokens()
            + list(self.brackets)
            + self.commas
            + sum((param.get_tokens() for param in self.args), [])
        )

    def __repr__(self):
        return f"CALL({self.base}({', '.join(map(repr, self.args))}))"

    def __eq__(self, other: CallExpression):
        return (
            type(other) is CallExpression
            and self.base == other.base
            and self.args == other.args
        )

    def copy(self) -> CallExpression:
        return CallExpression(
            self.base.copy(),
            [arg.copy() for arg in self.args],
            self.brackets,
            self.commas.copy(),
        )

    def get_signature(self) -> inspect.Signature:
        args = []

        for i, param in enumerate(self.args):
            param: CallExpressionArgument

            args.append(
                inspect.Parameter(
                    f":param_{i}",
                    param.arg_type.inspect_name,
                    annotation=param.get_type_annotation(),
                )
                if param.arg_type != ArgType.KEYWORD
                else inspect.Parameter(
                    param.keyword,
                    inspect.Parameter.POSITIONAL_OR_KEYWORD,
                    default=param.expr,
                    annotation=param.get_type_annotation(),
                )
            )

        return inspect.Signature(
            args,
        )
