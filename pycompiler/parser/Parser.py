from __future__ import annotations

import typing

from pycompiler.Lexer import Lexer, Token, TokenType
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeNode,
    AbstractSyntaxTreeExpressionNode,
)
from pycompiler.parser.BreakStatementNode import BreakStatement
from pycompiler.parser.ContinueStatementNode import ContinueStatement
from pycompiler.parser.NameAccessNode import NameAccessNode, NameWriteAccessNode
from pycompiler.parser.AssignmentExpressionNode import AssignmentExpressionNode
from pycompiler.parser.AttributeAccessExpressionNode import (
    AttributeAccessExpressionNode,
)
from pycompiler.parser.PassStatementNode import PassStatement
from pycompiler.parser.RaiseStatementNode import RaiseStatement
from pycompiler.parser.ReturnStatementNode import ReturnStatement
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
from pycompiler.parser.YieldStatementNode import YieldStatement
from pycompiler.parser.ListConstruction import (
    ListConstructorNode,
    ListComprehensionNode,
)
from pycompiler.parser.OperatorExpressionNode import (
    SingletonOperator,
    BinaryOperator,
    BinaryInplaceOperator,
)
from pycompiler.parser.util import (
    OperatorTypeType,
    LONGEST_OPERATOR_STRING,
    OPERATOR_STRING_TO_TYPE,
)


class Parser:
    KNOWN_EXACT_STATEMENTS = [
        FunctionDefinitionNode,
        ClassDefinitionNode,
        TypeStatementNode,
        ImportStatement,
        WhileStatementNode,
        ReturnStatement,
        RaiseStatement,
        YieldStatement,
        PassStatement,
        BreakStatement,
        ContinueStatement,
        BinaryInplaceOperator,
    ]

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
        self, expected_indent=0, first_needs_indent=True
    ) -> list[AbstractSyntaxTreeNode]:
        old_indent = self.indent
        self.indent = expected_indent
        result = []

        if first_needs_indent:
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
                return []

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
                print(result)
                print(next_token)
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

                    if next_token and next_token.token_type == TokenType.NEWLINE:
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
        for t in self.KNOWN_EXACT_STATEMENTS:
            self.push_state()
            pos = self.lexer.get_position_info()

            if expr := t.try_parse_from_parser(self):
                self.pop_state()
                return expr

            self.rollback_state()
            assert pos == self.lexer.get_position_info(), f"stack issue in {t}"

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
            self.push_state()
            c = self.lexer.get_chars_or_pad(LONGEST_OPERATOR_STRING)

            for i in range(len(c), 0, -1):
                if c[:i] in OPERATOR_STRING_TO_TYPE:
                    op = OPERATOR_STRING_TO_TYPE[c[:i]]

                    if op.optype != OperatorTypeType.SINGLETON:
                        continue

                    self.lexer.pop_state()
                    rhs = self.try_parse_expression()
                    if rhs is None:
                        raise SyntaxError(
                            f"expected <expression> after '{op.operator}'-operator"
                        )

                    return SingletonOperator(op, rhs)

            self.lexer.rollback_state()
            self.lexer.push_state()
            token = self.lexer.parse_token()

            if token is None:
                return

            if token.token_type == TokenType.IDENTIFIER:
                base = NameAccessNode(token.text, token)
                self.lexer.pop_state()

            elif token.token_type == TokenType.OPENING_SQUARE_BRACKET:
                base = self.parse_list_comprehension()

                if base is None:
                    self.lexer.rollback_state()
                    return

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

                if name is None:
                    self.lexer.raise_positioned_syntax_error(
                        "expected <identifier> after '.'"
                    )
                if name.token_type != TokenType.IDENTIFIER:
                    self.lexer.raise_positioned_syntax_error_on_token(
                        name, "expected <identifier> after '.'"
                    )

                base = AttributeAccessExpressionNode(base, name.text, token, name)

            elif token.token_type == TokenType.OPENING_SQUARE_BRACKET:
                base = self.parse_slice_operator(base, token)

            elif token.token_type == TokenType.OPENING_ROUND_BRACKET:
                base = CallExpression.parse_from_parser(self, base, token)

            else:
                self.rollback_state()
                self.push_state()
                self.lexer.parse_whitespace()

                c = self.lexer.get_chars_or_pad(LONGEST_OPERATOR_STRING)

                for i in range(len(c), 0, -1):
                    if c[:i] in OPERATOR_STRING_TO_TYPE:
                        op = OPERATOR_STRING_TO_TYPE[c[:i]]

                        if op.optype != OperatorTypeType.BINARY:
                            continue

                        self.lexer.pop_state()
                        rhs = self.try_parse_expression()
                        if rhs is None:
                            self.lexer.raise_positioned_syntax_error(
                                f"expected <expression> after '{op.operator}'-operator"
                            )
                        base = BinaryOperator(op, base, rhs)
                        break
                else:
                    self.lexer.rollback_state()
                    break

            self.pop_state()

        return base

    def parse_list_comprehension(
        self,
    ) -> ListComprehensionNode | ListConstructorNode | None:
        self.lexer.push_state()
        next_token = self.lexer.parse_token()
        if next_token.token_type == TokenType.CLOSING_SQUARE_BRACKET:
            self.lexer.pop_state()
            return ListConstructorNode([])
        self.lexer.rollback_state()

        expr = self.try_parse_expression()

        if expr is None:
            self.lexer.raise_positioned_syntax_error(
                "expected <expression> or ']' after '['"
            )

        self.lexer.push_state()
        token = self.lexer.parse_token()

        if token is None:
            self.lexer.raise_positioned_syntax_error("expected ']' or ','")

        if token.token_type == TokenType.IDENTIFIER and token.text == "for":
            self.lexer.pop_state()
            target = self.try_parse_assignment_target()
            if target is None:
                self.lexer.raise_positioned_syntax_error(
                    "expected <assignment target> after 'for'"
                )

            token = self.lexer.parse_token()
            if token.token_type != TokenType.IDENTIFIER or token.text != "in":
                self.lexer.raise_positioned_syntax_error_on_token(
                    token, "expected 'in' after 'for' <assignment target>"
                )

            source = self.try_parse_expression()
            if source is None:
                self.lexer.raise_positioned_syntax_error(
                    "expected <expression> after 'in'"
                )

            self.lexer.push_state()
            if_cond = None
            token = self.lexer.parse_token()

            if token is None:
                self.lexer.pop_state()

            elif token.token_type == TokenType.IDENTIFIER and token.text == "if":
                self.lexer.pop_state()
                if_cond = self.try_parse_expression()

                if if_cond is None:
                    self.lexer.raise_positioned_syntax_error(
                        "expected <expression> after 'if'"
                    )
            else:
                self.lexer.rollback_state()

            token = self.lexer.parse_token()
            if token.token_type != TokenType.CLOSING_SQUARE_BRACKET:
                self.lexer.raise_positioned_syntax_error("expected ']'")

            return ListComprehensionNode(
                expr,
                target,
                source,
                if_cond,
            )

        self.lexer.rollback_state()
        items = [expr]

        while True:
            self.push_state()
            token = self.lexer.parse_token()
            if token.token_type != TokenType.COMMA:
                self.rollback_state()
                break
            self.pop_state()

            expr = self.try_parse_expression()

            if expr is None:
                break

            items.append(expr)

        token = self.lexer.parse_token()
        if token is None or token.token_type != TokenType.CLOSING_SQUARE_BRACKET:
            self.lexer.raise_positioned_syntax_error_on_token(token, "expected ']'")

        return ListConstructorNode(items)

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
            self.lexer.raise_positioned_syntax_error_on_token(
                closing, "expected ']' after <expression>"
            )

        return SubscriptionAccessExpressionNode(
            base,
            inner_expr,
            opening_bracket,
            closing,
        )
