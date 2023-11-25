from __future__ import annotations

import typing

from pycompiler.Lexer import Token, TokenType
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeNode,
)

if typing.TYPE_CHECKING:
    from pycompiler.parser.Parser import Parser


class ContinueStatement(AbstractSyntaxTreeNode):
    @classmethod
    def try_parse_from_parser(cls, parser: Parser) -> ContinueStatement | None:
        parser.push_state()

        continue_token = parser.lexer.parse_token()

        if (
            continue_token is None
            or continue_token.token_type != TokenType.IDENTIFIER
            or continue_token.text != "continue"
        ):
            parser.rollback_state()
            return

        parser.pop_state()
        return ContinueStatement(continue_token=continue_token)

    def __init__(self, continue_token: Token = None):
        super().__init__()
        self.continue_token = continue_token
        self.surrounding_code_block = None  # where to break to

    def get_tokens(self) -> list[Token]:
        return [self.continue_token]

    def __repr__(self):
        return "CONTINUE"

    def __eq__(self, other: ContinueStatement):
        return type(other) is ContinueStatement

    def copy(self) -> ContinueStatement:
        return ContinueStatement(self.continue_token)

    def push_code(self, builder: CodeBuilder) -> CodeBuilder.Source:
        raise RuntimeError("not implemented")
