from __future__ import annotations

import typing

from pycompiler.visitors.AbstractSyntaxTreeVisitor import AbstractASTTreeVisitor
from pycompiler.parser.OperatorExpressionNode import (
    OperatorType,
    SingletonOperator,
    BinaryOperator,
)


PRIORITIES_GROUPS = [
    [
        OperatorType.SINGLE_INVERSE,
        OperatorType.SINGLE_MINUS,
        OperatorType.SINGLE_PLUS,
    ],
    [
        OperatorType.BINARY_INPLACE_STAR_STAR,
    ],
    [
        OperatorType.BINARY_STAR,
        OperatorType.BINARY_SLASH,
        OperatorType.BINARY_SLASH_SLASH,
        OperatorType.BINARY_PERCENT,
    ],
    [
        OperatorType.BINARY_LOGIC_OR,
        OperatorType.BINARY_LOGIC_AND,
        OperatorType.BINARY_LOGIC_XOR,
    ],
    [
        OperatorType.BINARY_PLUS,
        OperatorType.BINARY_MINUS,
    ],
    [
        OperatorType.BINARY_EQ,
        OperatorType.BINARY_NOT_EQ,
        OperatorType.BINARY_LT,
        OperatorType.BINARY_LE,
        OperatorType.BINARY_GT,
        OperatorType.BINARY_GE,
    ],
    [
        OperatorType.BINARY_IN,
        OperatorType.BINARY_IS,
    ],
    [
        OperatorType.LOGIC_NOT,
    ],
    [
        OperatorType.LOGIC_OR,
        OperatorType.LOGIC_AND,
    ],
]

PRIORITY_INDEX_MAP: typing.Dict[OperatorType, int] = {}
for i, t in PRIORITIES_GROUPS:
    PRIORITY_INDEX_MAP |= {x: i for x in t}


class OperatorPrioritiesRewriter(AbstractASTTreeVisitor):
    def visit_singleton_operator(self, operator: SingletonOperator):
        if isinstance(operator.arg, BinaryOperator):
            this_index = PRIORITY_INDEX_MAP[operator.operator]
            inner_index = PRIORITY_INDEX_MAP[operator.arg.operator]

            if this_index < inner_index:
                operator.replace_with(
                    operator := BinaryOperator(
                        operator.arg.operator,
                        SingletonOperator(
                            operator.operator,
                            operator.arg.lhs,
                        ),
                        operator.arg.rhs,
                    ),
                )

                self.visit_any(operator)
                return

        super().visit_singleton_operator(operator)

    def visit_binary_operator(self, operator: BinaryOperator):
        if isinstance(operator.lhs, SingletonOperator):
            this_index = PRIORITY_INDEX_MAP[operator.operator]
            inner_index = PRIORITY_INDEX_MAP[operator.lhs.operator]

            if this_index > inner_index:
                operator.replace_with(
                    operator := SingletonOperator(
                        operator.lhs.operator,
                        BinaryOperator(
                            operator.operator,
                            operator.lhs.arg,
                            operator.rhs,
                        ),
                    ),
                )
                self.visit_any(operator)
                return

        elif isinstance(operator.lhs, BinaryOperator):
            this_index = PRIORITY_INDEX_MAP[operator.operator]
            inner_index = PRIORITY_INDEX_MAP[operator.lhs.operator]

            if this_index > inner_index:
                operator.replace_with(
                    operator := BinaryOperator(
                        operator.lhs.operator,
                        operator.lhs.lhs,
                        BinaryOperator(
                            operator.operator,
                            operator.lhs.rhs,
                            operator.rhs,
                        ),
                    ),
                )
                self.visit_any(operator)
                return

        elif isinstance(operator.rhs, BinaryOperator):
            this_index = PRIORITY_INDEX_MAP[operator.operator]
            inner_index = PRIORITY_INDEX_MAP[operator.rhs.operator]

            if this_index < inner_index:
                operator.replace_with(
                    operator := BinaryOperator(
                        operator.rhs.operator,
                        BinaryOperator(
                            operator.operator,
                            operator.lhs,
                            operator.rhs.rhs,
                        ),
                        operator.rhs.rhs,
                    ),
                )
                self.visit_any(operator)
                return

        super().visit_binary_operator(operator)
