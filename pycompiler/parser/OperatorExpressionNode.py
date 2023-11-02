from __future__ import annotations

from pycompiler.Lexer import Token
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeExpressionNode,
    AbstractSyntaxTreeNode,
    ParentAttributeSection,
)
from pycompiler.parser.util import OperatorType, OperatorTypeType


class SingletonOperator(AbstractSyntaxTreeExpressionNode):
    def __init__(self, operator: OperatorType, arg: AbstractSyntaxTreeExpressionNode):
        super().__init__()
        self.operator = operator
        self.arg = arg

    def replace_child_with(
        self,
        original: AbstractSyntaxTreeNode,
        new: AbstractSyntaxTreeNode,
        section: ParentAttributeSection,
    ) -> bool:
        if section != ParentAttributeSection.RHS:
            return False
        self.arg = new
        return True

    def update_child_parent_relation(self):
        self.arg.parent = self
        self.arg.parent_section = ParentAttributeSection.RHS
        self.arg.update_child_parent_relation()

    def get_tokens(self) -> list[Token]:
        return self.arg.get_tokens()

    def __repr__(self):
        return f"{self.operator.operator} {self.arg}"

    def __eq__(self, other: SingletonOperator):
        return (
            type(other) is SingletonOperator
            and self.operator == other.operator
            and self.arg == other.arg
        )

    def copy(self) -> SingletonOperator:
        return SingletonOperator(self.operator, self.arg.copy())


class BinaryOperator(AbstractSyntaxTreeExpressionNode):
    def __init__(
        self,
        operator: OperatorType,
        lhs: AbstractSyntaxTreeExpressionNode,
        rhs: AbstractSyntaxTreeExpressionNode,
    ):
        super().__init__()
        self.operator = operator
        self.lhs = lhs
        self.rhs = rhs

    def replace_child_with(
        self,
        original: AbstractSyntaxTreeNode,
        new: AbstractSyntaxTreeNode,
        section: ParentAttributeSection,
    ) -> bool:
        if section == ParentAttributeSection.LHS:
            self.lhs = new
            return True

        if section == ParentAttributeSection.RHS:
            self.rhs = new
            return True

    def update_child_parent_relation(self):
        self.lhs.parent = self
        self.lhs.parent_section = ParentAttributeSection.LHS
        self.lhs.update_child_parent_relation()

        self.rhs.parent = self
        self.rhs.parent_section = ParentAttributeSection.RHS
        self.rhs.update_child_parent_relation()

    def get_tokens(self) -> list[Token]:
        return self.lhs.get_tokens() + self.rhs.get_tokens()

    def __repr__(self):
        return f"{self.lhs} {self.operator.operator} {self.rhs}"

    def __eq__(self, other: BinaryOperator):
        return (
            type(other) is BinaryOperator
            and self.operator == other.operator
            and self.lhs == other.lhs
            and self.rhs == other.rhs
        )

    def copy(self) -> BinaryOperator:
        return BinaryOperator(self.operator, self.lhs.copy(), self.rhs.copy())


class BinaryInplaceOperator(AbstractSyntaxTreeNode):
    def __init__(
        self,
        operator: OperatorType,
        lhs: AbstractSyntaxTreeExpressionNode,
        rhs: AbstractSyntaxTreeExpressionNode,
    ):
        super().__init__()
        self.operator = operator
        self.lhs = lhs
        self.rhs = rhs

        if lhs and not lhs.can_be_assignment_target():
            raise ValueError(f"lhs must be assign-able, got {lhs}")

    def replace_child_with(
        self,
        original: AbstractSyntaxTreeNode,
        new: AbstractSyntaxTreeExpressionNode,
        section: ParentAttributeSection,
    ) -> bool:
        if section == ParentAttributeSection.LHS:
            if not new.can_be_assignment_target():
                raise ValueError(f"new lhs must be assign-able, got {new}!")

            self.lhs = new
            return True

        if section == ParentAttributeSection.RHS:
            self.rhs = new
            return True

    def update_child_parent_relation(self):
        self.lhs.parent = self
        self.lhs.parent_section = ParentAttributeSection.LHS
        self.lhs.update_child_parent_relation()

        self.rhs.parent = self
        self.rhs.parent_section = ParentAttributeSection.RHS
        self.rhs.update_child_parent_relation()

    def get_tokens(self) -> list[Token]:
        return self.lhs.get_tokens() + self.rhs.get_tokens()

    def __repr__(self):
        return f"{self.lhs} {self.operator.operator} {self.rhs}"

    def __eq__(self, other: BinaryInplaceOperator):
        return (
            type(other) is BinaryInplaceOperator
            and self.operator == other.operator
            and self.lhs == other.lhs
            and self.rhs == other.rhs
        )

    def copy(self) -> BinaryInplaceOperator:
        return BinaryInplaceOperator(self.operator, self.lhs.copy(), self.rhs.copy())


TYPE_TYPE_TO_CLASS = {
    OperatorTypeType.SINGLETON: SingletonOperator,
    OperatorTypeType.BINARY: BinaryOperator,
    OperatorTypeType.INPLACE: BinaryInplaceOperator,
}
