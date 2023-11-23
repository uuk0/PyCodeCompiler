from __future__ import annotations

import typing

from pycompiler.Lexer import Token, TokenType
from pycompiler.emitter.CodeBuilder import CodeBuilder
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeNode,
)

if typing.TYPE_CHECKING:
    from pycompiler.parser.Parser import Parser


class BreakStatement(AbstractSyntaxTreeNode):
    @classmethod
    def try_parse_from_parser(cls, parser: Parser) -> BreakStatement | None:
        parser.push_state()

        break_token = parser.lexer.parse_token()

        if (
            break_token is None
            or break_token.token_type != TokenType.IDENTIFIER
            or break_token.text != "break"
        ):
            parser.rollback_state()
            return

        parser.pop_state()
        return BreakStatement(break_token=break_token)

    def __init__(self, break_token: Token = None):
        super().__init__()
        self.break_token = break_token
        self.surrounding_code_block = None  # where to break to

    def get_tokens(self) -> list[Token]:
        return [self.break_token]

    def __repr__(self):
        return "BREAK"

    def __eq__(self, other: BreakStatement):
        return type(other) is BreakStatement

    def copy(self) -> BreakStatement:
        return BreakStatement(self.break_token)

    def push_code(self, builder: CodeBuilder) -> CodeBuilder.Source:
        raise RuntimeError("not implemented")
