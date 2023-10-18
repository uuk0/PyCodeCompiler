from __future__ import annotations
import typing

from pycompiler.Lexer import Token, TokenType
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeNode,
    AbstractSyntaxTreeExpressionNode,
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

    def get_tokens(self) -> typing.List[Token]:
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
                        parser.rollback_state()
                        parser.lexer.raise_positioned_syntax_error(
                            "expected ',' or ')' after <keyword parameter>"
                        )

                    closing_bracket = token
                    parser.pop_state()
                    break

            if token.token_type == TokenType.STAR:
                parser.pop_state()
                parser.push_state()
                next_token = parser.lexer.parse_token()

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
                parser.rollback_state()
                parser.lexer.raise_positioned_syntax_error(
                    "expected ',' or ')' after <keyword parameter>"
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
        args: typing.List[CallExpressionArgument],
        brackets: typing.Tuple[Token, Token] = None,
        commas: typing.List[Token] = None,
    ):
        super().__init__()
        self.base = base
        self.args = args
        self.brackets = brackets or (None, None)
        self.commas = commas or []

    def get_tokens(self) -> typing.List[Token]:
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
