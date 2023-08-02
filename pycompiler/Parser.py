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

        self.strong_variables: typing.Dict[str, object] = {}

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

        if strong_value != self._NO_VALUE:
            self.strong_variables[name] = strong_value

    def get_static_value_or_fail(self, name: str) -> object:
        if name in self.strong_variables:
            return self.strong_variables[name]

        if name in self.variable_name_stack or self.parent is None:
            raise NameError(f"could not resolve static value of variable '{name}'")

        return self.parent.get_static_value_or_fail(name)


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
    BODY = enum.auto()


class CCodeEmitter:
    class CExpressionBuilder:
        def __init__(self):
            self.parent: CCodeEmitter.CExpressionBuilder | None = None
            self.snippets = []

        def add_code(self, code: str):
            self.snippets.append(code)

        def get_result(self) -> str:
            return "".join(self.snippets).rstrip()

    class CFunction(CExpressionBuilder):
        def __init__(self, name: str, parameter_decl: typing.List[str], return_type: str):
            super().__init__()

            self.name = name
            self.parameter_decl = parameter_decl
            self.return_type = return_type

        def get_result(self) -> str:
            lines = super().get_result().split("\n")

            while lines and lines[0].strip() == "":
                lines.pop(0)

            while lines and lines[-1].strip() == "":
                lines.pop(-1)

            for i, line in enumerate(lines):
                lines[i] = "" if line.strip() == "" else f"    {lines[i]}"

            if inner := "\n".join(lines):
                return f"""{self.return_type} {self.name}({' , '.join(self.parameter_decl)}) {{
{inner}
}}"""
            return f"""{self.return_type} {self.name}({' , '.join(self.parameter_decl)}) {{
}}"""

        def get_declaration(self) -> str:
            return f"{self.return_type} {self.name}({' , '.join(self.parameter_decl)});"

    class CSubBlock(CExpressionBuilder):
        def __init__(self, indent=True):
            super().__init__()
            self.indent = indent

        def get_result(self) -> str:
            lines = super().get_result().split("\n")

            while lines and lines[0].strip() == "":
                lines.pop(0)

            while lines and lines[-1].strip() == "":
                lines.pop(-1)

            for i, line in enumerate(lines):
                lines[i] = "" if line.strip() == "" else (f"    {lines[i]}" if self.indent else lines[i])

            return "\n".join(lines)

    def __init__(self):
        self._fresh_name_counter = 0
        self.functions: typing.List[CCodeEmitter.CFunction] = []
        self.includes: typing.List[str] = []
        self.global_variables: typing.List[typing.Tuple[str, str]] = []
        self.add_top_init = []
        self.init_function: CCodeEmitter.CFunction | None = None

    def get_fresh_name(self, base_name: str) -> str:
        name = f"_{base_name}__{self._fresh_name_counter}"
        self._fresh_name_counter += 1
        return name

    def add_function(self, function: CCodeEmitter.CFunction):
        self.functions.append(function)

    def add_include(self, target: str):
        if target not in self.includes:
            self.includes.append(target)

    def add_global_variable(self, var_type: str, var_name: str):
        self.global_variables.append((var_type, var_name))

    def add_to_initializer_top(self, code: str):
        self.add_top_init.append(code)

    def add_to_initializer(self, code: str):
        self.init_function.add_code(code)


class AbstractASTNode(abc.ABC):
    def __init__(self):
        self.scope = None
        self.parent: typing.Tuple[AbstractASTNode, ParentAttributeSection] | None = None

    def try_replace_child(self, original: AbstractASTNode | None, replacement: AbstractASTNode, position: ParentAttributeSection) -> bool:
        return False

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder, is_target=False):
        pass


class AbstractASTNodeExpression(AbstractASTNode, abc.ABC):
    pass


class PyNewlineNode(AbstractASTNode):
    def __init__(self, token: Lexer.Token):
        super().__init__()
        self.token = token

    def __eq__(self, other):
        return type(other) == PyNewlineNode and self.token == other.token

    def __repr__(self):
        return "NEWLINE"

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder, is_target=False):
        context.add_code("\n")


class PyCommentNode(AbstractASTNode):
    def __init__(self, base_token: Lexer.Token, inner_string: Lexer.Token):
        super().__init__()
        self.base_token = base_token
        self.inner_string = inner_string

    def __eq__(self, other):
        return type(other) == PyCommentNode and self.base_token == other.base_token and self.inner_string == other.inner_string

    def __repr__(self):
        return f"COMMENT({self.base_token}|{self.inner_string})"

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder, is_target=False):
        context.add_code(f"// SOURCE: {self.inner_string.text}\n")


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

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder, is_target=False):
        assert len(self.lhs) > 0

        if len(self.lhs) == 1:
            self.lhs[0].emit_c_code(base, context)
            context.add_code(" = ")
            self.rhs.emit_c_code(base, context)
            context.add_code(";")
            return

        # todo: do type stuff
        temporary = base.get_fresh_name("tas")

        context.add_code(f"PyObjectContainer* {temporary} = ")
        self.rhs.emit_c_code(base, context)
        context.add_code(";\n")

        for target in self.lhs:
            target.emit_c_code(base, context, is_target=True)
            context.add_code(f" = {temporary};")


class NameAccessExpression(AbstractASTNodeExpression):
    def __init__(self, name: Lexer.Token):
        super().__init__()
        self.name = name

    def __eq__(self, other):
        return type(other) == NameAccessExpression and self.name == other.name

    def __repr__(self):
        return f"VARIABLE({self.name})"

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder, is_target=False):
        if is_target:
            context.add_code(f"PyObjectContainer* {self.name.text}")
        else:
            context.add_code(self.name.text)


class ConstantAccessExpression(AbstractASTNodeExpression):
    def __init__(self, value: typing.Any, token=None):
        super().__init__()
        self.value = value
        self.token = token

    def __eq__(self, other):
        return type(other) == ConstantAccessExpression and self.value == other.value

    def __repr__(self):
        return f"CONSTANT({repr(self.value)})"

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder, is_target=False):
        if isinstance(self.value, int):
            context.add_code(f"PY_createInteger({self.value})")
        else:
            raise NotImplementedError(self.value)


class AttributeExpression(AbstractASTNodeExpression):
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

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder, is_target=False):
        if is_target:
            temporary = base.get_fresh_name("temp")
            context.parent.add_code(f"PyObjectContainer* {temporary} = ")
            context.add_code(f";\nPY_setObjectAttributeByName(")
            self.base.emit_c_code(base, context)
            context.add_code(f", {temporary}, \"{self.attribute.text}\")")

        else:
            context.add_code("PY_getObjectAttributeByNameOrStatic(")

            self.base.emit_c_code(base, context)
            context.add_code(f", \"{self.attribute.text}\")")


class SubscriptionExpression(AbstractASTNodeExpression):
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

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder, is_target=False):
        if not is_target:
            context.add_code("PY_GetSubscriptionValue(")
            self.base.emit_c_code(base, context)
            context.add_code(", ")
            self.expression.emit_c_code(base, context)
            context.add_code(")")
        else:
            temporary = base.get_fresh_name("temp")
            context.parent.add_code(f"PyObjectContainer* {temporary} = ")
            context.add_code(f";\nPY_SetSubscriptionValue(")
            self.base.emit_c_code(base, context)
            context.add_code(f", {temporary}, ")
            self.expression.emit_c_code(base, context)
            context.add_code(")")


class CallExpression(AbstractASTNodeExpression):
    class ParameterType(enum.Enum):
        NORMAL = enum.auto()
        KEYWORD = enum.auto()
        STAR = enum.auto()
        STAR_STAR = enum.auto()

    class CallExpressionArgument(AbstractASTNode):
        def __init__(self, value: AbstractASTNode, mode: CallExpression.ParameterType, key: Lexer.Token = None):
            super().__init__()

            assert (mode == CallExpression.ParameterType.KEYWORD) == (key is not None)

            self.value = value
            self.mode = mode
            self.key = key

        def __eq__(self, other):
            return type(other) == CallExpression.CallExpressionArgument and self.value == other.value and self.mode == other.mode and self.key == other.key

        def __repr__(self):
            return f"ARG({self.value}|{self.mode}|{self.key})"

        def try_replace_child(self, original: AbstractASTNode | None, replacement: AbstractASTNode, position: ParentAttributeSection) -> bool:
            if position == ParentAttributeSection.PARAMETER:
                self.value = replacement
                return True
            return False

    def __init__(self, base: AbstractASTNode, generics: typing.List[AbstractASTNode], l_bracket: Lexer.Token, args: typing.List[CallExpression.CallExpressionArgument], r_bracket: Lexer.Token):
        super().__init__()
        self.base = base
        self.generics = generics
        self.l_bracket = l_bracket
        self.args = args
        self.r_bracket = r_bracket

    def __eq__(self, other):
        return type(other) == CallExpression and self.base == other.base and self.generics == other.generics and self.l_bracket == other.l_bracket and self.args == other.args and self.r_bracket == other.r_bracket

    def __repr__(self):
        return f"CALL({self.base}|{self.generics}|{self.l_bracket}|{self.args}|{self.r_bracket})"

    def try_replace_child(self, original: AbstractASTNode | None, replacement: AbstractASTNode, position: ParentAttributeSection) -> bool:
        if position == ParentAttributeSection.LHS:
            self.base = replacement
        elif position == ParentAttributeSection.PARAMETER:
            self.args.replace(original, replacement)
        else:
            return False
        return True

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder, is_target=False):
        if not isinstance(self.base, ConstantAccessExpression):
            self.emit_c_code_any_call(base, context)
            return

        obj = typing.cast(ConstantAccessExpression, self.base).value

        if isinstance(obj, FunctionDefinitionNode):
            func_name = obj.name.text
        elif isinstance(obj, Lexer.Token):
            func_name = obj.text
        elif isinstance(obj, ClassDefinitionNode):
            self.emit_c_code_constructor(base, context)
            return
        else:
            raise NotImplementedError(obj)

        context.add_code(f"{func_name} (")

        for arg in self.args:
            arg.emit_c_code(base, context)
            context.add_code(" , ")

        context.add_code(")")

    def emit_c_code_constructor(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        temporary = base.get_fresh_name("obj_instance")
        constructor = base.get_fresh_name("constructor")
        cls: ClassDefinitionNode = typing.cast(ClassDefinitionNode, typing.cast(ConstantAccessExpression, self.base).value)

        args = ""
        if self.args:
            args = base.get_fresh_name("args")

            context.parent.add_code(f"PyObjectContainer* {args}[{len(self.args)}];")
            for i, arg in enumerate(self.args):
                context.parent.add_code(f"{args}[{i}] = ")
                arg.emit_c_code(base, context.parent)
                context.parent.add_code(";\n")

        context.parent.add_code(f"""
PyObjectContainer* {temporary} = PY_createClassInstance(PY_CLASS_{cls.name.text});
PyObjectContainer* {constructor} = PY_getObjectAttributeByNameOrStatic({temporary}, "__init__");

assert({constructor} != NULL);
PY_invokeBoxedMethod({constructor}, NULL, {len(self.args)}, {args if self.args else 'NULL'});
DECREF({constructor});
""")

        context.add_code(temporary)

    def emit_c_code_any_call(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        context.add_code("PY_invokeBoxedMethod(")
        self.base.emit_c_code(base, context)

        if self.args:
            args = base.get_fresh_name("args")

            context.parent.add_code(f"PyObjectContainer* {args}[{len(self.args)}];")
            for i, arg in enumerate(self.args):
                context.parent.add_code(f"{args}[{i}] = ")
                arg.emit_c_code(base, context.parent)
                context.parent.add_code(";\n")

            context.add_code(f", NULL, {len(self.args)}, {args})")
        else:
            context.add_code(", NULL, 0, NULL)")


class ReturnStatement(AbstractASTNode):
    def __init__(self, return_value: AbstractASTNode):
        super().__init__()
        self.return_value = return_value

    def __eq__(self, other):
        return type(other) == ReturnStatement and self.return_value == other.return_value

    def __repr__(self):
        return f"RETURN({self.return_value})"

    def try_replace_child(self, original: AbstractASTNode | None, replacement: AbstractASTNode, position: ParentAttributeSection) -> bool:
        if position == ParentAttributeSection.RHS:
            self.return_value = replacement
            return True
        return False

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder, is_target=False):
        context.add_code("return ")
        self.return_value.emit_c_code(base, context)
        context.add_code(";")


class FunctionDefinitionNode(AbstractASTNode):
    class ParameterType(enum.Enum):
        NORMAL = enum.auto()
        KEYWORD = enum.auto()
        STAR = enum.auto()
        STAR_STAR = enum.auto()

    class FunctionDefinitionParameter(AbstractASTNode):
        def __init__(self, name: Lexer.Token, mode: FunctionDefinitionNode.ParameterType, hint=None, default: AbstractASTNode = None):
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

        def try_replace_child(self, original: AbstractASTNode | None, replacement: AbstractASTNode, position: ParentAttributeSection) -> bool:
            if self.mode == FunctionDefinitionNode.ParameterType.KEYWORD and position == ParentAttributeSection.PARAMETER:
                self.default = replacement
                return True
            return False

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

    def try_replace_child(self, original: AbstractASTNode | None, replacement: AbstractASTNode, position: ParentAttributeSection) -> bool:
        return False  # nothing to replace, needs to be replaced in the arg itself

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder, is_target=False):
        func_name = self.name.text  # todo: do better here!

        func = base.CFunction(func_name, [f"PyObjectContainer* {param.name.text}" for param in self.parameters], "PyObjectContainer*")
        base.add_function(func)

        if len(self.body) > 0:
            args = [arg.name.text for arg in self.parameters]

            for var in self.body[0].scope.variable_name_stack:
                if var not in args:
                    func.add_code(f"PyObjectContainer* {var};\n")

        for line in self.body:
            inner_section = CCodeEmitter.CSubBlock(indent=False)
            inner_section.parent = func

            line.emit_c_code(base, inner_section)

            if isinstance(line, AbstractASTNodeExpression):
                inner_section.add_code(";\n")
            else:
                inner_section.add_code("\n")

            func.add_code(inner_section.get_result()+"\n")

        # todo: when bound object method, forward 'self' as first argument!
        base.add_include("<assert.h>")

        safe_name = f"{func_name}_safeWrap"
        safe_func = base.CFunction(safe_name, ["PyObjectContainer* self", "uint8_t argc", "PyObjectContainer** args"], "PyObjectContainer*")
        base.add_function(safe_func)

        # todo: there are other arg types!

        arg_unbox = [f"args[{i}]" for i, param in enumerate(self.parameters)]
        arg_unbox_2 = [f"args[{i}]" for i, param in enumerate(self.parameters[1:])]

        unbox = ' , '.join(arg_unbox)
        unbox_2 = " , ".join(arg_unbox_2)

        safe_func.add_code(
            f"""
if (self == NULL)
{{
    assert(argc == {len(self.parameters)});
    return {func_name}({unbox});
}}
else
{{
    assert(argc == {len(self.parameters) - 1});
    return {func_name}(self{f' , {unbox_2}' if unbox_2 else ''});
}}

"""
        )


class ClassDefinitionNode(AbstractASTNode):
    def __init__(self, name: Lexer.Token, generics: typing.List[Lexer.Token], parents: typing.List[AbstractASTNode], body: typing.List[AbstractASTNode]):
        super().__init__()
        self.name = name
        self.generics = generics
        self.parents = parents
        self.body = body

    def __eq__(self, other):
        return type(other) == ClassDefinitionNode and self.name == other.name and self.generics == other.generics and self.parents == other.parents and self.body == other.body

    def __repr__(self):
        return f"CLASS({self.name}|{self.generics}|{self.parents}|{self.body})"

    def try_replace_child(self, original: AbstractASTNode | None, replacement: AbstractASTNode, position: ParentAttributeSection) -> bool:
        if original is None:
            return False

        if position == ParentAttributeSection.PARAMETER:
            self.parents[self.parents.index(original)] = replacement
            return True
        elif position == ParentAttributeSection.BODY:
            self.body[self.body.index(original)] = replacement
            return True

        return False

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder, is_target=False):
        variable_name = f"PY_CLASS_{self.name.text}"

        base.add_global_variable("PyClassContainer*", variable_name)

        init_class = CCodeEmitter.CFunction(f"PY_CLASS_INIT_{variable_name}", [], "void")
        base.add_function(init_class)

        if len(self.body) > 0:
            external = [
                line.name.text
                for line in self.body
                if isinstance(line, (FunctionDefinitionNode, ClassDefinitionNode))
            ]
            for var in self.body[0].scope.variable_name_stack:
                if var not in external:
                    init_class.add_code(f"PyObjectContainer* {var};\n")

        init_class.add_code(f"""
// Create Class {variable_name} ({self.name.text} in source code)
{variable_name} = PY_createClassContainer("{self.name.text}");
PY_ClassContainer_AllocateParentArray({variable_name}, {len(self.parents)});
""")  # todo: include all the other stuff here!

        init_class.add_code(f"\n// Create Parent Objects for class {self.name.text}\n")
        if self.parents:

            for i, parent in enumerate(self.parents):
                if isinstance(parent, ClassDefinitionNode):
                    init_class.add_code(f"{variable_name} -> parents[{i}] = PY_CLASS_{parent.name.text};\n")
                else:
                    raise NotImplementedError

            init_class.add_code("\n// Attributes\n")

        for line in self.body:
            if isinstance(line, FunctionDefinitionNode):
                print(line)
                init_class.add_code(f"PY_setClassAttributeByNameOrCreate({variable_name}, \"{line.name.text}\", PY_createBoxForFunction({line.name.text}_safeWrap));\n")

        for line in self.body:
            inner_block = CCodeEmitter.CSubBlock(indent=False)
            inner_block.parent = init_class

            line.emit_c_code(base, inner_block)

            if isinstance(line, AbstractASTNodeExpression):
                inner_block.add_code(";\n")
            else:
                inner_block.add_code("\n")

            init_class.add_code(inner_block.get_result()+"\n")

        base.add_to_initializer(f"PY_CLASS_INIT_{variable_name}();")


class WhileStatement(AbstractASTNode):
    def __init__(self, condition: AbstractASTNode, body: typing.List[AbstractASTNode]):
        super().__init__()
        self.condition = condition
        self.body = body

    def __eq__(self, other):
        return type(other) == WhileStatement and self.condition == other.condition and self.body == other.body

    def __repr__(self):
        return f"WHILE({self.condition}|{self.body})"

    def try_replace_child(self, original: AbstractASTNode | None, replacement: AbstractASTNode, position: ParentAttributeSection) -> bool:
        if position == ParentAttributeSection.LHS:
            self.condition = replacement
            return True
        elif position == ParentAttributeSection.BODY and original is not None:
            self.body[self.body.index(original)] = replacement
            return True
        return False

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder, is_target=False):
        context.add_code("\nwhile (PY_getTruthValueOf(")
        self.condition.emit_c_code(base, context)
        context.add_code(")) {\n")

        block = CCodeEmitter.CSubBlock()

        # TODO: indent!
        for line in self.body:
            inner_block = CCodeEmitter.CSubBlock(indent=False)
            inner_block.parent = block

            line.emit_c_code(base, inner_block)

            if isinstance(line, AbstractASTNodeExpression):
                inner_block.add_code(";\n")
            else:
                inner_block.add_code("\n")

            block.add_code(inner_block.get_result() + "\n")

        context.add_code(block.get_result())

        context.add_code("\n}\n")


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
        elif obj_type == CallExpression:
            return self.visit_call_expression(obj)
        elif obj_type == CallExpression.CallExpressionArgument:
            return self.visit_call_argument(obj)
        elif obj_type == FunctionDefinitionNode:
            return self.visit_function_definition(obj)
        elif obj_type == FunctionDefinitionNode.FunctionDefinitionParameter:
            return self.visit_function_definition_parameter(obj)
        elif obj_type == ReturnStatement:
            return self.visit_return_statement(obj)
        elif obj_type == ClassDefinitionNode:
            return self.visit_class_definition(obj)
        elif obj_type == ConstantAccessExpression:
            return self.visit_constant(obj)
        elif obj_type == WhileStatement:
            return self.visit_while_statement(obj)
        else:
            raise RuntimeError(obj)

    def visit_any_list(self, objs: typing.List[AbstractASTNode]):
        return [
            self.visit_any(obj)
            for obj in objs
        ]

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

    def visit_call_expression(self, node: CallExpression):
        return self.visit_any(node.base), [
            self.visit_call_argument(arg)
            for arg in node.args
        ]

    def visit_call_argument(self, arg: CallExpression.CallExpressionArgument):
        return self.visit_any(arg.value),

    def visit_function_definition(self, node: FunctionDefinitionNode):
        return [
            self.visit_function_definition_parameter(param) for param in node.parameters
        ], self.visit_any_list(node.body)

    def visit_function_definition_parameter(self, node: FunctionDefinitionNode.FunctionDefinitionParameter):
        if node.mode == FunctionDefinitionNode.ParameterType.KEYWORD:
            assert node.default is not None

            return self.visit_any(node.default),

        return None,

    def visit_class_definition(self, node: ClassDefinitionNode):
        return self.visit_any_list(node.parents), self.visit_any_list(node.body)

    def visit_constant(self, constant: ConstantAccessExpression):
        pass

    def visit_return_statement(self, return_statement: ReturnStatement):
        return self.visit_any(return_statement.return_value),

    def visit_while_statement(self, while_statement: WhileStatement):
        return self.visit_any(while_statement.condition), self.visit_any_list(while_statement.body)


class Parser:
    def __init__(self, source: str):
        self.source = source
        self.lexer = Lexer.Lexer(source)
        self.indent_level = 0
        self.indent_markers: str | None = None
        self.is_in_function = False
        self.skip_end_check = False

    def parse(self, stop_on_indention_exit=False) -> typing.List[AbstractASTNode]:
        ast_stream: typing.List[AbstractASTNode] = []

        require_indent = True

        while self.lexer.has_text():
            while newline := self.lexer.try_parse_newline():
                ast_stream.append(PyNewlineNode(newline))

            if not self.lexer.has_text():
                break

            try:
                node = self.parse_line(require_indent=require_indent)
            except IndentationError:
                if stop_on_indention_exit:
                    self.skip_end_check = True
                    return ast_stream
                raise

            if not self.skip_end_check:
                self.lexer.try_parse_whitespaces()

                if self.lexer.inspect_chars(1) == ";":
                    self.lexer.get_chars(1)
                    self.lexer.try_parse_whitespaces()
                    require_indent = False
                else:
                    require_indent = True

                    if self.lexer.inspect_chars(1) not in ("\n", None):
                        for node in ast_stream:
                            print(node)
                        raise SyntaxError(f"expected <newline> or ';' after expression, got {repr(self.lexer.get_chars(1))}")

            self.skip_end_check = False

            if node is not None:
                ast_stream.append(node)
            else:
                print(repr(self.lexer.file[self.lexer.file_cursor:]), len(self.lexer.file[self.lexer.file_cursor:]))
                raise SyntaxError("no valid instruction found")

        return ast_stream

    def emit_c_code(self, expr: typing.List[AbstractASTNode] = None) -> str:
        from pycompiler.TypeResolver import ResolveParentAttribute, ScopeGeneratorVisitor, LocalNameValidator, ResolveStaticNames

        scope = Scope()

        if expr is None:
            expr = self.parse()

        ResolveParentAttribute().visit_any_list(expr)
        ScopeGeneratorVisitor(scope).visit_any_list(expr)
        LocalNameValidator().visit_any_list(expr)
        ResolveStaticNames().visit_any_list(expr)

        builder = CCodeEmitter()
        main = builder.CFunction("_initialise", [], "int")
        builder.add_function(main)
        builder.init_function = main

        if expr:
            skip_names = [
                line.name.text
                for line in expr
                if isinstance(line, (FunctionDefinitionNode, ClassDefinitionNode))
            ]

            for var in expr[0].scope.variable_name_stack:
                if var not in skip_names:
                    main.add_code(f"PyObjectContainer* {var};\n")

        for line in expr:
            inner_block = CCodeEmitter.CSubBlock(indent=False)
            inner_block.parent = main

            line.emit_c_code(builder, inner_block)

            if isinstance(line, AbstractASTNodeExpression):
                inner_block.add_code(";\n")
            else:
                inner_block.add_code("\n")

            main.add_code(inner_block.get_result() + "\n")

        code = "#include \"pyinclude.h\"\n\n// code compiled from python to c via PyCodeCompiler\n\n"

        for include in builder.includes:
            code += f"#include {include}\n"

        if builder.includes:
            code += "\n\n"

        for func in builder.functions:
            code += func.get_declaration()
            code += "\n"

        if builder.global_variables:
            code += "\n// Global Variables\n"
            for var_type, var_name in builder.global_variables:
                code += f"{var_type} {var_name};\n"

            code += "\n"

        code += "\n\n// implementations\n\n"

        main.snippets = builder.add_top_init + ["\n\n"] + main.snippets

        for func in builder.functions:
            code += func.get_result()
            code += "\n\n"

        return code

    def parse_line(self, require_indent=True, include_comment=True) -> AbstractASTNode | None:
        if include_comment and (comment := self.try_parse_comment()):
            return comment

        if self.indent_level and require_indent:
            empty = self.lexer.try_parse_whitespaces()

            if self.lexer.inspect_chars(1) == "\n":
                return

            if self.indent_markers:
                if not empty or empty.text != self.indent_markers * self.indent_level:
                    print("not enough", repr(empty.text) if empty else None, repr(self.indent_markers), self.indent_level)
                    self.lexer.give_back(empty)
                    raise IndentationError

            else:
                if not empty or not empty.text:
                    print("no indent")
                    self.lexer.give_back(empty)
                    raise IndentationError(empty)

                self.indent_markers = empty.text[: len(empty.text) // self.indent_level]

                if empty.text != self.indent_markers * self.indent_level:
                    print("not enough for level")
                    self.lexer.give_back(empty)
                    raise IndentationError

        if function := self.try_parse_function_definition():
            return function

        if cls := self.try_parse_class_node():
            return cls

        if while_statement := self.try_parse_while_statement():
            return while_statement

        if self.is_in_function and (return_statement := self.try_parse_return_statement()):
            return return_statement

        if assignment := self.try_parse_assignment():
            return assignment

        if expression := self.try_parse_expression():
            return expression

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

            elif opening_bracket := self.lexer.try_parse_opening_round_bracket():
                base = self.parse_function_call(base, opening_bracket)

            else:
                break

        self.lexer.try_parse_whitespaces()
        return base

    def parse_function_call(self, base: AbstractASTNode, opening_bracket: Lexer.Token) -> CallExpression:
        generics = []  # todo: load from base if it is an subscription access
        args = []

        while not (closing_bracket := self.lexer.try_parse_closing_round_bracket()):
            self.lexer.try_parse_whitespaces(include_newline=True)

            arg = None

            if self.lexer.inspect_chars(1) == "*":
                if self.lexer.inspect_chars(2) == "**":
                    self.lexer.get_chars(2)

                    expr = self.try_parse_expression()

                    if expr is None:
                        raise SyntaxError

                    arg = CallExpression.CallExpressionArgument(
                        expr,
                        CallExpression.ParameterType.STAR_STAR,
                    )

                else:
                    self.lexer.get_chars(1)

                    expr = self.try_parse_expression()

                    if expr is None:
                        raise SyntaxError

                    arg = CallExpression.CallExpressionArgument(
                        expr,
                        CallExpression.ParameterType.STAR,
                    )

            else:
                self.lexer.save_state()

                identifier = self.lexer.try_parse_identifier()

                if identifier is not None:
                    self.lexer.try_parse_whitespaces(include_newline=True)
                    if self.lexer.inspect_chars(1) == "=":
                        self.lexer.get_chars(1)

                        expr = self.try_parse_expression()

                        if expr is None:
                            raise SyntaxError

                        arg = CallExpression.CallExpressionArgument(
                            expr,
                            CallExpression.ParameterType.KEYWORD,
                            key=identifier,
                        )

                        self.lexer.discard_save_state()


                if arg is None:
                    self.lexer.rollback_state()
                    expr = self.try_parse_expression()

                    if expr is None:
                        raise SyntaxError

                    arg = CallExpression.CallExpressionArgument(
                        expr,
                        CallExpression.ParameterType.NORMAL,
                    )

            args.append(arg)

            self.lexer.try_parse_whitespaces()

            if self.lexer.inspect_chars(1) != ",":
                if not (closing_bracket := self.lexer.try_parse_closing_round_bracket()):
                    raise SyntaxError

                break

            self.lexer.get_chars(1)

        return CallExpression(
            base,
            generics,
            opening_bracket,
            args,
            closing_bracket,
        )

    def try_parse_type_hint(self):
        return self.try_parse_expression()  # todo: do something more fancy here!

    def try_parse_return_statement(self) -> ReturnStatement | None:
        keyword = self.lexer.get_chars(len("return "))

        if keyword != "return ":
            self.lexer.give_back(keyword)
            return

        return_value = self.try_parse_expression()

        if return_value is None:
            raise SyntaxError("expected <expression> after 'return'")

        return ReturnStatement(return_value)


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
        self.lexer.save_state()
        assigned_variables = [self.try_parse_assignment_target()]

        if assigned_variables[0] is None:
            self.lexer.rollback_state()
            return

        self.lexer.try_parse_whitespaces()

        eq_sign = self.lexer.try_parse_equal_sign()

        if eq_sign is None:
            self.lexer.rollback_state()
            return

        self.lexer.discard_save_state()

        while True:
            self.lexer.save_state()
            self.lexer.try_parse_whitespaces()
            expression = self.try_parse_assignment_target()
            self.lexer.try_parse_whitespaces()

            if expression is None:
                self.lexer.discard_save_state()
                break

            inner_eq_sign = self.lexer.try_parse_equal_sign()
            self.lexer.try_parse_whitespaces()

            if inner_eq_sign is None:
                self.lexer.rollback_state()
                break

            assigned_variables.append(expression)
            self.lexer.discard_save_state()
            # todo: store equal sign somewhere!

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

        if function_name is None:
            raise SyntaxError("expected <function name>")

        self.lexer.try_parse_whitespaces()

        generic_names: typing.List[Lexer.Token] = []
        duplicate_name_check = set()

        # Generic Attribute
        if self.lexer.inspect_chars(1) == "[":
            self.lexer.get_chars(1)
            self.lexer.try_parse_whitespaces(include_newline=True)

            if self.lexer.inspect_chars(1) != "]":
                generic_names += self.try_parse_generic_parameters(duplicate_name_check)
                self.lexer.try_parse_whitespaces(include_newline=True)

            if self.lexer.get_chars(1) != "]":
                raise SyntaxError("Did you forgot to close the '['?")

        self.lexer.try_parse_whitespaces(include_newline=True)

        if self.lexer.get_chars(1) != "(":
            print(function_name)
            raise SyntaxError("expected '(' after <function name> or <generic parameters>")

        parameters = []

        # todo: add more constraints to order of parameters:
        #   - normal only before keyword args
        #   - star args only after their respective without-star variant
        #   - no duplicate kind of a star
        #   - allow the \ syntax
        while self.lexer.inspect_chars(1) != ")":
            param = self.try_parse_function_parameter()

            if param.name.text in duplicate_name_check:
                raise NameError("duplicate parameter name found")

            duplicate_name_check.add(param.name.text)
            parameters.append(param)

            if self.lexer.inspect_chars(1) != ",":
                break

            self.lexer.get_chars(1)

        if self.lexer.get_chars(1) != ")":
            raise SyntaxError("expected ')' after <parameter list>")

        self.lexer.try_parse_whitespaces()

        if self.lexer.get_chars(1) != ":":
            raise SyntaxError("expected ':' after')'")

        self.lexer.try_parse_whitespaces()

        prev_in_function = self.is_in_function
        self.is_in_function = True

        if self.lexer.inspect_chars(1) != "\n":
            body = [
                self.parse_line(include_comment=False)
            ]
        else:
            self.indent_level += 1
            body = self.parse(stop_on_indention_exit=True)

            if len(body) == 0:
                raise SyntaxError("expected <body>")

            self.indent_level -= 1

        self.is_in_function = prev_in_function

        return FunctionDefinitionNode(
            function_name,
            generic_names,
            parameters,
            body,
        )

    def try_parse_generic_parameters(self, duplicate_name_check) -> typing.List[Lexer.Token]:
        generic_names = []

        while (
                name := self.lexer.try_parse_identifier()
        ) and name is not None:
            if name.text in duplicate_name_check:
                raise NameError("duplicate generic name found in function declaration")

            generic_names.append(name)
            duplicate_name_check.add(name.text)
            self.lexer.try_parse_whitespaces(include_newline=True)

            if self.lexer.inspect_chars(1) != ",":
                break

            self.lexer.get_chars(1)
            self.lexer.try_parse_whitespaces(include_newline=True)

        self.lexer.try_parse_whitespaces(include_newline=True)

        return generic_names

    def try_parse_function_parameter(self) -> FunctionDefinitionNode.FunctionDefinitionParameter | None:
        self.lexer.try_parse_whitespaces(include_newline=True)

        if self.lexer.inspect_chars(2) == "**":
            param = self.parse_function_parameter_star_star()

        elif self.lexer.inspect_chars(1) == "*":
            param = self.parse_function_parameter_star()
        else:
            param = self.parse_function_parameter_no_star()

        self.lexer.try_parse_whitespaces()
        return param

    def parse_function_parameter_no_star(self):
        name = self.lexer.try_parse_identifier()
        if name is None:
            raise SyntaxError("no parameter name found")

        self.lexer.try_parse_whitespaces()
        if self.lexer.inspect_chars(1) == ":":
            self.lexer.get_chars(1)
            self.lexer.try_parse_whitespaces()
            hint = self.try_parse_type_hint()

            if hint is None:
                raise SyntaxError
        else:
            hint = None

        self.lexer.try_parse_whitespaces()

        if self.lexer.inspect_chars(1) != "=":
            return FunctionDefinitionNode.FunctionDefinitionParameter(
                name,
                FunctionDefinitionNode.ParameterType.NORMAL,
                hint=hint,
            )
        self.lexer.get_chars(1)
        default = self.try_parse_expression()

        if default is None:
            raise SyntaxError

        return FunctionDefinitionNode.FunctionDefinitionParameter(
            name,
            FunctionDefinitionNode.ParameterType.KEYWORD,
            hint=hint,
            default=default,
        )

    def parse_function_parameter_star(self):
        self.lexer.get_chars(1)

        self.lexer.try_parse_whitespaces()
        name = self.lexer.try_parse_identifier()
        if name is None:
            raise SyntaxError

        self.lexer.try_parse_whitespaces()

        if self.lexer.inspect_chars(1) == ":":
            self.lexer.get_chars(1)
            self.lexer.try_parse_whitespaces()
            hint = self.try_parse_type_hint()

            if hint is None:
                raise SyntaxError
        else:
            hint = None

        return FunctionDefinitionNode.FunctionDefinitionParameter(
            name,
            FunctionDefinitionNode.ParameterType.STAR,
            hint=hint,
        )

    def parse_function_parameter_star_star(self):
        self.lexer.get_chars(2)
        self.lexer.try_parse_whitespaces()

        name = self.lexer.try_parse_identifier()
        if name is None:
            raise SyntaxError

        self.lexer.try_parse_whitespaces()
        if self.lexer.inspect_chars(1) == ":":
            self.lexer.get_chars(1)
            self.lexer.try_parse_whitespaces()
            hint = self.try_parse_type_hint()

            if hint is None:
                raise SyntaxError
        else:
            hint = None

        return FunctionDefinitionNode.FunctionDefinitionParameter(
            name,
            FunctionDefinitionNode.ParameterType.STAR_STAR,
            hint=hint,
        )

    def try_parse_class_node(self) -> ClassDefinitionNode | None:
        # class <xy> ['[' <generics> ']'] '(' <parent expressions> ')' ':' ...
        class_token = self.lexer.get_chars(len("class "))

        if class_token != "class ":
            self.lexer.give_back(class_token)
            return

        self.lexer.try_parse_whitespaces()

        class_name = self.lexer.try_parse_identifier()
        if class_name is None:
            raise SyntaxError("expected <class name>")

        generics = []
        if self.lexer.try_parse_opening_square_bracket():
            generics = self.try_parse_generic_parameters(set())

            if not self.lexer.try_parse_closing_square_bracket():
                raise SyntaxError("missing ']'")

        self.lexer.try_parse_whitespaces()

        parents = []
        if self.lexer.try_parse_opening_round_bracket():
            while not self.lexer.try_parse_closing_round_bracket():
                self.lexer.try_parse_whitespaces()
                expression = self.try_parse_expression()

                parents.append(expression)

                if self.lexer.inspect_chars(1) != ",":
                    if not self.lexer.try_parse_closing_round_bracket():
                        raise SyntaxError("expected ')'")

                    break

                self.lexer.get_chars(1)

        self.lexer.try_parse_whitespaces()

        if self.lexer.get_chars(1) != ":":
            raise SyntaxError

        self.indent_level += 1
        previous_in_func = self.is_in_function
        self.is_in_function = False
        body = self.parse(stop_on_indention_exit=True)
        self.is_in_function = previous_in_func
        self.indent_level -= 1

        return ClassDefinitionNode(
            class_name,
            generics,
            parents,
            body,
        )

    def try_parse_while_statement(self) -> WhileStatement | None:
        # while <condition>: ...
        while_token = self.lexer.get_chars(len("while "))

        if while_token != "while ":
            self.lexer.give_back(while_token)
            return

        self.lexer.try_parse_whitespaces()

        condition = self.try_parse_expression()

        if condition is None:
            raise SyntaxError("expected <expression> after 'while'")

        if self.lexer.get_chars(1) != ":":
            raise SyntaxError("expected ':' after <condition>")

        self.lexer.try_parse_whitespaces()

        if self.lexer.inspect_chars(1) != "\n":
            body = [
                self.parse_line(include_comment=False)
            ]
        else:
            self.indent_level += 1
            body = self.parse(stop_on_indention_exit=True)

            if len(body) == 0:
                raise SyntaxError("expected <body>")

            self.indent_level -= 1

        return WhileStatement(
            condition,
            body,
        )
