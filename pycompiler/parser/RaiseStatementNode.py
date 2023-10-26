from __future__ import annotations

import typing

from pycompiler.Lexer import Token, TokenType
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeNode,
    AbstractSyntaxTreeExpressionNode,
    ParentAttributeSection,
)


if typing.TYPE_CHECKING:
    from pycompiler.parser.Parser import Parser


class RaiseStatement(AbstractSyntaxTreeNode):
    CONTINUE_FLOW_AFTER_EXPRESSION = False

    @classmethod
    def try_parse_from_parser(cls, parser: Parser) -> RaiseStatement | None:
        parser.push_state()

        token = parser.lexer.parse_token()

        if token.token_type != TokenType.IDENTIFIER or token.text != "raise":
            parser.rollback_state()
            return
        parser.pop_state()
        expr = parser.try_parse_expression()
        from_expr = None
        from_token = None

        if expr:
            parser.push_state()
            from_token = parser.lexer.parse_token()

            if (
                from_token is None
                or from_token.token_type != TokenType.IDENTIFIER
                or token.text != "from"
            ):
                parser.rollback_state()
                from_token = None
            else:
                parser.pop_state()
                from_expr = parser.try_parse_expression()

                if from_expr is None:
                    parser.lexer.raise_positioned_syntax_error(
                        "expected <expression> after 'raise ... from'"
                    )

        return RaiseStatement(
            expr, from_expr, return_token=token, from_token=from_token
        )

    def __init__(
        self,
        value: AbstractSyntaxTreeExpressionNode,
        from_node: AbstractSyntaxTreeExpressionNode = None,
        return_token: Token = None,
        from_token: Token = None,
    ):
        super().__init__()
        self.value = value
        self.from_node = from_node
        self.return_token = return_token
        self.from_token = from_token

    def replace_child_with(
        self,
        original: AbstractSyntaxTreeNode,
        new: AbstractSyntaxTreeNode,
        section: ParentAttributeSection,
    ) -> bool:
        if section == ParentAttributeSection.LHS and self.value:
            self.value = new
            return True

        if section == ParentAttributeSection.RHS and self.from_node:
            self.from_node = new
            return True

        return False

    def update_child_parent_relation(self):
        if self.value:
            self.value.parent = self
            self.value.parent_section = ParentAttributeSection.LHS
            self.value.update_child_parent_relation()

        if self.from_node:
            self.from_node.parent = self
            self.from_node.parent_section = ParentAttributeSection.RHS
            self.from_node.update_child_parent_relation()

    def get_tokens(self) -> list[Token]:
        return (
            [self.return_token]
            + (self.value.get_tokens() if self.value else [])
            + [self.from_token]
            + (self.from_node.get_tokens() if self.from_node else [])
        )

    def __repr__(self):
        return f"RAISE({self.return_token})"

    def __eq__(self, other: RaiseStatement):
        return (
            type(other) is RaiseStatement
            and self.value == other.value
            and self.from_node == other.from_node
        )

    def copy(self) -> RaiseStatement:
        return RaiseStatement(
            self.value.copy() if self.value else None,
            self.from_node.copy() if self.from_node else None,
            self.return_token,
            self.from_token,
        )
