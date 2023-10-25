from __future__ import annotations
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


class ClassDefinitionGenericReference(AbstractSyntaxTreeExpressionNode):
    def __init__(self, name: str, index: int, name_token: Token = None):
        super().__init__()
        self.name = name
        self.index = index
        self.name_token = name_token

    def get_tokens(self) -> typing.List[Token]:
        return [self.name_token]

    def __repr__(self):
        return f"->GENERIC({self.name})"

    def __eq__(self, other: ClassDefinitionGenericReference):
        return (
            type(other) is ClassDefinitionGenericReference
            and self.name == other.name
            and self.index == other.index
        )

    def copy(self) -> ClassDefinitionGenericReference:
        # We are only ref-ing an arg decl, we don't need to copy the ref target
        return ClassDefinitionGenericReference(
            self.name,
            self.index,
            self.name_token,
        )


class StaticClassReferenceNode(AbstractSyntaxTreeExpressionNode):
    def __init__(self, class_def: ClassDefinitionNode):
        super().__init__()
        self.class_def = class_def

    def __repr__(self):
        return f"FUNC-REF({self.class_def.name})"

    def __eq__(self, other: StaticClassReferenceNode):
        return type(other) is StaticClassReferenceNode

    def copy(self) -> StaticClassReferenceNode:
        return StaticClassReferenceNode(self.class_def)


class ClassDefinitionNode(AbstractSyntaxTreeNode):
    @classmethod
    def decode_from_paser(cls, parser: Parser):
        # 'class' <name> ['[' <generics> ']'] '(' <parent_classes> ')' ':' <code block>
        parser.push_state()
        class_token = parser.lexer.parse_token()
        if (
            class_token is None
            or class_token.token_type != TokenType.IDENTIFIER
            or class_token.text != "class"
        ):
            parser.rollback_state()
            return

        name = parser.lexer.parse_token()
        if name is None or name.token_type != TokenType.IDENTIFIER:
            parser.lexer.raise_positioned_syntax_error("expected <name> after 'class'")

        parser.push_state()
        opening = parser.lexer.parse_token()
        generics = []
        generic_commas = []
        generic_pair = None, None

        if opening is None:
            parser.lexer.raise_positioned_syntax_error(
                "expected '(', '[' or ':' after <identifier> in <class definition>"
            )

        if opening.token_type == TokenType.OPENING_SQUARE_BRACKET:
            generic_pair, opening = cls.parse_generics(
                generic_commas, generic_pair, generics, opening, parser
            )

        if opening is None:
            parser.pop_state()
            parser.push_state()
            opening = parser.lexer.parse_token()

        if opening.token_type == TokenType.OPENING_ROUND_BRACKET:
            parser.pop_state()
            parent_classes = cls.parse_parent_references(parser)
        else:
            parser.rollback_state()
            parent_classes = []

        parser.push_state()
        colon = parser.lexer.parse_token()
        if colon.token_type != TokenType.COLON:
            parser.lexer.raise_positioned_syntax_error_on_token(
                colon, "expected ':' after ')' in <class definition>"
            )
        parser.pop_state()
        parser.push_state()
        newline = parser.lexer.parse_token()

        if newline.token_type == TokenType.NEWLINE:
            parser.pop_state()
            body = parser.parse_code_block(parser.indent + 1)

            if not body:
                parser.lexer.raise_positioned_syntax_error(
                    "expected <statement> after <class definition>"
                )

        else:
            parser.rollback_state()
            body = [parser.try_parse_code_line_obj()]

            if body[0] is None:
                parser.lexer.throw_positioned_syntax_error(
                    "expected <statement> after <class definition>"
                )

        # todo: commas, bracket tokens
        return cls(
            name.text,
            [gen.text for gen in generics],
            parent_classes,
            body,
            class_token,
            name,
            generic_pair,
            generics,
        )

    @classmethod
    def parse_parent_references(cls, parser: Parser):
        parameters = []
        while True:
            parser.push_state()
            token = parser.lexer.parse_token()

            if token.token_type == TokenType.CLOSING_ROUND_BRACKET:
                parser.pop_state()
                break

            parser.rollback_state()
            expr = parser.try_parse_expression()

            if expr is None:
                parser.lexer.raise_positioned_syntax_error(
                    "expected <expression> after '(' or ',' in <parents of class>"
                )

            parameters.append(expr)

            parser.push_state()
            comma = parser.lexer.parse_token()

            if comma is None:
                parser.lexer.raise_positioned_syntax_error(
                    "expected ',' or ')' after <parameter>"
                )

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

                if comma is None:
                    parser.lexer.raise_positioned_syntax_error(
                        "expected ',' or ']' after <name> in <function definition> - <generics>",
                    )

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
        parent_references: typing.List[AbstractSyntaxTreeExpressionNode] | None,
        body: typing.List[AbstractSyntaxTreeNode],
        class_token: Token = None,
        name_token: Token = None,
        generic_bracket_tokens: typing.Tuple[Token, Token] = None,
        generic_name_tokens: typing.List[Token] = None,
        parameter_bracket: typing.Tuple[Token, Token] = None,
    ):
        super().__init__()
        self.name_token = name_token
        self.class_token = class_token
        self.parameter_bracket = parameter_bracket
        self.generic_name_tokens = generic_name_tokens or []
        self.generic_bracket_tokens = generic_bracket_tokens
        self.name = name
        self.generics = generics or []
        self.parent_references = parent_references or []
        self.body = body

    def replace_child_with(
        self,
        original: AbstractSyntaxTreeNode,
        new: AbstractSyntaxTreeNode,
        section: ParentAttributeSection,
    ) -> bool:
        if section == ParentAttributeSection.PARAMETER:
            for i, node in enumerate(self.parent_references):
                if node is original:
                    self.parent_references[i] = new
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
        for parent in self.parent_references:
            parent.parent = self
            parent.parent_section = ParentAttributeSection.PARAMETER
            parent.update_child_parent_relation()

        for node in self.body:
            node.parent = self
            node.parent_section = ParentAttributeSection.BODY
            node.update_child_parent_relation()

    def get_tokens(self) -> typing.List[Token]:
        return (
            list(self.generic_bracket_tokens)
            + self.generic_name_tokens
            + list(self.parameter_bracket)
            + sum((parent.get_tokens() for parent in self.parent_references), [])
            + sum((node.get_tokens() for node in self.body), [])
        )

    def __repr__(self):
        generic = f"[{', '.join(self.generics)}]" if self.generics else ""

        return f"CLASS-DEFINITION(class {self.name}{generic}({', '.join(map(repr, self.parent_references))}): {'; '.join(map(repr, self.body))})"

    def __eq__(self, other: ClassDefinitionNode):
        return (
            type(other) is ClassDefinitionNode
            and self.name == other.name
            and self.generics == other.generics
            and self.parent_references == other.parent_references
            and self.body == other.body
        )

    def copy(self) -> ClassDefinitionNode:
        return ClassDefinitionNode(
            self.name,
            self.generics.copy(),
            [param.copy() for param in self.parent_references],
            [node.copy() for node in self.body],
            self.class_token,
            self.name_token,
            self.generic_bracket_tokens,
            self.generic_name_tokens.copy(),
            self.parameter_bracket,
        )
