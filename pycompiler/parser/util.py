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


class OperatorTypeType(enum.Enum):
    SINGLETON = enum.auto()
    BINARY = enum.auto()
    INPLACE = enum.auto()


SINGLETON_OPERATOR_STRING_TO_TYPE: typing.Dict[str, OperatorType] = {}
BINARY_OPERATOR_STRING_TO_TYPE: typing.Dict[str, OperatorType] = {}
INPLACE_BINARY_OPERATOR_STRING_TO_TYPE: typing.Dict[str, OperatorType] = {}
LONGEST_OPERATOR_STRING = -1


class OperatorType(enum.Enum):
    SINGLE_PLUS = OperatorTypeType.SINGLETON, "+", "__pos__"
    SINGLE_MINUS = OperatorTypeType.SINGLETON, "-", "__neg__"
    SINGLE_INVERSE = OperatorTypeType.SINGLETON, "~", "__inv__"
    LOGIC_NOT = OperatorTypeType.SINGLETON, "not", None

    BINARY_PLUS = OperatorTypeType.BINARY, "+", "__add__", "__radd__"
    BINARY_MINUS = OperatorTypeType.BINARY, "-", "__sub__", "__rsub__"
    BINARY_STAR = OperatorTypeType.BINARY, "*", "__mul__", "__rmul__"
    BINARY_STAR_STAR = OperatorTypeType.BINARY, "**", "__pow__", "__rpow__"
    BINARY_SLASH = OperatorTypeType.BINARY, "/", "__truediv__", "__rtruediv__"
    BINARY_SLASH_SLASH = OperatorTypeType.BINARY, "//", "__floordiv__", "__rfloordiv__"
    BINARY_PERCENT = OperatorTypeType.BINARY, "%", "__mod__", "__rmod__"
    BINARY_LOGIC_OR = OperatorTypeType.BINARY, "|", "__or__", "__ror__"
    BINARY_LOGIC_AND = OperatorTypeType.BINARY, "&", "__and__", "__rand__"
    BINARY_LOGIC_XOR = OperatorTypeType.BINARY, "^", "__xor__", "__rxor__"
    BINARY_AT = OperatorTypeType.BINARY, "@", "__matmul__", "__rmatmul__"
    BINARY_IN = OperatorTypeType.BINARY, "in", "__contains__", None, True
    BINARY_IS = OperatorTypeType.BINARY, "is", "__is__"
    BINARY_EQ = OperatorTypeType.BINARY, "==", "__eq__", "__eq__"
    BINARY_NOT_EQ = OperatorTypeType.BINARY, "!=", "__ne__", "__ne__"
    BINARY_GT = OperatorTypeType.BINARY, ">", "__gt__", "__le__"
    BINARY_GE = OperatorTypeType.BINARY, ">=", "__ge__", "__lt__"
    BINARY_LT = OperatorTypeType.BINARY, "<", "__lt__", "__ge__"
    BINARY_LE = OperatorTypeType.BINARY, "<=", "__le__", "__gt__"
    LOGIC_OR = OperatorTypeType.BINARY, "or", None
    LOGIC_AND = OperatorTypeType.BINARY, "and", None

    BINARY_INPLACE_PLUS = OperatorTypeType.INPLACE, "+=", "__iadd__"
    BINARY_INPLACE_MINUS = OperatorTypeType.INPLACE, "-=", "__isub__"
    BINARY_INPLACE_STAR = OperatorTypeType.INPLACE, "*=", "__imul__"
    BINARY_INPLACE_STAR_STAR = OperatorTypeType.INPLACE, "**=", "__ipow__"
    BINARY_INPLACE_SLASH = OperatorTypeType.INPLACE, "/=", "__itruediv__"
    BINARY_INPLACE_SLASH_SLASH = OperatorTypeType.INPLACE, "//=", "__ifloordiv__"
    BINARY_INPLACE_PERCENT = OperatorTypeType.INPLACE, "%=", "__imod__"
    BINARY_INPLACE_LOGIC_OR = OperatorTypeType.INPLACE, "|=", "__ior__"
    BINARY_INPLACE_LOGIC_AND = OperatorTypeType.INPLACE, "&=", "__iand__"
    BINARY_INPLACE_LOGIC_XOR = OperatorTypeType.INPLACE, "^=", "__ixor__"
    BINARY_INPLACE_AT = OperatorTypeType.INPLACE, "@=", "__imatmul__"

    def __init__(
        self,
        optype: OperatorTypeType,
        operator: str,
        opattr: str,
        opinvattr: str = None,
        reverse_operator=False,
    ):
        self.operator = operator
        self.opattr = opattr
        self.opinvattr = opinvattr
        self.optype = optype
        self.reverse_operator = reverse_operator

        if optype == OperatorTypeType.SINGLETON:
            SINGLETON_OPERATOR_STRING_TO_TYPE[operator] = self
        elif optype == OperatorTypeType.BINARY:
            BINARY_OPERATOR_STRING_TO_TYPE[operator] = self
        elif optype == OperatorTypeType.INPLACE:
            INPLACE_BINARY_OPERATOR_STRING_TO_TYPE[operator] = self

        global LONGEST_OPERATOR_STRING
        LONGEST_OPERATOR_STRING = max(LONGEST_OPERATOR_STRING, len(operator))
