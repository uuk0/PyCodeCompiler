from __future__ import annotations

import inspect
import typing

from pycompiler.Lexer import Token, TokenType
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeNode,
    AbstractSyntaxTreeExpressionNode,
    ParentAttributeSection,
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
        type_hint: AbstractSyntaxTreeExpressionNode = None,
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

    def replace_child_with(
        self,
        original: AbstractSyntaxTreeNode,
        new: AbstractSyntaxTreeNode,
        section: ParentAttributeSection,
    ) -> bool:
        if (
            section != ParentAttributeSection.DEFAULT
            or self.arg_type != ArgType.KEYWORD
        ):
            return False

        self.default_value = new
        return True

    def update_child_parent_relation(self):
        if self.arg_type == ArgType.KEYWORD:
            self.default_value.parent = self
            self.default_value.parent_section = ParentAttributeSection.DEFAULT
            self.default_value.update_child_parent_relation()

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
            type(other) is FunctionDefinitionArg
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


class FunctionDefinitionArgReference(AbstractSyntaxTreeExpressionNode):
    def __init__(
        self, arg_ref: FunctionDefinitionArg, access_tokens: typing.List[Token] = None
    ):
        super().__init__()
        self.arg_ref = arg_ref
        self.access_tokens = access_tokens

    def get_tokens(self) -> typing.List[Token]:
        return self.access_tokens

    def __repr__(self):
        return f"->{repr(self.arg_ref)}"

    def __eq__(self, other: FunctionDefinitionArgReference):
        return (
            type(other) is FunctionDefinitionArgReference
            and self.arg_ref == other.arg_ref
        )

    def copy(self) -> FunctionDefinitionArgReference:
        # We are only ref-ing an arg decl, we don't need to copy the ref target
        return FunctionDefinitionArgReference(
            self.arg_ref,
            self.access_tokens,
        )

    def can_be_assignment_target(self) -> bool:
        return True


class FunctionDefinitionGenericReference(AbstractSyntaxTreeExpressionNode):
    def __init__(self, name: str, index: int, name_token: Token = None):
        super().__init__()
        self.name = name
        self.index = index
        self.name_token = name_token

    def get_tokens(self) -> typing.List[Token]:
        return [self.name_token]

    def __repr__(self):
        return f"->GENERIC({self.name})"

    def __eq__(self, other: FunctionDefinitionGenericReference):
        return (
            type(other) is FunctionDefinitionGenericReference
            and self.name == other.name
            and self.index == other.index
        )

    def copy(self) -> FunctionDefinitionGenericReference:
        # We are only ref-ing an arg decl, we don't need to copy the ref target
        return FunctionDefinitionGenericReference(
            self.name,
            self.index,
            self.name_token,
        )


class StaticFunctionReferenceNode(AbstractSyntaxTreeExpressionNode):
    def __init__(self, func_def: FunctionDefinitionNode):
        super().__init__()
        self.func_def = func_def

    def __repr__(self):
        return f"FUNC-REF({self.func_def.name})"

    def __eq__(self, other: StaticFunctionReferenceNode):
        return (
            type(other) is StaticFunctionReferenceNode
            and self.func_def is other.func_def
        )

    def copy(self) -> StaticFunctionReferenceNode:
        return StaticFunctionReferenceNode(self.func_def)


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
            generic_pair, opening = cls.parse_generics(
                generic_commas, generic_pair, generics, opening, parser
            )

        if opening is None:
            parser.pop_state()
            parser.push_state()
            opening = parser.lexer.parse_token()

        if opening.token_type != TokenType.OPENING_ROUND_BRACKET:
            parser.lexer.raise_positioned_syntax_error_on_token(
                opening, f"expected '(' after {'<name>' if generic_pair[0] else ']'}"
            )

        parser.pop_state()

        parameters = cls.parse_parameters(parser)

        parser.push_state()
        colon = parser.lexer.parse_token()
        if colon.token_type != TokenType.COLON:
            parser.lexer.raise_positioned_syntax_error_on_token(
                colon, "expected ':' after ')' in <function definition>"
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

    @classmethod
    def parse_parameters(cls, parser):
        parameters = []
        while True:
            parser.push_state()
            token = parser.lexer.parse_token()

            if token.token_type == TokenType.CLOSING_ROUND_BRACKET:
                parser.pop_state()
                break

            if token.token_type == TokenType.STAR:
                cls.parse_parameter_star(parameters, parser, token)

            else:
                cls.parse_parameter_no_star(parameters, parser, token)

            parser.push_state()
            comma = parser.lexer.parse_token()
            if comma.token_type == TokenType.COMMA:
                parser.pop_state()
                continue
            elif comma.token_type != TokenType.CLOSING_ROUND_BRACKET:
                parser.lexer.raise_positioned_syntax_error_on_token(
                    comma, "expected ',' or ')' after <parameter>"
                )

            parser.pop_state()
            break
        return parameters

    @classmethod
    def parse_parameter_no_star(
        cls,
        parameters: typing.List[FunctionDefinitionArg],
        parser: Parser,
        identifier: Token,
    ):
        is_keyword = False
        type_hint = None

        if identifier.token_type == TokenType.IDENTIFIER:
            next_token = parser.lexer.parse_token()

            if next_token.token_type == TokenType.COLON:
                type_hint = parser.try_parse_type_annotation()

                if type_hint is None:
                    parser.lexer.raise_positioned_syntax_error(
                        "expected <type hint> after ':'"
                    )

                parser.pop_state()
                parser.push_state()
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
                        identifier.text,
                        expr,
                        name_token=identifier,
                        equal_sign_token=next_token,
                    )
                )
            else:
                parser.rollback_state()

        else:
            parser.rollback_state()
            return

        if not is_keyword:
            expr = parser.try_parse_expression()

            if expr is None:
                parser.lexer.raise_positioned_syntax_error(
                    "expected <expression> after '(' or ','"
                )

            parameters.append(
                FunctionDefinitionArg(
                    ArgType.NORMAL,
                    identifier.text,
                    name_token=identifier,
                    type_hint=type_hint,
                )
            )

    @classmethod
    def parse_parameter_star(cls, parameters, parser: Parser, token):
        parser.push_state()
        next_token = parser.lexer.parse_token()
        if next_token.token_type == TokenType.STAR:
            parser.pop_state()
            parser.push_state()
            param_name = parser.lexer.parse_token()

            if param_name.token_type != TokenType.IDENTIFIER:
                parser.lexer.raise_positioned_syntax_error_on_token(
                    param_name, "expected <identifier> or '*' after '*'"
                )

            parser.pop_state()
            parser.pop_state()

            parser.push_state()
            type_hint = None
            next_token = parser.lexer.parse_token()
            if next_token.token_type == TokenType.COLON:
                type_hint = parser.try_parse_type_annotation()

                if type_hint is None:
                    parser.lexer.raise_positioned_syntax_error(
                        "expected <type hint> after ':'"
                    )

                parser.pop_state()
            else:
                parser.rollback_state()

            parameters.append(
                FunctionDefinitionArg(
                    ArgType.STAR_STAR,
                    param_name.text,
                    name_token=token,
                    type_hint=type_hint,
                )
            )

        else:
            parser.rollback_state()
            parser.push_state()
            param_name = parser.lexer.parse_token()

            if param_name.token_type != TokenType.IDENTIFIER:
                parser.lexer.raise_positioned_syntax_error_on_token(
                    param_name, "expected <expression> or '*' after '*'"
                )

            parser.pop_state()
            parser.pop_state()

            parser.push_state()
            type_hint = None
            next_token = parser.lexer.parse_token()
            if next_token.token_type == TokenType.COLON:
                type_hint = parser.try_parse_type_annotation()

                if type_hint is None:
                    parser.lexer.raise_positioned_syntax_error(
                        "expected <type hint> after ':'"
                    )

                parser.pop_state()
            else:
                parser.rollback_state()

            parameters.append(
                FunctionDefinitionArg(
                    ArgType.STAR,
                    param_name.text,
                    name_token=token,
                    type_hint=type_hint,
                )
            )

    @classmethod
    def parse_generics(
        cls, generic_commas, generic_pair, generics, opening, parser: Parser
    ):
        parser.push_state()
        generic_name = parser.lexer.parse_token()
        if generic_name.token_type == TokenType.CLOSING_SQUARE_BRACKET:
            generic_pair = opening, generic_name
            opening = None
            parser.pop_state()

        elif generic_name.token_type != TokenType.IDENTIFIER:
            parser.lexer.raise_positioned_syntax_error_on_token(
                generic_name,
                "expected <name> after '[' in <function definition> - <generics>",
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
                    parser.lexer.raise_positioned_syntax_error_on_token(
                        comma,
                        "expected ',' or ']' after <name> in <function definition> - <generics>",
                    )

                generic_commas.append(comma)

                generic_name = parser.lexer.parse_token()
                if generic_name.token_type == TokenType.CLOSING_SQUARE_BRACKET:
                    generic_pair = opening, generic_name
                    opening = None
                    parser.pop_state()
                    parser.pop_state()
                    break

                elif generic_name.token_type != TokenType.IDENTIFIER:
                    parser.lexer.raise_positioned_syntax_error_on_token(
                        generic_name,
                        "expected <name> or ']' after ','  in <function definition> - <generics>",
                    )

                parser.pop_state()
                generics.append(generic_name)
        return generic_pair, opening

    def __init__(
        self,
        name: str,
        generics: typing.List[str] | None,
        parameters: typing.List[FunctionDefinitionArg] | None,
        body: typing.List[AbstractSyntaxTreeNode],
        def_token: Token = None,
        name_token: Token = None,
        generic_bracket_tokens: typing.Tuple[Token, Token] = None,
        generic_name_tokens: typing.List[Token] = None,
        parameter_bracket: typing.Tuple[Token, Token] = None,
        return_type: AbstractSyntaxTreeExpressionNode = None,
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
        self.return_type = return_type

    def replace_child_with(
        self,
        original: AbstractSyntaxTreeNode,
        new: AbstractSyntaxTreeNode,
        section: ParentAttributeSection,
    ) -> bool:
        if section == ParentAttributeSection.PARAMETER:
            for i, param in enumerate(self.parameters):
                if param is original:
                    self.parameters[i] = new
                    return True

            return False

        if section == ParentAttributeSection.BODY:
            for i, node in enumerate(self.body):
                if node is original:
                    self.body[i] = new
                    return True

            return False

        return False

    def update_child_parent_relation(self):
        for param in self.parameters:
            param.parent = self
            param.parent_section = ParentAttributeSection.PARAMETER
            param.update_child_parent_relation()

        for node in self.body:
            node.parent = self
            node.parent_section = ParentAttributeSection.BODY
            node.update_child_parent_relation()

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

    def get_signature(self) -> inspect.Signature:
        args = []

        for param in self.parameters:
            if param.arg_type == ArgType.KEYWORD:
                args.append(
                    inspect.Parameter(
                        param.name,
                        inspect.Parameter.POSITIONAL_OR_KEYWORD,
                        default=param.default_value,
                        annotation=param.type_hint.as_data_type()
                        if param.type_hint
                        else typing.Any,
                    )
                )
            else:
                args.append(
                    inspect.Parameter(
                        param.name,
                        param.arg_type.inspect_name,
                        annotation=param.type_hint.as_data_type()
                        if param.type_hint
                        else typing.Any,
                    )
                )

        return inspect.Signature(
            args,
            return_annotation=self.return_type or typing.Any,
        )
