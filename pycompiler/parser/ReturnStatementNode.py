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


class ReturnStatement(AbstractSyntaxTreeNode):
    CONTINUE_FLOW_AFTER_EXPRESSION = False

    @classmethod
    def try_parse_from_parser(cls, parser: Parser) -> ReturnStatement | None:
        parser.push_state()

        token = parser.lexer.parse_token()

        if token.token_type != TokenType.IDENTIFIER or token.text != "return":
            parser.rollback_state()
            return
        parser.pop_state()
        expr = parser.try_parse_expression()
        return ReturnStatement(expr, return_token=token)

    def __init__(
        self, value: AbstractSyntaxTreeExpressionNode, return_token: Token = None
    ):
        super().__init__()
        self.value = value
        self.return_token = return_token

    def replace_child_with(
        self,
        original: AbstractSyntaxTreeNode,
        new: AbstractSyntaxTreeNode,
        section: ParentAttributeSection,
    ) -> bool:
        if section != ParentAttributeSection.LHS or self.value is None:
            return False

        self.value = new
        return True

    def update_child_parent_relation(self):
        if self.value:
            self.value.parent = self
            self.value.parent_section = ParentAttributeSection.LHS
            self.value.update_child_parent_relation()

    def get_tokens(self) -> list[Token]:
        return [self.return_token] + (self.value.get_tokens() if self.value else None)

    def __repr__(self):
        return f"RETURN({self.return_token})"

    def __eq__(self, other: ReturnStatement):
        return type(other) is ReturnStatement and self.value == other.value

    def copy(self) -> ReturnStatement:
        return ReturnStatement(
            self.value.copy() if self.value else None, self.return_token
        )

    def push_code(self, builder: CodeBuilder):
        value = self.value.push_code(builder) if self.value else builder.PY_NONE
        builder.push_return_statement(value)
