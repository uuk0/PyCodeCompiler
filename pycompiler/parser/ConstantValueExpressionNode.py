from __future__ import annotations

import typing

from pycompiler.Lexer import Token
from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeExpressionNode,
)


class ConstantValueExpressionNode(AbstractSyntaxTreeExpressionNode):
    def __init__(self, value, tokens: typing.List[Token] = None):
        super().__init__()
        self.value = value
        self.tokens = tokens or []

    def get_tokens(self) -> typing.List[Token]:
        return self.tokens

    def copy(self) -> ConstantValueExpressionNode:
        return ConstantValueExpressionNode(self.value, self.tokens.copy())

    def __repr__(self):
        return f"CONST[{self.value}]"

    def __eq__(self, other: ConstantValueExpressionNode):
        return type(other) is ConstantValueExpressionNode and self.value == other.value
