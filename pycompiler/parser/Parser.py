from __future__ import annotations

import typing

from pycompiler.Lexer import Lexer, Token, TokenType
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeNode,
    AbstractSyntaxTreeExpressionNode,
)
from pycompiler.parser.NameAccessNode import NameAccessNode, NameWriteAccessNode
from pycompiler.parser.AssignmentExpressionNode import AssignmentExpressionNode
from pycompiler.parser.AttributeAccessExpressionNode import (
    AttributeAccessExpressionNode,
)
from pycompiler.parser.SubscriptionAccessExpressionNode import (
    SubscriptionAccessExpressionNode,
)
from pycompiler.parser.FunctionDefinitionStatementNode import FunctionDefinitionNode
from pycompiler.parser.CallExpression import CallExpression
from pycompiler.parser.SliceExpressionNode import SliceExpressionNode
from pycompiler.parser.ConstantValueExpressionNode import ConstantValueExpressionNode
from pycompiler.parser.ImportStatementNode import ImportStatement
from pycompiler.parser.TypeStatementNode import TypeStatementNode
from pycompiler.parser.ClassDefinitionStatementNode import ClassDefinitionNode
from pycompiler.parser.WhileStatementNode import WhileStatementNode


class Parser:
    def __init__(self, code: str, filename: str = None):
        self.code = code
        self.lexer = Lexer(code, filename=filename)
        self.indent = 0

    def push_state(self):
        self.lexer.push_state()

    def pop_state(self):
        self.lexer.pop_state()

    def rollback_state(self):
        self.lexer.rollback_state()

    def parse_code_block(
        self, expected_indent=0
    ) -> typing.List[AbstractSyntaxTreeNode]:
        old_indent = self.indent
        self.indent = expected_indent
        result = []

        while True:
            expr = self.try_parse_code_line_obj()

            if expr is None:
                break

            result.append(expr)

            self.push_state()
            next_token = self.lexer.parse_token()
            if next_token is None:
                self.rollback_state()
                break

            if next_token.token_type == TokenType.SEMICOLON:
                self.pop_state()
                continue

            elif next_token.token_type != TokenType.NEWLINE:
                self.lexer.raise_positioned_syntax_error(
                    "expected ';' or NEWLINE after <expression>"
                )

            self.pop_state()
            self.push_state()

            exit_block = False

            while True:
                self.push_state()

                if not all(
                    self.lexer.parse_indent_block() for _ in range(expected_indent)
                ):
                    next_token = self.lexer.parse_token()

                    if next_token.token_type == TokenType.NEWLINE:
                        self.pop_state()
                        continue

                    self.rollback_state()
                    self.lexer.increment_cursor(-1)  # \n unrolling
                    exit_block = True
                else:
                    self.pop_state()
                break

            if exit_block:
                break

        self.indent = old_indent

        return result

    def try_parse_code_line_obj(self) -> AbstractSyntaxTreeNode:
        if expr := FunctionDefinitionNode.decode_from_paser(self):
            return expr

        if expr := ClassDefinitionNode.decode_from_paser(self):
            return expr

        if expr := TypeStatementNode.parse_from_parser(self):
            return expr

        if expr := ImportStatement.parse_from_parser(self):
            return expr

        if expr := WhileStatementNode.parse_from_parser(self):
            return expr

        if expr := self.try_parse_assignment():
            return expr

        if expr := self.try_parse_expression():
            return expr

        self.lexer.raise_positioned_syntax_error("expected <code line>")

    def try_parse_assignment(self) -> AssignmentExpressionNode | None:
        self.push_state()
        targets = [tar := self.try_parse_assignment_target()]

        if tar is None:
            self.rollback_state()
            return

        eq_signs = [eq_sign := self.lexer.parse_token()]

        if eq_sign is None or eq_sign.token_type != TokenType.EQUAL_SIGN:
            self.rollback_state()
            return

        while True:
            self.push_state()
            target = self.try_parse_assignment_target()

            if target is None:
                self.rollback_state()
                break

            eq_sign = self.lexer.parse_token()

            if eq_sign is None or eq_sign.token_type != TokenType.EQUAL_SIGN:
                self.rollback_state()
                break

            self.pop_state()

            targets.append(target)
            eq_signs.append(eq_sign)

        expr = self.try_parse_expression()

        if expr is None:
            self.lexer.raise_positioned_syntax_error("expected <expression> after '='")

        self.pop_state()

        return AssignmentExpressionNode(
            targets,
            expr,
            eq_signs,
        )

    def try_parse_expression(self) -> AbstractSyntaxTreeExpressionNode | None:
        if number := self.lexer.try_parse_number():
            base = ConstantValueExpressionNode(number.value, [number])
            base.result_type = int

        elif string := self.lexer.try_parse_string():
            base = ConstantValueExpressionNode(string.value, [string])
            base.result_type = str

        else:
            self.lexer.push_state()
            token = self.lexer.parse_token()

            if token is None:
                return

            if token.token_type == TokenType.IDENTIFIER:
                base = NameAccessNode(token.text, token)
                self.lexer.pop_state()
            else:
                self.lexer.rollback_state()
                return

        while True:
            self.lexer.push_state()
            token = self.lexer.parse_token()

            if token is None:
                self.rollback_state()
                break

            if token.token_type == TokenType.POINT:
                name = self.lexer.parse_token()

                if name is None or name.token_type != TokenType.IDENTIFIER:
                    self.rollback_state()
                    break

                base = AttributeAccessExpressionNode(base, name.text, token, name)

            elif token.token_type == TokenType.OPENING_SQUARE_BRACKET:
                base = self.parse_slice_operator(base, token)

            elif token.token_type == TokenType.OPENING_ROUND_BRACKET:
                base = CallExpression.parse_from_parser(self, base, token)

            else:
                self.rollback_state()
                break

            self.pop_state()

        return base

    def try_parse_assignment_target(self) -> AbstractSyntaxTreeExpressionNode | None:
        self.lexer.push_state()
        token = self.lexer.parse_token()

        if token is None:
            return

        if token.token_type == TokenType.IDENTIFIER:
            base = NameAccessNode(token.text, token)
            self.lexer.pop_state()
        else:
            self.lexer.rollback_state()
            return

        while True:
            self.lexer.push_state()
            token = self.lexer.parse_token()

            if token is None:
                self.lexer.rollback_state()
                break

            if token.token_type == TokenType.POINT:
                name = self.lexer.parse_token()

                if name is None or name.token_type != TokenType.IDENTIFIER:
                    self.rollback_state()
                    break

                base = AttributeAccessExpressionNode(base, name.text, token, name)

            elif token.token_type == TokenType.OPENING_SQUARE_BRACKET:
                base = self.parse_slice_operator(base, token)

            else:
                self.rollback_state()
                break

            self.pop_state()

        # in this case, this is a direct write
        if isinstance(base, NameAccessNode):
            return NameWriteAccessNode(base.name, base.token)

        return base

    def try_parse_type_annotation(
        self, is_lhs=True
    ) -> AbstractSyntaxTreeExpressionNode | None:
        self.lexer.push_state()
        token = self.lexer.parse_token()

        if token is None:
            return

        if token.token_type == TokenType.IDENTIFIER:
            base = NameAccessNode(token.text, token)
            self.lexer.pop_state()
        else:
            self.lexer.rollback_state()
            return

        if is_lhs:
            while True:
                self.lexer.push_state()
                token = self.lexer.parse_token()

                if token is None:
                    self.rollback_state()
                    break

                if token.token_type == TokenType.POINT:
                    name = self.lexer.parse_token()

                    if name is None or name.token_type != TokenType.IDENTIFIER:
                        self.rollback_state()
                        break

                    base = AttributeAccessExpressionNode(base, name.text, token, name)

                else:
                    self.rollback_state()
                    break

                self.pop_state()

        self.push_state()
        token = self.lexer.parse_token()

        if token and token.token_type == TokenType.OPENING_SQUARE_BRACKET:
            # todo: this is not the correct code; only identifiers are allowed
            #   (and if is_lhs is False, also <identifier>: <type annotation>)
            self.lexer.pop_state()
            base = self.parse_slice_operator(base, token)
        else:
            self.lexer.rollback_state()

        return base

    def parse_slice_operator(
        self, base: AbstractSyntaxTreeExpressionNode, opening_bracket: Token
    ) -> SubscriptionAccessExpressionNode:
        inner_expr = self.try_parse_expression()

        self.push_state()
        token = self.lexer.parse_token()

        if token.token_type != TokenType.COLON:
            self.rollback_state()
            if inner_expr is None:
                self.lexer.raise_positioned_syntax_error(
                    "expected <expression> or ':' after '['"
                )
        else:
            self.pop_state()
            middle_expr = self.try_parse_expression()

            self.push_state()
            other_token = self.lexer.parse_token()

            if other_token.token_type != TokenType.COLON:
                self.rollback_state()
                other_token = None
                end_expr = None
            else:
                end_expr = self.try_parse_expression()

            inner_expr = SliceExpressionNode(
                inner_expr, middle_expr, end_expr, token, other_token
            )

        closing = self.lexer.parse_token()

        if closing.token_type != TokenType.CLOSING_SQUARE_BRACKET:
            self.rollback_state()
            self.lexer.raise_positioned_syntax_error("expected ']' after <expression>")

        return SubscriptionAccessExpressionNode(
            base,
            inner_expr,
            opening_bracket,
            closing,
        )
