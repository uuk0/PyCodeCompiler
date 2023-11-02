from __future__ import annotations

from pycompiler.parser.AbstractSyntaxTreeNode import (
    AbstractSyntaxTreeExpressionNode,
    AbstractSyntaxTreeNode,
)
from pycompiler.parser.util import OperatorType


class SingletonOperator(AbstractSyntaxTreeExpressionNode):
    pass


class BinaryOperator(AbstractSyntaxTreeExpressionNode):
    pass


class BinaryInplaceOperator(AbstractSyntaxTreeNode):
    pass
