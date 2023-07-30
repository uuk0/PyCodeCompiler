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
    def __init__(self, file: io.StringIO):
        self.file = file
        self._file_cache = ""
        self.read_blocks: typing.List[str] = []
        self._state_block_indices: typing.List[int] = []

        self._token_parse_table: typing.Dict[TokenType, typing.Callable[[], Token | None]] = {
            TokenType.NEWLINE: self.try_parse_newline,
            TokenType.WHITESPACES: self.try_parse_whitespaces,
            TokenType.IDENTIFIER: self.try_parse_identifier,
            TokenType.KEYWORD: self.try_parse_keyword,
            TokenType.HASHTAG: self.try_parse_hashtag,
            TokenType.EQUAL_SIGN: self.try_parse_equal_sign,
        }

    def has_text(self) -> bool:
        if self._file_cache:
            return True

        c = self.get_chars(1)
        self.give_back(c)

        return c is not None

    def save_state(self):
        self._state_block_indices.append(len(self.read_blocks))

    def rollback_state(self):
        index = self._state_block_indices.pop(-1)
        self._file_cache += "".join(self.read_blocks[index:])
        del self.read_blocks[index:]

    def discard_save_state(self):
        self._state_block_indices.pop(-1)

    def get_chars(self, count: int) -> str | None:
        if len(self._file_cache) > count:
            text = self._file_cache[-count:]
            self._file_cache = self._file_cache[:-count]
            self.read_blocks.append(text)
            return text

        text = self._file_cache
        self._file_cache = ""
        text += self.file.read(count - len(text))

        if len(text) < count:
            self._file_cache += text
            return

        self.read_blocks.append(text)
        return text

    def give_back(self, text: str | Token | typing.List[str | Token | None] | None):
        if text is None:
            return self

        if isinstance(text, str):
            self._file_cache += text
        elif isinstance(text, Token):
            self._file_cache += text.text
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

    def try_parse_whitespaces(self) -> Token | None:
        c = self.get_chars(1)
        text = ""

        while c and c in _WHITESPACE:
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
            return Token(TokenType.HASHTAG, c)

    def try_parse_hashtag(self) -> Token | None:
        c = self.get_chars(1)

        if c != "#":
            self.give_back(c)
        else:
            return Token(TokenType.HASHTAG, c)

