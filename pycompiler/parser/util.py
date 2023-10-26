import enum
import inspect


class ArgType(enum.Enum):
    NORMAL = inspect.Parameter.POSITIONAL_OR_KEYWORD, 0
    KEYWORD = inspect.Parameter.POSITIONAL_OR_KEYWORD, 1
    STAR = inspect.Parameter.VAR_POSITIONAL, 2
    STAR_STAR = inspect.Parameter.VAR_KEYWORD, 3

    def __init__(self, inspect_name: str, id: int):
        self.inspect_name = inspect_name
        self.id = id

    def __eq__(self, other):
        return type(other) is ArgType and self.id == other.id

    def __hash__(self):
        return self.id
