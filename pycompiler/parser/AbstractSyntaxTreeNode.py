from __future__ import annotations

import enum
import typing
from abc import ABC
from pycompiler.Lexer import Token
from pycompiler.emitter.CodeBuilder import CodeBuilder


if typing.TYPE_CHECKING:
    from pycompiler.parser.Parser import Parser
    from pycompiler.TypeChecking import TypeInformationHolder


class ParentAttributeSection(enum.Enum):
    LHS = enum.auto()
    RHS = enum.auto()
    BASE = enum.auto()
    PARAMETER = enum.auto()
    DEFAULT = enum.auto()
    BODY = enum.auto()
    CONDITION = enum.auto()
    ELSE_BLOCK = enum.auto()


class AbstractSyntaxTreeNode(ABC):
    CONTINUE_FLOW_AFTER_EXPRESSION = True

    @classmethod
    def try_parse_from_parser(cls, parser: Parser) -> AbstractSyntaxTreeNode:
        pass

    def __init__(self):
        self.scope = None
        self.parent: AbstractSyntaxTreeNode | None = None
        self.parent_section: ParentAttributeSection | None = None

    def replace_with(self, node: AbstractSyntaxTreeNode) -> bool:
        assert self.parent is not None, self
        status = self.parent.replace_child_with(self, node, self.parent_section)

        if status:
            self.parent.update_child_parent_relation()
            self.parent = None
            self.parent_section = None

        return status

    def replace_child_with(
        self,
        original: AbstractSyntaxTreeNode,
        new: AbstractSyntaxTreeNode,
        section: ParentAttributeSection,
    ) -> bool:
        raise NotImplementedError

    def update_child_parent_relation(self):
        pass

    def get_tokens(self) -> list[Token]:
        return []

    def __repr__(self):
        raise NotImplementedError

    def __eq__(self, other: AbstractSyntaxTreeNode):
        raise NotImplementedError

    def copy(self) -> AbstractSyntaxTreeNode:
        raise NotImplementedError

    def push_code(self, builder: CodeBuilder) -> CodeBuilder.Source:
        raise NotImplementedError

    def push_write_code(self, builder: CodeBuilder, value: CodeBuilder.Source):
        pass


class AbstractSyntaxTreeExpressionNode(AbstractSyntaxTreeNode, ABC):
    def __init__(self):
        super().__init__()
        self.result_type = None
        self.type_annotation: TypeInformationHolder | None = None

    def can_be_assignment_target(self) -> bool:
        return False

    def get_constant_on_attribute_access(
        self,
        name: str,
        context: AbstractSyntaxTreeNode = None,
    ) -> tuple[AbstractSyntaxTreeExpressionNode, AbstractSyntaxTreeNode | None] | None:
        """
        Optimisation method for getting an attribute of the node

        Should return None when not possible.
        Otherwise, should return tuple of the value, and optional a side effect

        :param name: the attribute name
        :param context: A node describing the attribute access
        """

    def get_constant_on_subscription_access(
        self,
        expr: AbstractSyntaxTreeExpressionNode,
        context: AbstractSyntaxTreeNode = None,
    ) -> tuple[AbstractSyntaxTreeExpressionNode, AbstractSyntaxTreeNode | None] | None:
        """
        Optimisation method for getting a subscription

        Should return None when not possible.
        Otherwise, should return tuple of the value, and optional a side effect

        :param expr: the index expr
        :param context: A node describing the attribute access
        """

    def update_result_type(self):
        pass

    def copy(self) -> AbstractSyntaxTreeExpressionNode:
        raise NotImplementedError

    def get_data_type(self) -> type:
        return self.result_type or typing.Any

    def as_data_type(self):
        return NotImplemented
