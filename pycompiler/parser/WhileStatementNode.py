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


class WhileStatementNode(AbstractSyntaxTreeNode):
    @classmethod
    def try_parse_from_parser(cls, parser: Parser) -> WhileStatementNode | None:
        parser.push_state()
        while_token = parser.lexer.parse_token()

        if (
            while_token is None
            or while_token.token_type != TokenType.IDENTIFIER
            or while_token.text != "while"
        ):
            parser.rollback_state()
            return

        parser.pop_state()

        condition = parser.try_parse_expression()

        if condition is None:
            parser.lexer.raise_positioned_syntax_error(
                "expected <condition> after 'while'"
            )

        parser.push_state()
        colon = parser.lexer.parse_token()

        if colon.token_type != TokenType.COLON:
            parser.lexer.raise_positioned_syntax_error_on_token(
                colon, "expected ':' after <condition> in 'while'"
            )

        parser.pop_state()
        parser.push_state()
        newline = parser.lexer.parse_token()
        if newline.token_type == TokenType.NEWLINE:
            parser.pop_state()
            body = parser.parse_code_block(parser.indent + 1)

            if not body:
                parser.lexer.throw_positioned_syntax_error(
                    "expected <statement> after <function definition>"
                )
        else:
            parser.rollback_state()
            body = [parser.try_parse_code_line_obj()]

            if body[0] is None:
                parser.lexer.throw_positioned_syntax_error(
                    "expected <statement> after <function definition>"
                )

        return cls(
            condition,
            body,
            while_token,
            colon,
        )

    def __init__(
        self,
        condition: AbstractSyntaxTreeExpressionNode,
        body: list[AbstractSyntaxTreeNode],
        while_token: Token = None,
        colon_token: Token = None,
    ):
        super().__init__()
        self.condition = condition
        self.body = body
        self.while_token = while_token
        self.colon_token = colon_token

    def replace_child_with(
        self,
        original: AbstractSyntaxTreeNode,
        new: AbstractSyntaxTreeNode,
        section: ParentAttributeSection,
    ) -> bool:
        if section == ParentAttributeSection.CONDITION:
            self.condition = new
            return True

        if section == ParentAttributeSection.BODY:
            for i, node in enumerate(self.body):
                if node is original:
                    self.body[i] = new
                    return True

            return False

        return False

    def update_child_parent_relation(self):
        self.condition.parent = self
        self.condition.parent_section = ParentAttributeSection.CONDITION
        self.condition.update_child_parent_relation()

        for node in self.body:
            node.parent = self
            node.parent_section = ParentAttributeSection.BODY
            node.update_child_parent_relation()

    def get_tokens(self) -> list[Token]:
        return (
            [self.while_token]
            + self.condition.get_tokens()
            + [self.colon_token]
            + sum((node.get_tokens() for node in self.body), [])
        )

    def __repr__(self):
        return f"WHILE({self.condition} : {self.body})"

    def __eq__(self, other: WhileStatementNode):
        return (
            type(other) is WhileStatementNode
            and self.condition == other.condition
            and self.body == other.body
        )

    def copy(self) -> WhileStatementNode:
        return WhileStatementNode(
            self.condition.copy(),
            [node.copy() for node in self.body],
            self.while_token,
            self.colon_token,
        )

    def push_code(self, builder: CodeBuilder):
        condition = self.condition.push_code(builder)
        inner_builder = builder.push_while_loop(condition)

        for node in self.body:
            inner_builder.push_evaluate_value(node.push_code(inner_builder))

        # todo: else block
