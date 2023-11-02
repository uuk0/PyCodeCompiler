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
    AT_SIGN = enum.auto()
    LESS_THAN = enum.auto()
    BIGGER_THAN = enum.auto()
    VBAR = enum.auto()

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
    TokenType.AT_SIGN: "@",
    TokenType.LESS_THAN: "<",
    TokenType.BIGGER_THAN: ">",
    TokenType.VBAR: "|",
}

REVERSE_SPECIAL_TYPE_MAP = {
    text: token_type for token_type, text in SPECIAL_TYPE_MAP.items()
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

    def __repr__(self):
        return f"{self.token_type.name}({self.text})"


class Lexer:
    def __init__(self, code: str, filename: str = None):
        self.code = code

        self.line = 0
        self.column = 0

        self.cursor = 0

        self.info_stack = []
        self.line_offsets = []

        offset = 0
        for line in code.split("\n"):
            self.line_offsets.append(offset)
            offset += len(line) + 1
        self.line_offsets.append(offset)

        self.filename = filename

    def parse_indent_block(self) -> bool:
        block = self.get_chars(4)

        if block is None or block != "    ":
            return False

        self.increment_cursor(4)
        return True

    def raise_positioned_syntax_error(self, message: str, span=1) -> typing.NoReturn:
        print(
            f"File \"{self.filename or '<unknown>'}\", line {self.line + 1}",
            file=sys.stderr,
        )
        line = self.code[
            self.line_offsets[self.line] : self.line_offsets[self.line + 1] + 1
        ]
        print(line, file=sys.stderr)
        print((" " * self.column) + ("^" * span), file=sys.stderr)
        # todo: throw something only propagating major levels
        raise SyntaxError(message)

    def raise_positioned_syntax_error_on_token(self, token: Token, message: str):
        print(
            f"File \"{self.filename or '<unknown>'}\", line {token.line + 1}",
            file=sys.stderr,
        )
        line = self.code[
            self.line_offsets[token.line] : self.line_offsets[token.line + 1] + 1
        ]
        print(line, file=sys.stderr)
        print((" " * token.column) + ("^" * token.span), file=sys.stderr)
        # todo: throw something only propagating major levels

        raise SyntaxError(message)

    def push_state(self):
        self.info_stack.append((self.cursor, self.line, self.column))

    def pop_state(self):
        self.info_stack.pop(-1)

    def rollback_state(self):
        self.cursor, self.line, self.column = self.info_stack.pop(-1)

    def get_position_info(self) -> tuple[int, int]:
        return self.line, self.column

    def get_chars(self, count: int) -> str | None:
        if len(self.code) < self.cursor + 1:
            return

        return self.code[self.cursor : self.cursor + count]

    def get_chars_or_pad(self, count: int, pad=" "):
        if len(self.code) > self.cursor:
            return self.code[self.cursor : self.cursor + count]

        delta = count - (len(self.code) - self.cursor - 1)
        return self.code[self.cursor : self.cursor + count - delta] + (pad * delta)

    def parse_whitespace(self):
        while (c := self.get_chars(1)) and c in " \t":
            self.increment_cursor(1)

    def increment_cursor(self, count: int | str):
        count = count if isinstance(count, int) else len(count)
        text = self.get_chars(count)

        if text and "\n" in text:
            self.line += text.count("\n")
            self.column = count - text.rindex("\n") - 1
        else:
            self.column += count

        self.cursor += count

    def parse_partial_token(self) -> Token | None:
        c = self.get_chars(1)

        if c is None:
            return

        if c in string.whitespace:
            pos = self.get_position_info()
            self.increment_cursor(1)

            if c == "\n":
                return Token(TokenType.NEWLINE, "\n", *pos, 1)

            return Token(TokenType.WHITESPACE, c, *pos, 1)

        elif c in string.digits:
            pos = self.get_position_info()
            self.increment_cursor(1)

            while (x := self.get_chars(1)) and x and x in string.digits:
                c += x
                self.increment_cursor(1)

            return Token(
                TokenType.NUMBER,
                c,
                *pos,
                len(c),
            )

        elif c in REVERSE_SPECIAL_TYPE_MAP:
            pos = self.get_position_info()
            self.increment_cursor(1)

            return Token(
                REVERSE_SPECIAL_TYPE_MAP[c],
                c,
                *pos,
                1,
            )

        elif c.isidentifier():
            pos = self.get_position_info()
            self.increment_cursor(1)

            while (x := self.get_chars(1)) and (c + x).isidentifier():
                c += x
                self.increment_cursor(1)

            return Token(
                TokenType.IDENTIFIER,
                c,
                *pos,
                len(c),
            )

        raise ValueError(f"unsupported start token: {c}")

    def parse_token(self, include_whitespace=False) -> Token | None:
        self.push_state()

        while (
            (token := self.parse_partial_token())
            and token
            and token.token_type == TokenType.WHITESPACE
            and not include_whitespace
        ):
            pass

        if token is None:
            self.rollback_state()
            return

        if token.token_type == TokenType.IDENTIFIER:
            self.pop_state()
            return token

        if token.token_type in (TokenType.PLUS, TokenType.MINUS):
            self.pop_state()
            if number := self.try_parse_number():
                merged = token.merge(number, TokenType.NUMBER)

                if token.token_type == TokenType.MINUS:
                    merged.value = -merged.value

                return merged

            return token

        self.pop_state()

        # todo: are we missing any other cases?
        return token

    def try_parse_number(self) -> Token | None:
        self.push_state()
        token = self.parse_token()

        if token is None:
            self.rollback_state()
            return

        fragments = []
        has_seen_point = False

        if token.token_type == TokenType.NUMBER:
            fragments.append(token)

            pos = self.get_position_info()
            c = self.get_chars(1)

            if c and fragments[0].text == "0" and c.lower() in tuple("box"):
                self.increment_cursor(1)
                fragments.append(Token(TokenType.IDENTIFIER, c, *pos))

        elif token.token_type == TokenType.POINT:
            has_seen_point = True
            fragments.append(token)

        else:
            self.rollback_state()
            return

        while True:
            self.push_state()
            token = self.parse_token()

            if token is None:
                self.rollback_state()
                break

            if token.token_type == TokenType.NUMBER:
                fragments.append(token)
            elif token.token_type == TokenType.UNDERSCORE:
                fragments.append(token)
            elif token.token_type == TokenType.POINT and not has_seen_point:
                has_seen_point = True
                fragments.append(token)
            else:
                self.rollback_state()
                break
            self.pop_state()

        total = "".join(token.text for token in fragments).lower()

        try:
            if "." in total:
                result = float(total)
            elif "b" in total:
                result = int(total.removeprefix("0b"), base=2)
            elif "o" in total:
                result = int(total.removeprefix("0o"), base=8)
            elif "x" in total:
                result = int(total.removeprefix("0x"), base=16)
            else:
                result = int(total)
        except ValueError:
            self.raise_positioned_syntax_error("expected <integer literal>")

        return Token(
            TokenType.NUMBER,
            total,
            fragments[0].line,
            fragments[0].column,
            sum(token.span for token in fragments),  # todo: add whitespaces!
            result,
        )

    def try_parse_string(self) -> Token | None:
        self.push_state()
        token = self.parse_token()

        if token is None:
            self.rollback_state()
            return

        if token.token_type == TokenType.SINGLE_QUOTE:
            self.pop_state()
            escapes = 0
            string = "'"

            while True:
                c = self.get_chars(1)
                self.increment_cursor(1)

                if c == "\\":
                    escapes += 1
                    if escapes % 2 == 0:
                        string += "\\"
                elif c == "'":
                    string += "'"
                    if escapes % 2 == 0:
                        break
                    escapes = 0
                elif c == "\n":
                    self.raise_positioned_syntax_error(
                        "did NOT expect '\n' in single-quoted string literal"
                    )
                else:
                    string += c
                    escapes = 0

            return Token(
                TokenType.STRING_LITERAL,
                string,
                token.line,
                token.column,
                token.span,
                string[1:-1],
            )

        elif token.token_type == TokenType.DOUBLE_QUOTES:
            self.pop_state()
            escapes = 0
            string = '"'

            while True:
                c = self.get_chars(1)
                self.increment_cursor(1)

                if c == "\\":
                    escapes += 1
                    if escapes % 2 == 0:
                        string += "\\"
                elif c == '"':
                    string += '"'
                    if escapes % 2 == 0:
                        break
                    escapes = 0
                elif c == "\n":
                    self.raise_positioned_syntax_error(
                        "did NOT expect '\n' in double-quoted string literal"
                    )
                else:
                    escapes = 0
                    string += c

            return Token(
                TokenType.STRING_LITERAL,
                string,
                token.line,
                token.column,
                token.span,
                string[1:-1],
            )

        self.rollback_state()
