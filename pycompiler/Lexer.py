import enum
import io
import string
import typing


_WHITESPACE = " \t"
_KEYWORDS = [
    "def",
    "class",
    "if",
    "elif",
    "else",
    "while",
    "for",
    "return",
    "yield",
    "pass",
    "import",
    "from",
    "as",
    "and",
    "or",
]


class TokenType(enum.Enum):
    NEWLINE = enum.auto()
    WHITESPACES = enum.auto()

    IDENTIFIER = enum.auto()
    KEYWORD = enum.auto()

    OPENING_ROUND_BRACKET = enum.auto()  # todo
    CLOSING_ROUND_BRACKET = enum.auto()  # todo

    OPENING_SQUARE_BRACKET = enum.auto()  # todo
    CLOSING_SQUARE_BRACKET = enum.auto()  # todo

    OPENING_CURLY_BRACKET = enum.auto()  # todo
    CLOSING_CURLY_BRACKET = enum.auto()  # todo

    DOT = enum.auto()
    COLON = enum.auto()  # todo
    SEMICOLON = enum.auto()  # todo
    PLUS = enum.auto()  # todo
    MINUS = enum.auto()  # todo
    STAR = enum.auto()  # todo
    TILDE = enum.auto()  # todo
    PERCENT = enum.auto()  # todo
    EQUAL_SIGN = enum.auto()
    HASHTAG = enum.auto()

    SINGLE_QUOTE = enum.auto()  # todo
    DOUBLE_QUOTE = enum.auto()  # todo

    REMAINING_STRING = enum.auto()

    def __call__(self, text: str):
        return Token(self, text)


class Token:
    def __init__(self, token_type: TokenType, text: str):
        self.token_type = token_type
        self.text = text

    def __eq__(self, other):
        return type(other) == Token and self.token_type == other.token_type and self.text == other.text

    def __repr__(self):
        return f"{self.token_type.name}({repr(self.text)})"


class Lexer:
    def __init__(self, file: str):
        self.file = file
        self.file_cursor = 0
        self._saved_states: typing.List[int] = []

        self._token_parse_table: typing.Dict[TokenType, typing.Callable[[], Token | None]] = {
            TokenType.NEWLINE: self.try_parse_newline,
            TokenType.WHITESPACES: self.try_parse_whitespaces,
            TokenType.IDENTIFIER: self.try_parse_identifier,
            TokenType.KEYWORD: self.try_parse_keyword,
            TokenType.HASHTAG: self.try_parse_hashtag,
            TokenType.EQUAL_SIGN: self.try_parse_equal_sign,
        }

    def has_text(self) -> bool:
        return len(self.file) > self.file_cursor + 1

    def save_state(self):
        self._saved_states.append(self.file_cursor)

    def rollback_state(self):
        self.file_cursor = self._saved_states.pop(-1)

    def discard_save_state(self):
        self._saved_states.pop(-1)

    def inspect_chars(self, count: int) -> str | None:
        if self.file_cursor + count > len(self.file):
            return
        return self.file[self.file_cursor:self.file_cursor + count]

    def get_chars(self, count: int) -> str | None:
        if self.file_cursor + count > len(self.file):
            return

        text = self.file[self.file_cursor:self.file_cursor+count]
        self.file_cursor += count
        return text

    def give_back(self, text: str | Token | typing.List[str | Token | None] | None):
        if text is None:
            return self

        if isinstance(text, str):
            self.file_cursor -= len(text)
            assert self.inspect_chars(len(text)) == text

        elif isinstance(text, Token):
            self.file_cursor -= len(text.text)
            assert self.inspect_chars(len(text.text)) == text.text

        elif isinstance(text, list):
            for e in text:
                self.give_back(e)

        else:
            raise ValueError(text)

        return self

    def try_parse_token(self, token_type: TokenType) -> Token | None:
        if token_type not in self._token_parse_table:
            return

        return self._token_parse_table[token_type]()

    def parse_until_newline(self) -> Token | None:
        c = self.get_chars(1)

        if not c:
            return

        if c == "\n":
            return Token(TokenType.REMAINING_STRING, "")

        text = c
        c = self.get_chars(1)

        while c and c != "\n":
            text += c
            c = self.get_chars(1)

        self.give_back(c)

        return Token(TokenType.REMAINING_STRING, text)

    def try_parse_newline(self) -> Token | None:
        c = self.get_chars(1)

        if c != "\n":
            self.give_back(c)
        else:
            return Token(TokenType.NEWLINE, c)

    def try_parse_whitespaces(self, include_newline=False) -> Token | None:
        c = self.get_chars(1)
        text = ""

        search = _WHITESPACE
        if include_newline:
            search += "\n"

        while c and c in search:
            text += c
            c = self.get_chars(1)

        self.give_back(c)

        if text:
            return Token(TokenType.WHITESPACES, text)

    def try_parse_identifier(self) -> Token | None:
        c = self.get_chars(1)

        if not c or c not in string.ascii_letters:
            self.give_back(c)
            return

        text = c
        c = self.get_chars(1)

        while c and c in string.ascii_letters + string.digits + "_":
            text += c
            c = self.get_chars(1)

        self.give_back(c)

        if text in _KEYWORDS:
            self.give_back(text)
            return

        return Token(TokenType.IDENTIFIER, text)

    def try_parse_keyword(self) -> Token | None:
        identifier = self.try_parse_identifier()

        if not identifier:
            return

        if identifier.text in _KEYWORDS:
            identifier.token_type = TokenType.IDENTIFIER
            return identifier

        self.give_back(identifier.text)

    def try_parse_equal_sign(self) -> Token | None:
        c = self.get_chars(1)

        if c != "=":
            self.give_back(c)
        else:
            return Token(TokenType.EQUAL_SIGN, c)

    def try_parse_hashtag(self) -> Token | None:
        c = self.get_chars(1)

        if c != "#":
            self.give_back(c)
        else:
            return Token(TokenType.HASHTAG, c)

    def try_parse_dot(self) -> Token | None:
        c = self.get_chars(1)

        if c != ".":
            self.give_back(c)
        else:
            return Token(TokenType.DOT, c)

    def try_parse_opening_round_bracket(self) -> Token | None:
        c = self.get_chars(1)

        if c != "(":
            self.give_back(c)
        else:
            return Token(TokenType.OPENING_ROUND_BRACKET, c)


    def try_parse_closing_round_bracket(self) -> Token | None:
        c = self.get_chars(1)

        if c != ")":
            self.give_back(c)
        else:
            return Token(TokenType.CLOSING_ROUND_BRACKET, c)


    def try_parse_opening_square_bracket(self) -> Token | None:
        c = self.get_chars(1)

        if c != "[":
            self.give_back(c)
        else:
            return Token(TokenType.OPENING_SQUARE_BRACKET, c)

    def try_parse_closing_square_bracket(self) -> Token | None:
        c = self.get_chars(1)

        if c != "]":
            self.give_back(c)
        else:
            return Token(TokenType.CLOSING_SQUARE_BRACKET, c)

    def try_parse_opening_curly_bracket(self) -> Token | None:
        c = self.get_chars(1)

        if c != "{":
            self.give_back(c)
        else:
            return Token(TokenType.OPENING_CURLY_BRACKET, c)

    def try_parse_closing_curly_bracket(self) -> Token | None:
        c = self.get_chars(1)

        if c != "}":
            self.give_back(c)
        else:
            return Token(TokenType.CLOSING_CURLY_BRACKET, c)

