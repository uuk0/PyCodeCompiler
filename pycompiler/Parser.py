import abc
import typing

from pycompiler import Lexer
import io


class AbstractASTNode(abc.ABC):
    pass


class PyNewlineNode(AbstractASTNode):
    def __init__(self, token: Lexer.Token):
        self.token = token


class PyCommentNode(AbstractASTNode):
    def __init__(self, base_token: Lexer.Token, inner_string: Lexer.Token):
        self.base_token = base_token
        self.inner_string = inner_string


class Parser:
    def __init__(self, source: str):
        self.source = source
        self.stream = io.StringIO(source)
        self.lexer = Lexer.Lexer(self.stream)

    def parse(self):
        ast_stream: typing.List[AbstractASTNode] = []

        while self.lexer.has_text():
            while newline := self.lexer.try_parse_newline():
                ast_stream.append(PyNewlineNode(newline))

            if comment := self.try_parse_comment():
                ast_stream.append(comment)
                continue

    def try_parse_comment(self) -> PyCommentNode | None:
        if comment_start := self.lexer.try_parse_hashtag():
            return PyCommentNode(comment_start, self.lexer.parse_until_newline())
