import enum


class ArgType(enum.Enum):
    NORMAL = enum.auto()
    KEYWORD = enum.auto()
    STAR = enum.auto()
    STAR_STAR = enum.auto()
