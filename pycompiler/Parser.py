from __future__ import annotations

import abc
import enum
import string
import typing
import io

from pycompiler import Lexer


class Scope:
    def __init__(self):
        self.parent: Scope | None = None

        self.module_file: str | None = None
        self.class_name_stack: typing.List[str] = []

        self.exposed_type_names: typing.Dict[str, ClassDefinitionNode] = {}

        self.generic_name_stack: typing.Set[str] = set()
        self.variable_name_stack: typing.Set[str] = set()

    def has_name_access(self, name: str) -> bool:
        if name in self.generic_name_stack or name in self.variable_name_stack:
            return True

        return self.parent and self.parent.has_name_access(name)

    def copy(self) -> Scope:
        scope = Scope()
        scope.parent = self
        scope.module_file = self.module_file
        scope.class_name_stack += self.class_name_stack
        scope.exposed_type_names = self.exposed_type_names
        return scope

    def close(self, export_local_name: str | None = None):
        # sourcery skip: remove-empty-nested-block, remove-redundant-if
        if export_local_name:
            pass  # todo: do we want to hint this for warnings?

    def expose_type_name(self, name: str, definition: ClassDefinitionNode):
        assert name != "", "name must not be empty"
        assert name.isidentifier(), "name must be valid identifier"

        full_name = ".".join(self.class_name_stack)

        if full_name:
            full_name += "."

        full_name += name
        self.exposed_type_names[full_name] = definition

    def export_valid_generic(self, name: str):
        """
        Exports a generic name for inner use in the scope

        :param name:
        :return:
        """

    _NO_VALUE = object()

    def export_variable_name(self, name: str, strong_value: typing.Any = _NO_VALUE):
        """
        Exports a variable name in the current scope level

        :param name: the name of the variable
        :param strong_value: optionally the value of the variable; May only be set when
            the value is guaranteed
        """
        self.variable_name_stack.add(name)

    def get_static_value_or_fail(self, name: str):
        pass


class FilledScope:
    def __init__(self, scope: Scope):
        self.scope = scope
        # todo: also allow generic's as targets
        self.generic_name_fillings: typing.List[typing.Dict[str, ClassDefinitionNode]] = [{} for _ in range(len(scope.generic_name_stack))]

    def copy_for_child(self, scope: Scope) -> FilledScope:
        filled_scope = FilledScope(scope)
        filled_scope.generic_name_fillings[:len(self.generic_name_fillings)] = self.generic_name_fillings
        return filled_scope


class ParentAttributeSection(enum.Enum):
    LHS = enum.auto()
    RHS = enum.auto()

    PARAMETER = enum.auto()


class AbstractASTNode(abc.ABC):
    def __init__(self):
        self.scope = None
        self.parent: typing.Tuple[AbstractASTNode, ParentAttributeSection] | None = None

    def try_replace_child(self, original: AbstractASTNode | None, replacement: AbstractASTNode, position: ParentAttributeSection) -> bool:
        return False


class PyNewlineNode(AbstractASTNode):
    def __init__(self, token: Lexer.Token):
        super().__init__()
        self.token = token

    def __eq__(self, other):
        return type(other) == PyNewlineNode and self.token == other.token

    def __repr__(self):
        return "NEWLINE"


class PyCommentNode(AbstractASTNode):
    def __init__(self, base_token: Lexer.Token, inner_string: Lexer.Token):
        super().__init__()
        self.base_token = base_token
        self.inner_string = inner_string

    def __eq__(self, other):
        return type(other) == PyCommentNode and self.base_token == other.base_token and self.inner_string == other.inner_string

    def __repr__(self):
        return f"COMMENT({self.base_token}|{self.inner_string})"


class AssignmentExpression(AbstractASTNode):
    def __init__(self, lhs: typing.List[AbstractASTNode], eq_sign: Lexer.Token, rhs: AbstractASTNode):
        super().__init__()
        self.lhs = lhs
        self.eq_sign = eq_sign
        self.rhs = rhs

    def __eq__(self, other):
        return type(other) == AssignmentExpression and self.lhs == other.lhs and self.eq_sign == other.eq_sign and self.rhs == other.rhs

    def __repr__(self):
        return f"ASSIGNMENT({self.lhs}|{self.eq_sign}|{self.rhs})"

    def try_replace_child(self, original: AbstractASTNode | None, replacement: AbstractASTNode, position: ParentAttributeSection) -> bool:
        if position == ParentAttributeSection.LHS:
            if original is None:
                return False

            self.lhs.replace(original, replacement)
        elif position == ParentAttributeSection.RHS:
            self.rhs = replacement
        else:
            return False
        return True


class NameAccessExpression(AbstractASTNode):
    def __init__(self, name: Lexer.Token):
        super().__init__()
        self.name = name

    def __eq__(self, other):
        return type(other) == NameAccessExpression and self.name == other.name

    def __repr__(self):
        return f"VARIABLE({self.name})"


class ConstantAccessExpression(AbstractASTNode):
    def __init__(self, value: typing.Any, token=None):
        super().__init__()
        self.value = value
        self.token = token

    def __eq__(self, other):
        return type(other) == ConstantAccessExpression and self.value == other.value

    def __repr__(self):
        return f"CONSTANT({repr(self.value)})"


class AttributeExpression(AbstractASTNode):
    def __init__(self, base: AbstractASTNode, dot: Lexer.Token, attribute: Lexer.Token):
        super().__init__()
        self.base = base
        self.dot = dot
        self.attribute = attribute

    def __eq__(self, other):
        return type(other) == AttributeExpression and self.base == other.base and self.dot == other.dot and self.attribute == other.attribute

    def __repr__(self):
        return f"ATTRIBUTE({self.base}|{self.dot}|{self.attribute})"

    def try_replace_child(self, original: AbstractASTNode | None, replacement: AbstractASTNode, position: ParentAttributeSection) -> bool:
        if position != ParentAttributeSection.LHS:
            return False

        self.base = replacement
        return True


class SubscriptionExpression(AbstractASTNode):
    def __init__(self, base: AbstractASTNode, lhs_bracket: Lexer.Token, expression: AbstractASTNode, rhs_bracket: Lexer.Token):
        super().__init__()
        self.base = base
        self.lhs_bracket = lhs_bracket
        self.expression = expression
        self.rhs_bracket = rhs_bracket

    def __eq__(self, other):
        return type(other) == SubscriptionExpression and self.base == other.base and self.lhs_bracket == other.lhs_bracket and self.expression == other.expression and self.rhs_bracket == other.rhs_bracket

    def __repr__(self):
        return f"SUBSCRIPTION({self.base}|{self.lhs_bracket}|{self.expression}|{self.rhs_bracket})"

    def try_replace_child(self, original: AbstractASTNode | None, replacement: AbstractASTNode, position: ParentAttributeSection) -> bool:
        if position == ParentAttributeSection.LHS:
            self.base = replacement
        elif position == ParentAttributeSection.RHS:
            self.expression = replacement
        else:
            return False

        return True


class FunctionDefinitionNode(AbstractASTNode):
    class ParameterType(enum.Enum):
        NORMAL = enum.auto()
        KEYWORD = enum.auto()
        STAR = enum.auto()
        STAR_STAR = enum.auto()

    class FunctionDefinitionParameter(AbstractASTNode):
        def __init__(self, name: Lexer.Token, mode: FunctionDefinitionNode.ParameterType, hint=None, default=None):
            super().__init__()

            assert (default is not None) == (mode == FunctionDefinitionNode.ParameterType.KEYWORD)

            self.name = name
            self.mode = mode
            self.hint = hint
            self.default = default

        def __eq__(self, other):
            return type(other) == FunctionDefinitionNode.FunctionDefinitionParameter and self.name == other.name and self.mode == other.mode and self.hint == other.hint and self.default == other.default

        def __repr__(self):
            return f"PARAMETER({self.name}|{self.mode}|{self.hint}|{self.default})"

    def __init__(self, name: Lexer.Token, generics: typing.List[Lexer.Token], parameters: typing.List[FunctionDefinitionNode.FunctionDefinitionParameter], body: typing.List[AbstractASTNode]):
        super().__init__()
        self.name = name
        self.generics = generics
        self.parameters = parameters
        self.body = body

    def __eq__(self, other):
        return type(other) == FunctionDefinitionNode and self.name == other.name and self.generics == other.generics and self.parameters == other.parameters and self.body == other.body

    def __repr__(self):
        return f"FUNCTION({self.name}|{self.generics}|{self.parameters}|{self.body})"



class ClassDefinitionNode(AbstractASTNode):
    pass


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
        elif obj_type == FunctionDefinitionNode:
            return self.visit_function_definition(obj)
        elif obj_type == FunctionDefinitionNode.FunctionDefinitionParameter:
            return self.visit_function_definition_parameter(obj)
        elif obj_type == ClassDefinitionNode:
            return self.visit_class_definition(obj)
        elif obj_type == ConstantAccessExpression:
            return self.visit_constant(obj)
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

    def visit_function_definition(self, node: FunctionDefinitionNode):
        for param in node.parameters:
            self.visit_function_definition_parameter(param)

        for body_node in node.body:
            self.visit_any(body_node)

    def visit_function_definition_parameter(self, node: FunctionDefinitionNode.FunctionDefinitionParameter):
        pass

    def visit_class_definition(self, node: ClassDefinitionNode):
        pass

    def visit_constant(self, constant: ConstantAccessExpression):
        pass


class Parser:
    def __init__(self, source: str):
        self.source = source
        self.lexer = Lexer.Lexer(source)
        self.indent_level = 0
        self.indent_markers: str | None = None

    def parse(self) -> typing.List[AbstractASTNode]:
        ast_stream: typing.List[AbstractASTNode] = []

        while self.lexer.has_text():
            while newline := self.lexer.try_parse_newline():
                ast_stream.append(PyNewlineNode(newline))

            node = self.parse_line()

            if node is not None:
                ast_stream.append(node)
            else:
                raise SyntaxError

        return ast_stream

    def parse_line(self) -> AbstractASTNode | None:
        if comment := self.try_parse_comment():
            return comment

        if self.indent_level:
            empty = self.lexer.try_parse_whitespaces()
            if self.indent_markers:
                if not empty or empty.text[:self.indent_level] != self.indent_markers * self.indent_level:
                    raise IndentationError

            elif self.indent_level:
                if not empty or not empty.text:
                    raise IndentationError(empty)

                self.indent_markers = empty.text[0]

                if empty.text[:self.indent_level] != self.indent_markers * self.indent_level:
                    raise IndentationError

        if function := self.try_parse_function_definition():
            return function

        if assignment := self.try_parse_assignment():
            return assignment

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
            c = self.lexer.get_chars(1)
            self.lexer.give_back(c)

            if not c:
                return

            if c.isdigit() or c == "-" or c == ".":
                base = self.try_parse_integer_or_float()

            elif c == "'":
                base = self.parse_quoted_string("'")
            elif c == '"':
                base = self.parse_quoted_string('"')
            else:
                return

        else:
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

    def try_parse_type_hint(self):
        return self.try_parse_expression()  # todo: do something more fancy here!

    def parse_quoted_string(self, quote_type: str) -> ConstantAccessExpression:
        self.lexer.get_chars(1)
        text = ""
        escapes = 0

        while (c := self.lexer.get_chars(1)) != quote_type or escapes % 2 == 1:
            if c is None:
                raise SyntaxError

            if c == "\\":
                escapes += 1

                if escapes % 2 == 0:
                    text += c

            elif c == "\n":
                raise SyntaxError
            else:
                escapes = 0
                text += c

        if text == "":
            c = self.lexer.get_chars(1)

            if c == quote_type:
                return self.parse_multiline_quoted_string(quote_type)
            else:
                self.lexer.give_back(c)

        return ConstantAccessExpression(text)

    def parse_multiline_quoted_string(self, quote_type: str) -> ConstantAccessExpression:
        text = ""
        escapes = 0
        quotes = 0

        while True:
            c = self.lexer.get_chars(1)

            if c is None:
                raise SyntaxError((c, quotes))

            if c == "\\":
                escapes += 1
                quotes = 0

            elif c == quote_type:
                if quotes == 2:
                    break

                if escapes:
                    escapes -= 1
                else:
                    quotes += 1

            else:
                escapes = 0
                quotes = 0

            text += c

        text = text.removesuffix(quote_type * 2)

        return ConstantAccessExpression(text)

    def try_parse_integer_or_float(self) -> ConstantAccessExpression:
        c = self.lexer.get_chars(1)
        text = c

        while True:
            c = self.lexer.get_chars(1)

            if c and c.isdigit():
                text += c
            elif c == "." and "." not in text:
                text += c
            else:
                break

        self.lexer.give_back(c)
        return ConstantAccessExpression(int(text) if "." not in text else float(text))

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

    # def <name>['[' <generic parameters> ']'] '(' <parameters, some with *, ** or =, some with type hints> ')':
    def try_parse_function_definition(self) -> FunctionDefinitionNode | None:
        def_token = self.lexer.get_chars(len("def "))

        if def_token != "def ":
            self.lexer.give_back(def_token)
            return

        self.lexer.try_parse_whitespaces()

        function_name = self.lexer.try_parse_identifier()

        self.lexer.try_parse_whitespaces()

        generic_names: typing.List[Lexer.Token] = []
        duplicate_generic_check = set()

        # Generic Attribute
        if self.lexer.inspect_chars(1) == "[":
            self.lexer.get_chars(1)
            self.lexer.try_parse_whitespaces()

            if self.lexer.inspect_chars(1) != "]":
                while (
                    name := self.lexer.try_parse_identifier()
                ) and name is not None:
                    if name.text in duplicate_generic_check:
                        raise NameError("duplicate generic name found in function declaration")

                    generic_names.append(name)
                    duplicate_generic_check.add(name.text)
                    self.lexer.try_parse_whitespaces(include_newline=True)

                    if self.lexer.inspect_chars(1) != ",":
                        break

                    self.lexer.get_chars(1)
                    self.lexer.try_parse_whitespaces(include_newline=True)

                self.lexer.try_parse_whitespaces(include_newline=True)

            if self.lexer.get_chars(1) != "]":
                raise SyntaxError("Did you forgot to close the '['?")

        self.lexer.try_parse_whitespaces(include_newline=True)

        if self.lexer.get_chars(1) != "(":
            raise SyntaxError("expected '(' after <function name> or <generic parameters>")

        parameters = []
        duplicate_parameter_check = set()

        while self.lexer.inspect_chars(1) != ")":
            self.lexer.try_parse_whitespaces(include_newline=True)

            if self.lexer.inspect_chars(2) == "**":
                self.lexer.get_chars(2)
                self.lexer.try_parse_whitespaces()

                name = self.lexer.try_parse_identifier()

                if name is None:
                    raise SyntaxError

                if name.text in duplicate_generic_check:
                    raise NameError("duplicate parameter name!")

                self.lexer.try_parse_whitespaces()

                hint = None
                if self.lexer.inspect_chars(1) == ":":
                    self.lexer.get_chars(1)
                    self.lexer.try_parse_whitespaces()
                    hint = self.try_parse_type_hint()

                    if hint is None:
                        raise SyntaxError

                parameters.append(FunctionDefinitionNode.FunctionDefinitionParameter(
                    name,
                    FunctionDefinitionNode.ParameterType.STAR_STAR,
                    hint=hint,
                ))
                duplicate_parameter_check.add(name.text)

            elif self.lexer.inspect_chars(1) == "*":
                self.lexer.get_chars(1)
                self.lexer.try_parse_whitespaces()

                name = self.lexer.try_parse_identifier()

                if name is None:
                    raise SyntaxError

                if name.text in duplicate_generic_check:
                    raise NameError("duplicate parameter name!")

                self.lexer.try_parse_whitespaces()

                hint = None
                if self.lexer.inspect_chars(1) == ":":
                    self.lexer.get_chars(1)
                    self.lexer.try_parse_whitespaces()
                    hint = self.try_parse_type_hint()

                    if hint is None:
                        raise SyntaxError

                parameters.append(FunctionDefinitionNode.FunctionDefinitionParameter(
                    name,
                    FunctionDefinitionNode.ParameterType.STAR,
                    hint=hint,
                ))
                duplicate_parameter_check.add(name.text)

            else:
                name = self.lexer.try_parse_identifier()
                if name is None:
                    raise SyntaxError

                if name.text in duplicate_generic_check:
                    raise NameError("duplicate parameter name!")

                self.lexer.try_parse_whitespaces()

                hint = None
                if self.lexer.inspect_chars(1) == ":":
                    self.lexer.get_chars(1)
                    self.lexer.try_parse_whitespaces()
                    hint = self.try_parse_type_hint()

                    if hint is None:
                        raise SyntaxError

                self.lexer.try_parse_whitespaces()

                if self.lexer.inspect_chars(1) == "=":
                    self.lexer.get_chars(1)
                    default = self.try_parse_expression()

                    if default is None:
                        raise SyntaxError

                    parameters.append(FunctionDefinitionNode.FunctionDefinitionParameter(
                        name,
                        FunctionDefinitionNode.ParameterType.KEYWORD,
                        hint=hint,
                        default=default
                    ))
                    duplicate_parameter_check.add(name.text)
                else:
                    parameters.append(FunctionDefinitionNode.FunctionDefinitionParameter(
                        name,
                        FunctionDefinitionNode.ParameterType.NORMAL,
                        hint=hint,
                    ))
                    duplicate_parameter_check.add(name.text)

        if self.lexer.get_chars(1) != ")":
            raise SyntaxError("expected ')' after <parameter list>")

        self.lexer.try_parse_whitespaces()

        if self.lexer.get_chars(1) != ":":
            raise SyntaxError("expected ':' after')'")

        self.lexer.try_parse_whitespaces()

        if self.lexer.inspect_chars(1) != "\n":
            body = [
                self.parse_line()
            ]
        else:
            self.indent_level += 1
            body = self.parse()

            if len(body) == 0:
                raise SyntaxError("expected <body>")

            self.indent_level -= 1

        return FunctionDefinitionNode(
            function_name,
            generic_names,
            parameters,
            body,
        )
