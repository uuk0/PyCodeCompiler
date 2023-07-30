import abc
import typing

from pycompiler import Lexer
import io


class AbstractASTNode(abc.ABC):
    pass


class PyNewlineNode(AbstractASTNode):
    def __init__(self, token: Lexer.Token):
        self.token = token

    def __eq__(self, other):
        return type(other) == PyNewlineNode and self.token == other.token

    def __repr__(self):
        return "NEWLINE"


class PyCommentNode(AbstractASTNode):
    def __init__(self, base_token: Lexer.Token, inner_string: Lexer.Token):
        self.base_token = base_token
        self.inner_string = inner_string

    def __eq__(self, other):
        return type(other) == PyCommentNode and self.base_token == other.base_token and self.inner_string == other.inner_string

    def __repr__(self):
        return f"COMMENT({self.base_token}|{self.inner_string})"


class AssignmentExpression(AbstractASTNode):
    def __init__(self, lhs: typing.List[AbstractASTNode], eq_sign: Lexer.Token, rhs: AbstractASTNode):
        self.lhs = lhs
        self.eq_sign = eq_sign
        self.rhs = rhs

    def __eq__(self, other):
        return type(other) == AssignmentExpression and self.lhs == other.lhs and self.eq_sign == other.eq_sign and self.rhs == other.rhs

    def __repr__(self):
        return f"ASSIGNMENT({self.lhs}|{self.eq_sign}|{self.rhs})"


class Parser:
    def __init__(self, source: str):
        self.source = source
        self.stream = io.StringIO(source)
        self.lexer = Lexer.Lexer(self.stream)

    def parse(self) -> typing.List[AbstractASTNode]:
        ast_stream: typing.List[AbstractASTNode] = []

        while self.lexer.has_text():
            while newline := self.lexer.try_parse_newline():
                ast_stream.append(PyNewlineNode(newline))

            if comment := self.try_parse_comment():
                ast_stream.append(comment)
                continue

            if assignment := self.try_parse_assignment():
                ast_stream.append(assignment)
                continue

        return ast_stream

    def try_parse_assignment_target(self) -> AbstractASTNode:
        pass

    def try_parse_expression(self) -> AbstractASTNode:
        pass

    def try_parse_comment(self) -> PyCommentNode | None:
        if comment_start := self.lexer.try_parse_hashtag():
            return PyCommentNode(comment_start, self.lexer.parse_until_newline())

    def try_parse_assignment(self) -> AssignmentExpression | None:
        assigned_variables = [self.try_parse_assignment_target()]

        if assigned_variables[0] is None:
            return

        eq_sign = self.lexer.try_parse_equal_sign()

        if eq_sign is None:
            self.lexer.give_back(eq_sign)
            return

        while True:
            expression = self.try_parse_assignment_target()

            if expression is None:
                break

            eq_sign = self.lexer.try_parse_equal_sign()

            if eq_sign is None:
                break

            assigned_variables.append(expression)
            # todo: store equal sign somewhere!

        if expression is None:
            expression = self.try_parse_expression()

        if expression is None:
            raise SyntaxError

        return AssignmentExpression(
            assigned_variables,
            eq_sign,
            expression,
        )
