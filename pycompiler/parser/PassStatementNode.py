from __future__ import annotations

import typing

from pycompiler.Lexer import Token, TokenType
from pycompiler.emitter.CodeBuilder import CodeBuilder
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeNode,
)

if typing.TYPE_CHECKING:
    from pycompiler.parser.Parser import Parser


class PassStatement(AbstractSyntaxTreeNode):
    @classmethod
    def try_parse_from_parser(cls, parser: Parser) -> PassStatement | None:
        parser.push_state()

        pass_token = parser.lexer.parse_token()

        if pass_token.token_type != TokenType.IDENTIFIER or pass_token.text != "pass":
            parser.rollback_state()
            return
        parser.pop_state()
        return PassStatement(pass_token=pass_token)

    def __init__(self, pass_token: Token = None):
        super().__init__()
        self.pass_token = pass_token

    def get_tokens(self) -> list[Token]:
        return [self.pass_token]

    def __repr__(self):
        return "PASS"

    def __eq__(self, other: PassStatement):
        return type(other) is PassStatement

    def copy(self) -> PassStatement:
        return PassStatement(self.pass_token)

    def push_code(self, builder: CodeBuilder) -> CodeBuilder.Source:
        pass
