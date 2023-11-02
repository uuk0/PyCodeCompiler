from __future__ import annotations

import enum
import inspect
import typing


class ArgType(enum.Enum):
    NORMAL = inspect.Parameter.POSITIONAL_OR_KEYWORD, 0
    KEYWORD = inspect.Parameter.POSITIONAL_OR_KEYWORD, 1
    STAR = inspect.Parameter.VAR_POSITIONAL, 2
    STAR_STAR = inspect.Parameter.VAR_KEYWORD, 3

    def __init__(self, inspect_name, id: int):
        self.inspect_name = inspect_name
        self.id = id

    def __eq__(self, other):
        return type(other) is ArgType and self.id == other.id

    def __hash__(self):
        return self.id


OPERATOR_STRING_TO_TYPE: typing.Dict[str, OperatorType] = {}
LONGEST_OPERATOR_STRING = -1


class OperatorType(enum.Enum):
    SINGLE_PLUS = "+", "__pos__"
    SINGLE_MINUS = "-", "__neg__"
    SINGLE_INVERSE = "~", "__inv__"

    BINARY_PLUS = "+", "__add__", "__radd__"
    BINARY_MINUS = "-", "__sub__", "__rsub__"
    BINARY_STAR = "*", "__mul__", "__rmul__"
    BINARY_STAR_STAR = "**", "__pow__", "__rpow__"
    BINARY_SLASH = "/", "__truediv__", "__rtruediv__"
    BINARY_SLASH_SLASH = "//", "__floordiv__", "__rfloordiv__"
    BINARY_PERCENT = "%", "__mod__", "__rmod__"
    BINARY_LOGIC_OR = "|", "__or__", "__ror__"
    BINARY_LOGIC_AND = "&", "__and__", "__rand__"
    BINARY_LOGIC_XOR = "^", "__xor__", "__rxor__"
    BINARY_AT = "@", "__matmul__", "__rmatmul__"
    BINARY_IN = "in", "__contains__", None, True
    BINARY_IS = "is", "__is__"
    BINARY_EQ = "==", "__eq__", "__eq__"
    BINARY_NOT_EQ = "!=", "__ne__", "__ne__"
    BINARY_GT = ">", "__gt__", "__le__"
    BINARY_GE = ">=", "__ge__", "__lt__"
    BINARY_LT = "<", "__lt__", "__ge__"
    BINARY_LE = "<=", "__le__", "__gt__"

    BINARY_INPLACE_PLUS = "+=", "__iadd__"
    BINARY_INPLACE_MINUS = "-=", "__isub__"
    BINARY_INPLACE_STAR = "*=", "__imul__"
    BINARY_INPLACE_STAR_STAR = "**=", "__ipow__"
    BINARY_INPLACE_SLASH = "/=", "__itruediv__"
    BINARY_INPLACE_SLASH_SLASH = "//=", "__ifloordiv__"
    BINARY_INPLACE_PERCENT = "%=", "__imod__"
    BINARY_INPLACE_LOGIC_OR = "|=", "__ior__"
    BINARY_INPLACE_LOGIC_AND = "&=", "__iand__"
    BINARY_INPLACE_LOGIC_XOR = "^=", "__ixor__"
    BINARY_INPLACE_AT = "@=", "__imatmul__"

    def __init__(
        self, operator: str, opattr: str, opinvattr: str = None, reverse_operator=False
    ):
        self.operator = operator
        self.opattr = opattr
        self.opinvattr = opinvattr
        self.reverse_operator = reverse_operator

        global OPERATOR_STRING_TO_TYPE, LONGEST_OPERATOR_STRING
        OPERATOR_STRING_TO_TYPE[operator] = self
        LONGEST_OPERATOR_STRING = max(LONGEST_OPERATOR_STRING, len(operator))

    def __eq__(self, other: OperatorType):
        return type(other) is OperatorType and self.operator == other.operator

    def __hash__(self):
        return hash(self.operator)
