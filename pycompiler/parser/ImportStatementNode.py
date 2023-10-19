from __future__ import annotations

import typing

from pycompiler.Lexer import Token
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeExpressionNode,
    AbstractSyntaxTreeNode,
)
from pycompiler.Lexer import Token, TokenType

if typing.TYPE_CHECKING:
    from pycompiler.parser.Parser import Parser


class ImportStatement(AbstractSyntaxTreeNode):
    @classmethod
    def parse_from_parser(cls, parser: Parser) -> ImportStatement | None:
        parser.push_state()

        token = parser.lexer.parse_token()

        if token.token_type != TokenType.IDENTIFIER or token.text not in ("from", "import"):
            parser.rollback_state()
            return
        
        parser.pop_state()
        
        tokens = [token]
        from_module = None
        
        if token.text == "from":
            from_module = cls.parse_module_fragment(parser, "'from'")
            token = parser.lexer.parse_token()
            
            if token.token_type != TokenType.IDENTIFIER or token.text != "import":
                parser.lexer.raise_positioned_syntax_error("expected 'import' after 'from' <module>")
                
            tokens.append(token)
                
        module = cls.parse_module_fragment(parser, "'import'")
        
        parser.push_state()
        token = parser.lexer.parse_token()
        
        if token is not None and token.token_type == TokenType.IDENTIFIER and token.text == "as":
            parser.pop_state()
            as_token = parser.lexer.parse_token()
            
            if as_token.token_type != TokenType.IDENTIFIER:
                parser.lexer.raise_positioned_syntax_error("expected <name> after 'as'")
        else:
            as_token = None
            parser.rollback_state()
            
        return cls(
            ".".join(token.text for token in module),
            ".".join(token.text for token in from_module) if from_module else None,
            as_token.text if as_token else None,
            tokens + [as_token] + module + (from_module or []),
        )
        
    @classmethod
    def parse_module_fragment(cls, parser: Parser, context: str) -> typing.List[Token]:
        # todo: modules which start with a '.' !

        token = parser.lexer.parse_token()

        if token.token_type != TokenType.IDENTIFIER:
            parser.lexer.raise_positioned_syntax_error(f"expected <identifier> after {context}")

        module = [token]
        while True:
            parser.push_state()
            token = parser.lexer.parse_token()

            if token is None or token.token_type != TokenType.POINT:
                parser.rollback_state()
                return module

            token = parser.lexer.parse_token()

            if token.token_type != TokenType.IDENTIFIER:
                parser.lexer.raise_positioned_syntax_error(f"expected <identifier> after {context} ... '.'")

            module.append(token)

    def __init__(
        self,
        module: str,
        from_module: str = None,
        as_name: str = None,
        tokens: typing.List[Token] = None,
    ):
        super().__init__()
        self.tokens = tokens or []
        self.as_name = as_name
        self.from_module = from_module
        self.module = module

    def get_tokens(self) -> typing.List[Token]:
        return self.tokens

    def __repr__(self):
        return f"IMPORT({self.module}{f" from {self.from_module}" if self.from_module else ""}{f" as {self.as_name}" if self.as_name else ""})"

    def __eq__(self, other: ImportStatement):
        return (
            type(other) is ImportStatement
            and self.module == other.module
            and self.from_module == other.from_module
            and self.as_name == other.as_name
        )

    def copy(self) -> ImportStatement:
        return ImportStatement(
            self.module,
            self.from_module,
            self.as_name,
            self.tokens.copy()
        )
