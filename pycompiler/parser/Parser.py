from pycompiler.Lexer import Lexer, Token, TokenType
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeNode,
    AbstractSyntaxTreeExpressionNode,
)
from pycompiler.parser.NameAccessNode import NameAccessNode


class Parser:
    def __init__(self, code: str, filename: str = None):
        self.code = code
        self.lexer = Lexer(code, filename=filename)

    def try_parse_code_line_obj(self) -> AbstractSyntaxTreeNode:
        if expr := self.try_parse_expression():
            return expr

        self.lexer.raise_positioned_syntax_error("expected <code line>")

    def try_parse_expression(self) -> AbstractSyntaxTreeExpressionNode | None:
        self.lexer.push_state()
        token = self.lexer.parse_token()

        if token.token_type == TokenType.IDENTIFIER:
            base = NameAccessNode(token.text, token)
            self.lexer.pop_state()
        else:
            self.lexer.rollback_state()
            return

        return base
