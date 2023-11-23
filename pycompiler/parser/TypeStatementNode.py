from __future__ import annotations

import typing

from pycompiler.emitter.CodeBuilder import CodeBuilder
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeExpressionNode,
    AbstractSyntaxTreeNode,
    ParentAttributeSection,
)
from pycompiler.parser.SubscriptionAccessExpressionNode import (
    SubscriptionAccessExpressionNode,
)
from pycompiler.parser.NameAccessNode import NameAccessNode
from pycompiler.Lexer import Token, TokenType

if typing.TYPE_CHECKING:
    from pycompiler.parser.Parser import Parser


class StaticTypeDefinitionReference(AbstractSyntaxTreeExpressionNode):
    def __init__(self, node: TypeStatementNode):
        super().__init__()
        self.node = node

    def __repr__(self):
        return f"TYPE-REF({self.node.base_type})"

    def __eq__(self, other: StaticTypeDefinitionReference):
        return type(other) is StaticTypeDefinitionReference and self.node is other.node

    def copy(self) -> StaticTypeDefinitionReference:
        return StaticTypeDefinitionReference(self.node)


class TypeStatementNode(AbstractSyntaxTreeNode):
    @classmethod
    def try_parse_from_parser(cls, parser: Parser) -> TypeStatementNode | None:
        parser.push_state()
        token = parser.lexer.parse_token()

        if token is None:
            parser.rollback_state()
            return

        if (
            token.token_type != TokenType.IDENTIFIER
            or token.text != "type"
            or parser.lexer.get_chars(1) != " "
        ):
            parser.rollback_state()
            return

        lhs = parser.try_parse_type_annotation(is_lhs=False)
        if lhs is None:
            parser.rollback_state()
            return

        eq_sign = parser.lexer.parse_token()
        if eq_sign.token_type != TokenType.EQUAL_SIGN:
            parser.rollback_state()
            return

        rhs = parser.try_parse_type_annotation()
        if rhs is None:
            parser.rollback_state()
            return

        return cls(
            lhs,
            rhs,
        )

    def __init__(
        self,
        base_type: AbstractSyntaxTreeExpressionNode,
        real_type: AbstractSyntaxTreeExpressionNode,
    ):
        super().__init__()
        self.base_type = base_type
        self.real_type = real_type

    def get_base_name(self) -> str:
        node = self.base_type

        if isinstance(node, SubscriptionAccessExpressionNode):
            node = node.base

        assert isinstance(node, NameAccessNode)

        return node.name

    def replace_child_with(
        self,
        original: AbstractSyntaxTreeNode,
        new: AbstractSyntaxTreeNode,
        section: ParentAttributeSection,
    ) -> bool:
        if section == ParentAttributeSection.LHS:
            self.base_type = new
            return True

        if section == ParentAttributeSection.RHS:
            self.real_type = new
            return True

        return False

    def update_child_parent_relation(self):
        self.base_type.parent = self
        self.base_type.parent_section = ParentAttributeSection.LHS
        self.base_type.update_child_parent_relation()

        self.real_type.parent = self
        self.real_type.parent_section = ParentAttributeSection.RHS
        self.real_type.update_child_parent_relation()

    def get_tokens(self) -> list[Token]:
        return self.base_type.get_tokens() + self.real_type.get_tokens()

    def __repr__(self):
        return f"TYPE({self.base_type} := {self.real_type})"

    def __eq__(self, other: TypeStatementNode):
        return (
            type(other) is TypeStatementNode
            and self.base_type == other.base_type
            and self.real_type == other.real_type
        )

    def copy(self) -> TypeStatementNode:
        return TypeStatementNode(
            self.base_type.copy(),
            self.real_type.copy(),
        )

    def push_code(self, builder: CodeBuilder):
        real = self.real_type.push_code(builder)

        # todo: this should be the base name without generics!
        self.base_type.push_write_code(builder, real)
