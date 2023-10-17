from __future__ import annotations

import typing
from abc import ABC
from pycompiler.Lexer import Token


class AbstractSyntaxTreeNode(ABC):
    def get_tokens(self) -> typing.List[Token]:
        return []

    def __repr__(self):
        raise NotImplementedError

    def __eq__(self, other: AbstractSyntaxTreeNode):
        raise NotImplementedError

    def copy(self) -> AbstractSyntaxTreeNode:
        raise NotImplementedError

    def can_be_assignment_target(self) -> bool:
        return False


class AbstractSyntaxTreeExpressionNode(AbstractSyntaxTreeNode, ABC):
    pass