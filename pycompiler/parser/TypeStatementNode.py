from __future__ import annotations

import typing

from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeExpressionNode,
    AbstractSyntaxTreeNode,
)
from pycompiler.Lexer import Token, TokenType

if typing.TYPE_CHECKING:
    from pycompiler.parser.Parser import Parser


class TypeStatementNode(AbstractSyntaxTreeNode):
    @classmethod
    def parse_from_parser(cls, parser: Parser) -> TypeStatementNode | None:
        parser.push_state()
        token = parser.lexer.parse_token()

        if (
            token.token_type != TokenType.IDENTIFIER
            or token.text != "type"
            or parser.lexer.get_chars(1) != " "
        ):
            parser.rollback_state()
            return

        lhs = parser.try_parse_type_annotation(is_lhs=False)
        if lhs is None:
            parser.rollback_state()
            return

        eq_sign = parser.lexer.parse_token()
        if eq_sign.token_type != TokenType.EQUAL_SIGN:
            parser.rollback_state()
            return

        rhs = parser.try_parse_type_annotation()
        if rhs is None:
            parser.rollback_state()
            return

        return cls(
            lhs,
            rhs,
        )

    def __init__(
        self,
        base_type: AbstractSyntaxTreeExpressionNode,
        real_type: AbstractSyntaxTreeExpressionNode,
    ):
        super().__init__()
        self.base_type = base_type
        self.real_type = real_type

    def get_tokens(self) -> typing.List[Token]:
        return self.base_type.get_tokens() + self.real_type.get_tokens()

    def __repr__(self):
        return f"TYPE({self.base_type} := {self.real_type})"

    def __eq__(self, other: TypeStatementNode):
        return (
            type(other) is TypeStatementNode
            and self.base_type == other.base_type
            and self.real_type == other.real_type
        )

    def copy(self) -> TypeStatementNode:
        return TypeStatementNode(
            self.base_type.copy(),
            self.real_type.copy(),
        )
