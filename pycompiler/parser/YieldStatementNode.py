from __future__ import annotations

import typing

from pycompiler.Lexer import Token, TokenType
from pycompiler.emitter.CodeBuilder import CodeBuilder
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeNode,
    AbstractSyntaxTreeExpressionNode,
    ParentAttributeSection,
)

if typing.TYPE_CHECKING:
    from pycompiler.parser.Parser import Parser


class YieldStatement(AbstractSyntaxTreeNode):
    @classmethod
    def try_parse_from_parser(cls, parser: Parser) -> YieldStatement | None:
        parser.push_state()

        token = parser.lexer.parse_token()

        if token.token_type != TokenType.IDENTIFIER or token.text != "yield":
            parser.rollback_state()
            return

        parser.pop_state()
        parser.push_state()
        is_yield_from = False

        from_token = parser.lexer.parse_token()
        if (
            from_token is None
            or from_token.token_type != TokenType.IDENTIFIER
            or from_token.text != "from"
        ):
            parser.rollback_state()
        else:
            parser.push_state()
            is_yield_from = True

        expr = parser.try_parse_expression()
        return YieldStatement(expr, return_token=token, is_yield_from=is_yield_from)

    def __init__(
        self,
        value: AbstractSyntaxTreeExpressionNode,
        return_token: Token = None,
        is_yield_from=False,
    ):
        super().__init__()
        self.value = value
        self.return_token = return_token
        self.is_yield_from = is_yield_from

    def replace_child_with(
        self,
        original: AbstractSyntaxTreeNode,
        new: AbstractSyntaxTreeNode,
        section: ParentAttributeSection,
    ) -> bool:
        if section != ParentAttributeSection.LHS:
            return False

        self.value = new
        return True

    def update_child_parent_relation(self):
        self.value.parent = self
        self.value.parent_section = ParentAttributeSection.LHS
        self.value.update_child_parent_relation()

    def get_tokens(self) -> list[Token]:
        return [self.return_token] + (self.value.get_tokens() if self.value else None)

    def __repr__(self):
        return f"YIELD{'-FROM' if self.is_yield_from else 'YIELD'}({self.return_token})"

    def __eq__(self, other: YieldStatement):
        return (
            type(other) is YieldStatement
            and self.value == other.value
            and self.is_yield_from is other.is_yield_from
        )

    def copy(self) -> YieldStatement:
        return YieldStatement(self.value.copy(), self.return_token, self.is_yield_from)

    def push_code(self, builder: CodeBuilder) -> CodeBuilder.Source:
        raise RuntimeError("not implemented!")
