from __future__ import annotations
import typing

from pycompiler.Lexer import Token, TokenType
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeNode,
    AbstractSyntaxTreeExpressionNode,
)
from pycompiler.parser.util import ArgType

if typing.TYPE_CHECKING:
    from pycompiler.parser.Parser import Parser


class FunctionDefinitionArg(AbstractSyntaxTreeNode):
    def __init__(
        self,
        arg_type: ArgType,
        name: str,
        default_value: AbstractSyntaxTreeNode = None,
        type_hint: AbstractSyntaxTreeNode = None,
        name_token: Token = None,
        equal_sign_token: Token = None,
    ):
        # todo: star tokens!
        super().__init__()
        self.arg_type = arg_type
        self.name = name
        self.default_value = default_value
        self.type_hint = type_hint
        self.name_token = name_token
        self.equal_sign_token = equal_sign_token

    def get_tokens(self) -> typing.List[Token]:
        return [self.name_token, self.equal_sign_token] + (
            self.default_value.get_tokens() if self.default_value else []
        )

    def __repr__(self):
        return (
            f"PARA({'' if self.arg_type == ArgType.NORMAL else ('*' if self.arg_type == ArgType.STAR else '**')}{self.name})"
            if self.arg_type != ArgType.KEYWORD
            else f"PARA({self.name} = {repr(self.default_value)})"
        )

    def __eq__(self, other: FunctionDefinitionArg):
        return (
            type(other) is FunctionDefinitionNode
            and self.arg_type == other.arg_type
            and self.name == other.name
            and self.default_value == other.default_value
        )

    def copy(self) -> FunctionDefinitionArg:
        return FunctionDefinitionArg(
            self.arg_type,
            self.name,
            self.default_value.copy() if self.default_value else None,
            self.type_hint,
            self.name_token,
            self.equal_sign_token,
        )


class FunctionDefinitionNode(AbstractSyntaxTreeNode):
    @classmethod
    def decode_from_paser(cls, parser: Parser):
        # 'def' <name> ['[' <generics> ']'] '(' <parameters> ')' ':' <code block>
        parser.push_state()
        def_token = parser.lexer.parse_token()
        if (
            def_token is None
            or def_token.token_type != TokenType.IDENTIFIER
            or def_token.text != "def"
        ):
            parser.rollback_state()
            return

        name = parser.lexer.parse_token()
        if name is None or name.token_type != TokenType.IDENTIFIER:
            parser.rollback_state()
            return

        parser.push_state()
        opening = parser.lexer.parse_token()
        generics = []
        generic_commas = []
        generic_pair = None, None

        if opening.token_type == TokenType.OPENING_SQUARE_BRACKET:
            parser.push_state()
            generic_name = parser.lexer.parse_token()

            if generic_name.token_type == TokenType.CLOSING_SQUARE_BRACKET:
                generic_pair = opening, generic_name
                opening = None
                parser.pop_state()
            elif generic_name.token_type != TokenType.IDENTIFIER:
                parser.rollback_state()
                parser.lexer.raise_positioned_syntax_error(
                    "expected <name> after '[' in <function definition> - <generics>"
                )
            else:
                parser.pop_state()
                generics.append(generic_name)

                while True:
                    parser.push_state()
                    comma = parser.lexer.parse_token()

                    if comma.token_type == TokenType.CLOSING_SQUARE_BRACKET:
                        generic_pair = opening, comma
                        opening = None
                        parser.pop_state()
                        parser.pop_state()
                        break
                    elif comma.token_type != TokenType.COMMA:
                        parser.rollback_state()
                        parser.lexer.raise_positioned_syntax_error(
                            "expected ',' or ']' after <name> in <function definition> - <generics>"
                        )

                    generic_commas.append(comma)

                    name = parser.lexer.parse_token()
                    if name.token_type == TokenType.CLOSING_SQUARE_BRACKET:
                        generic_pair = opening, name
                        opening = None
                        parser.pop_state()
                        parser.pop_state()
                    elif name.token_type != TokenType.IDENTIFIER:
                        parser.lexer.raise_positioned_syntax_error(
                            "expected <name> or ']' after ','  in <function definition> - <generics>"
                        )

                    parser.pop_state()
                    generics.append(name)

        if opening is None:
            parser.pop_state()
            parser.push_state()
            opening = parser.lexer.parse_token()

        if opening.token_type != TokenType.OPENING_ROUND_BRACKET:
            parser.rollback_state()
            parser.lexer.raise_positioned_syntax_error(
                f"expected '(' after {'<name>' if generic_pair[0] else ']'}"
            )

        parser.pop_state()

        parameters = []

        while True:
            parser.push_state()
            token = parser.lexer.parse_token()

            if token.token_type == TokenType.CLOSING_ROUND_BRACKET:
                parser.pop_state()
                break

            if token.token_type == TokenType.STAR:
                next_token = parser.lexer.parse_token()

                if next_token.token_type == TokenType.STAR:
                    expr = parser.try_parse_expression()

                    if expr is None:
                        parser.lexer.raise_positioned_syntax_error(
                            "expected <expression> after '**'"
                        )

                    parser.pop_state()

                    parameters.append(
                        FunctionDefinitionArg(
                            ArgType.STAR_STAR,
                            token.text,
                            name_token=token,
                        )
                    )

                else:
                    expr = parser.try_parse_expression()

                    if expr is None:
                        parser.lexer.raise_positioned_syntax_error(
                            "expected <expression> or '*' after '*'"
                        )

                    parser.pop_state()

                    parameters.append(
                        FunctionDefinitionArg(
                            ArgType.STAR,
                            token.text,
                            name_token=token,
                        )
                    )

            else:
                is_keyword = False
                if token.token_type == TokenType.IDENTIFIER:
                    next_token = parser.lexer.parse_token()

                    if next_token.token_type == TokenType.EQUAL_SIGN:
                        is_keyword = True

                        expr = parser.try_parse_expression()

                        if expr is None:
                            parser.lexer.raise_positioned_syntax_error(
                                "expected <expression> after '='"
                            )

                        parser.pop_state()
                        parameters.append(
                            FunctionDefinitionArg(
                                ArgType.KEYWORD,
                                token.text,
                                expr,
                                name_token=token,
                                equal_sign_token=next_token,
                            )
                        )
                    else:
                        parser.rollback_state()

                else:
                    parser.rollback_state()

                if not is_keyword:
                    expr = parser.try_parse_expression()

                    if expr is None:
                        parser.lexer.raise_positioned_syntax_error(
                            "expected <expression> after '(' or ','"
                        )

                    parameters.append(
                        FunctionDefinitionArg(
                            ArgType.NORMAL,
                            token.text,
                            name_token=token,
                        )
                    )

            parser.push_state()
            comma = parser.lexer.parse_token()
            if comma.token_type == TokenType.COMMA:
                parser.pop_state()
                continue
            elif comma.token_type != TokenType.CLOSING_ROUND_BRACKET:
                parser.rollback_state()
                parser.lexer.raise_positioned_syntax_error(
                    "expected ',' or ')' after <parameter>"
                )

            parser.pop_state()
            break

        parser.push_state()
        colon = parser.lexer.parse_token()
        if colon.token_type != TokenType.COLON:
            parser.rollback_state()
            parser.lexer.raise_positioned_syntax_error(
                "expected ':' after ')' in <function definition>"
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

        # todo: commas, bracket tokens
        return cls(
            name.text,
            [gen.text for gen in generics],
            parameters,
            body,
            def_token,
            name,
            generic_pair,
            generics,
        )

    def __init__(
        self,
        name: str,
        generics: typing.List[str] | None,
        parameters: typing.List | None,
        body: typing.List[AbstractSyntaxTreeNode],
        def_token: Token = None,
        name_token: Token = None,
        generic_bracket_tokens: typing.Tuple[Token, Token] = None,
        generic_name_tokens: typing.List[Token] = None,
        parameter_bracket: typing.Tuple[Token, Token] = None,
    ):
        super().__init__()
        self.name_token = name_token
        self.def_token = def_token
        self.parameter_bracket = parameter_bracket
        self.generic_name_tokens = generic_name_tokens
        self.generic_bracket_tokens = generic_bracket_tokens
        self.name = name
        self.generics = generics or []
        self.parameters = parameters or []
        self.body = body

    def get_tokens(self) -> typing.List[Token]:
        return (
            list(self.generic_bracket_tokens)
            + self.generic_name_tokens
            + list(self.parameter_bracket)
            + sum((param.get_tokens() for param in self.parameters), [])
            + sum((node.get_tokens() for node in self.body), [])
        )

    def __repr__(self):
        generic = f"[{', '.join(self.generics)}]" if self.generics else ""

        return f"FUNCTION-DEFINITION(def {self.name}{generic}({', '.join(map(repr, self.parameters))}): {'; '.join(map(repr, self.body))})"

    def __eq__(self, other: FunctionDefinitionNode):
        return (
            type(other) is FunctionDefinitionNode
            and self.name == other.name
            and self.generics == other.generics
            and self.parameters == other.parameters
            and self.body == other.body
        )

    def copy(self) -> FunctionDefinitionNode:
        return FunctionDefinitionNode(
            self.name,
            self.generics.copy(),
            [param.copy() for param in self.parameters],
            [node.copy() for node in self.body],
            self.def_token,
            self.name_token,
            self.generic_bracket_tokens,
            self.generic_name_tokens.copy(),
            self.parameter_bracket,
        )
