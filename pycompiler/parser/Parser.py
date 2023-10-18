from pycompiler.Lexer import Lexer, Token, TokenType
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeNode,
    AbstractSyntaxTreeExpressionNode,
)
from pycompiler.parser.NameAccessNode import NameAccessNode
from pycompiler.parser.AssignmentExpressionNode import AssignmentExpressionNode
from pycompiler.parser.AttributeAccessExpressionNode import (
    AttributeAccessExpressionNode,
)


class Parser:
    def __init__(self, code: str, filename: str = None):
        self.code = code
        self.lexer = Lexer(code, filename=filename)

    def push_state(self):
        self.lexer.push_state()

    def pop_state(self):
        self.lexer.pop_state()

    def rollback_state(self):
        self.lexer.rollback_state()

    def try_parse_code_line_obj(self) -> AbstractSyntaxTreeNode:
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
            else:
                self.rollback_state()
                break

            self.pop_state()

        return base
