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


class NameAccessExpression(AbstractASTNode):
    def __init__(self, name: Lexer.Token):
        self.name = name

    def __eq__(self, other):
        return type(other) == NameAccessExpression and self.name == other.name

    def __repr__(self):
        return f"VARIABLE({self.name})"


class AttributeExpression(AbstractASTNode):
    def __init__(self, base: AbstractASTNode, dot: Lexer.Token, attribute: Lexer.Token):
        self.base = base
        self.dot = dot
        self.attribute = attribute

    def __eq__(self, other):
        return type(other) == AttributeExpression and self.base == other.base and self.dot == other.dot and self.attribute == other.attribute

    def __repr__(self):
        return f"ATTRIBUTE({self.base}|{self.dot}|{self.attribute})"


class SubscriptionExpression(AbstractASTNode):
    def __init__(self, base: AbstractASTNode, lhs_bracket: Lexer.Token, expression: AbstractASTNode, rhs_bracket: Lexer.Token):
        self.base = base
        self.lhs_bracket = lhs_bracket
        self.expression = expression
        self.rhs_bracket = rhs_bracket

    def __eq__(self, other):
        return type(other) == SubscriptionExpression and self.base == other.base and self.lhs_bracket == other.lhs_bracket and self.expression == other.expression and self.rhs_bracket == other.rhs_bracket

    def __repr__(self):
        return f"SUBSCRIPTION({self.base}|{self.lhs_bracket}|{self.expression}|{self.rhs_bracket})"


class SyntaxTreeVisitor:
    def visit_any(self, obj: AbstractASTNode):
        obj_type = type(obj)

        if obj_type == PyNewlineNode:
            return self.visit_newline(obj)
        elif obj_type == PyCommentNode:
            return self.visit_comment(obj)
        elif obj_type == AssignmentExpression:
            return self.visit_assignment(obj)
        elif obj_type == NameAccessExpression:
            return self.visit_name_access(obj)
        elif obj_type == AttributeExpression:
            return self.visit_attribute_expression(obj)
        elif obj_type == SubscriptionExpression:
            return self.visit_subscription_expression(obj)
        else:
            raise RuntimeError(obj)

    def visit_newline(self, newline: PyNewlineNode):
        pass

    def visit_comment(self, comment: PyCommentNode):
        pass

    def visit_assignment(self, assignment: AssignmentExpression):
        return [self.visit_any(target) for target in assignment.lhs], self.visit_any(assignment.rhs)

    def visit_name_access(self, access: NameAccessExpression):
        pass

    def visit_attribute_expression(self, expression: AttributeExpression):
        return self.visit_any(expression.base),

    def visit_subscription_expression(self, expression: SubscriptionExpression):
        return self.visit_any(expression.base), self.visit_any(expression.expression)


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

    def try_parse_assignment_target(self) -> AbstractASTNode | None:
        identifier = self.lexer.try_parse_identifier()

        if identifier is None:
            return

        base = NameAccessExpression(identifier)

        while True:
            if opening_square_bracket := self.lexer.try_parse_opening_square_bracket():
                expression = self.try_parse_expression()

                if expression is None or not (closing_bracket := self.lexer.try_parse_closing_square_bracket()):
                    raise SyntaxError

                base = SubscriptionExpression(
                    base,
                    opening_square_bracket,
                    expression,
                    closing_bracket,
                )

            else:
                break

        return base

    def try_parse_expression(self) -> AbstractASTNode | None:
        self.lexer.try_parse_whitespaces()
        identifier = self.lexer.try_parse_identifier()

        if identifier is None:
            return

        base = NameAccessExpression(identifier)

        while True:
            self.lexer.try_parse_whitespaces()

            # todo: allow slices
            if opening_square_bracket := self.lexer.try_parse_opening_square_bracket():
                expression = self.try_parse_expression()

                if expression is None or not (closing_bracket := self.lexer.try_parse_closing_square_bracket()):
                    raise SyntaxError

                base = SubscriptionExpression(
                    base,
                    opening_square_bracket,
                    expression,
                    closing_bracket,
                )

            elif dot := self.lexer.try_parse_dot():
                self.lexer.try_parse_whitespaces()

                identifier = self.lexer.try_parse_identifier()

                if identifier is None:
                    raise SyntaxError

                base = AttributeExpression(base, dot, identifier)

            elif opening_round_bracket := self.lexer.try_parse_opening_round_bracket():
                raise NotImplementedError

            else:
                break

        self.lexer.try_parse_whitespaces()
        return base

    def try_parse_comment(self) -> PyCommentNode | None:
        if comment_start := self.lexer.try_parse_hashtag():
            return PyCommentNode(comment_start, self.lexer.parse_until_newline())

    def try_parse_assignment(self) -> AssignmentExpression | None:
        assigned_variables = [self.try_parse_assignment_target()]

        if assigned_variables[0] is None:
            return

        whitespace = self.lexer.try_parse_whitespaces()

        eq_sign = self.lexer.try_parse_equal_sign()

        if eq_sign is None:
            self.lexer.give_back([whitespace, eq_sign])
            return

        while True:
            self.lexer.try_parse_whitespaces()
            expression = self.try_parse_assignment_target()
            self.lexer.try_parse_whitespaces()

            if expression is None:
                break

            inner_eq_sign = self.lexer.try_parse_equal_sign()
            self.lexer.try_parse_whitespaces()

            if inner_eq_sign is None:
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
