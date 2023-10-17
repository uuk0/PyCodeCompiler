from __future__ import annotations

import sys
import typing
from typing import NamedTuple
import enum
import string


class TokenType(enum.Enum):
    WHITESPACE = enum.auto()
    NEWLINE = enum.auto()
    COMMENT = enum.auto()
    IDENTIFIER = enum.auto()
    NUMBER = enum.auto()

    EXCLAMATION_POINT = enum.auto()
    DOUBLE_QUOTES = enum.auto()
    PERCENT = enum.auto()
    LOGIC_AND = enum.auto()
    FORWARD_SLASH = enum.auto()
    OPENING_CURLY_BRACKET = enum.auto()
    OPENING_ROUND_BRACKET = enum.auto()
    OPENING_SQUARE_BRACKET = enum.auto()
    CLOSING_ROUND_BRACKET = enum.auto()
    CLOSING_SQUARE_BRACKET = enum.auto()
    EQUAL_SIGN = enum.auto()
    CLOSING_CURLY_BRACKET = enum.auto()
    QUESTION_MARK = enum.auto()
    BACKSLASH = enum.auto()
    PLUS = enum.auto()
    STAR = enum.auto()
    TILDE = enum.auto()
    HASHTAG = enum.auto()
    SINGLE_QUOTE = enum.auto()
    COMMA = enum.auto()
    SEMICOLON = enum.auto()
    POINT = enum.auto()
    COLON = enum.auto()
    MINUS = enum.auto()
    UNDERSCORE = enum.auto()

    STRING_LITERAL = enum.auto()


SPECIAL_TYPE_MAP = {
    TokenType.EXCLAMATION_POINT: "!",
    TokenType.DOUBLE_QUOTES: '"',
    TokenType.PERCENT: "%",
    TokenType.LOGIC_AND: "&",
    TokenType.FORWARD_SLASH: "/",
    TokenType.OPENING_CURLY_BRACKET: "{",
    TokenType.OPENING_ROUND_BRACKET: "(",
    TokenType.OPENING_SQUARE_BRACKET: "[",
    TokenType.CLOSING_ROUND_BRACKET: ")",
    TokenType.CLOSING_SQUARE_BRACKET: "]",
    TokenType.EQUAL_SIGN: "=",
    TokenType.CLOSING_CURLY_BRACKET: "}",
    TokenType.QUESTION_MARK: "?",
    TokenType.BACKSLASH: "\\",
    TokenType.PLUS: "+",
    TokenType.STAR: "*",
    TokenType.TILDE: "~",
    TokenType.HASHTAG: "#",
    TokenType.SINGLE_QUOTE: "'",
    TokenType.COMMA: ",",
    TokenType.SEMICOLON: ";",
    TokenType.POINT: ".",
    TokenType.COLON: ":",
    TokenType.MINUS: "-",
    TokenType.UNDERSCORE: "_",
}


class Token(NamedTuple):
    token_type: TokenType
    text: str
    line: int = -1
    column: int = -1
    span: int = 0
    value: object = None

    def __hash__(self):
        return hash((self.token_type, self.text))

    def __eq__(self, other: Token):
        return (
            type(other) is TokenType
            and self.token_type == other.token_type
            and self.text == other.text
        )

    def merge(self, rhs: Token, new_token_type: TokenType = None):
        return Token(
            new_token_type or self.token_type,
            self.text + rhs.text,
            self.line,
            self.column,
            self.span + rhs.span,
            self.value or rhs.value,
        )


class Lexer:
    def __init__(self, code: str, filename: str = None):
        self.code = code

        self.line = 0
        self.column = 0

        self.cursor = 0

        self.info_stack = []

        self.filename = filename

    def raise_positioned_syntax_error(self, message: str, span=1):
        print(
            f"File \"{self.filename or '<unknown>'}\", line {self.line}",
            file=sys.stdout,
        )
        line = self.code[self.cursor - self.column :]
        if "\n" in line:
            line = line[: line.index("\n")]
        print(line)
        print((" " * self.column) + ("^" * span))
        raise SyntaxError(
            message
        )  # todo: throw something only propagating major levels

    def push_state(self):
        self.info_stack.append((self.cursor, self.line, self.column))

    def pop_state(self):
        self.info_stack.pop(-1)

    def rollback_state(self):
        self.cursor, self.line, self.column = self.info_stack.pop(-1)

    def get_position_info(self) -> typing.Tuple[int, int]:
        return self.line, self.column

    def get_chars(self, count: int) -> str | None:
        if len(self.code) < self.cursor + 1:
            return

        return self.column[self.cursor : self.cursor + count]

    def increment_cursor(self, count: int | str):
        count = count if isinstance(count, int) else len(count)
        text = self.get_chars(count)

        if "\n" in text:
            self.line += text.count("\n")
            self.column = count - text.rindex("\n") - 1
        else:
            self.column += count

        self.cursor += count

    def parse_partial_token(self) -> Token:
        c = self.get_chars(1)

        if c in string.whitespace:
            pos = self.get_position_info()
            self.increment_cursor(1)

            if c == "\n":
                return Token(TokenType.NEWLINE, "\n", *pos, 1)

            return Token(TokenType.WHITESPACE, c, *pos, 1)

        elif c in string.digits:
            pos = self.get_position_info()
            self.increment_cursor(1)

            while (x := self.get_chars(1)) in string.digits:
                c += x
                self.increment_cursor(1)

            return Token(
                TokenType.NUMBER,
                c,
                *pos,
                len(c),
            )

        elif c in SPECIAL_TYPE_MAP:
            pos = self.get_position_info()
            self.increment_cursor(1)

            return Token(
                SPECIAL_TYPE_MAP[c],
                c,
                *pos,
                1,
            )

        elif c.isidentifier():
            pos = self.get_position_info()
            self.increment_cursor(1)

            while (x := self.get_chars(1)).isidentifier():
                c += x
                self.increment_cursor(1)

            return Token(
                TokenType.IDENTIFIER,
                c,
                *pos,
                len(c),
            )

        raise ValueError(f"unsupported start token: {c}")

    def parse_token(self):
        self.push_state()
        token = self.parse_partial_token()

        if token.token_type == TokenType.IDENTIFIER:
            self.pop_state()
            return token

        if token.token_type in (TokenType.PLUS, TokenType.MINUS):
            self.pop_state()
            number = self.try_parse_number()

            if number:
                merged = token.merge(number, TokenType.NUMBER)

                if token.token_type == TokenType.MINUS:
                    merged.value = -merged.value

                return merged

            return token

        # todo: are we missing any other cases?
        return token

    def try_parse_number(self) -> Token | None:
        self.push_state()
        token = self.parse_partial_token()

        if token.token_type != TokenType.NUMBER:
            self.rollback_state()
            return

        number_repr = 0  # 0: normal, 1: binary, 2: octal, 3: hexadecimal

        if token.text == "0":
            self.push_state()
            next_token = self.parse_partial_token()
            itoken: Token | None = None

            if next_token.token_type == TokenType.IDENTIFIER:
                if next_token.text.lower() == "b":
                    number_repr = 1
                    itoken = token.merge(next_token)
                elif next_token.text.lower() == "o":
                    number_repr = 2
                    itoken = token.merge(next_token)
                elif next_token.text.lower() == "x":
                    number_repr = 3
                    itoken = token.merge(next_token)

            if number_repr != 0:
                next_token = self.parse_partial_token()

                if next_token.token_type == TokenType.NUMBER:
                    token = itoken.merge(next_token)
                    self.pop_state()
                    self.push_state()
                else:
                    self.rollback_state()
                    self.push_state()
            else:
                self.rollback_state()
                self.push_state()

        has_seen_dot = False
        while True:
            self.pop_state()
            self.push_state()
            next_token = self.parse_partial_token()

            if next_token.token_type == TokenType.POINT:
                if has_seen_dot:
                    self.rollback_state()
                    break

                token = token.merge(next_token)
                has_seen_dot = True
                continue

            elif next_token.token_type in (TokenType.UNDERSCORE, TokenType.NUMBER):
                token = token.merge(next_token)
                continue

            self.rollback_state()
            break

        error: SyntaxError | None = None
        try:
            if number_repr == 0:
                token.value = int(token.text)
            elif number_repr == 1:
                token.value = int(token.text, base=2)
            elif number_repr == 2:
                token.value = int(token.text, base=8)
            elif number_repr == 3:
                token.value = int(token.text, base=16)
        except SyntaxError as error:
            pass
        else:
            self.pop_state()
            return token

        self.rollback_state()
        self.raise_positioned_syntax_error(
            error.text,
            span=token.span,
        )
