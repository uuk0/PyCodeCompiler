from __future__ import annotations

import abc
import enum
import json
import math
import os.path
import string
import typing
import io

from pycompiler import Lexer
from pycompiler.Lexer import TokenType


class Scope:
    STANDARD_LIBRARY_VALUES: typing.Dict[str, typing.Dict[str | int, object]] = {}
    STANDARD_LIBRARY_MODULES: typing.Dict[str, StandardLibraryModuleReference] = {}

    def __init__(self):
        self._fresh_name_counter = 0
        self.parent: Scope | None = None
        self.global_scope: Scope = self
        self.is_scope_root = False

        self.module_file: str | None = None
        self.class_name_stack: typing.List[str] = []

        self.exposed_type_names: typing.Dict[str, ClassDefinitionNode] = {}

        self.generic_name_stack: typing.Set[str] = set()
        self.variable_name_stack: typing.Set[str] = set()
        self.variable_name_remap: typing.Dict[str, str] = {}
        self.variable_type_map: typing.Dict[str, AbstractDataType | None] = {}

        self.strong_variables: typing.Dict[str, object] = {}
        self.export_locals_to_inner = True

    def set_local_var_type_or_clear(self, name: str, data_type: AbstractDataType):
        if name in self.variable_type_map:
            if self.variable_type_map[name] != data_type:
                # todo: when e.g. using a list, we need to remove some generic variants, but it might still be valid!
                raise ValueError(
                    f"type conflict: '{name}' was declared as data type "
                    f"{self.variable_type_map[name]} and {data_type}, which is a conflict!"
                )
            return
        self.variable_type_map[name] = data_type

    def get_fresh_name(self, base_name: str) -> str:
        if self.parent is not None:
            self.get_fresh_name = self.parent.get_fresh_name
            return self.parent.get_fresh_name(base_name)

        name = f"{base_name}_{self._fresh_name_counter}"
        self._fresh_name_counter += 1
        return name

    def get_normalised_name(self, name: str) -> str:
        name = name.replace("_", "")
        return self.get_fresh_name(name)

    def get_remapped_name(self, name: str) -> str:
        look_for_exposed = self.exposed_type_names

        if name not in self.variable_name_remap:
            if self.parent and not self.is_scope_root:
                parent = self.parent

                while parent:
                    if name in parent.variable_name_remap and (
                        not look_for_exposed or parent.exposed_type_names
                    ):
                        self.variable_name_remap[
                            name
                        ] = result = parent.variable_name_remap[name]
                        return result

                    look_for_exposed = look_for_exposed or parent.exposed_type_names

                    if not parent.is_scope_root:
                        break

                    parent = parent.parent

            self.variable_name_remap[name] = result = self.get_fresh_name(name)
            return result

        return self.variable_name_remap[name]

    def add_remapped_name(self, name: str, remapped: str):
        self.variable_name_remap[name] = remapped

    def has_name_access(self, name: str) -> bool:
        if name in self.generic_name_stack or name in self.variable_name_stack:
            return True

        if not self.parent:
            return name in Scope.STANDARD_LIBRARY_VALUES

        return self.parent.has_name_access(name)

    def copy(self) -> Scope:
        scope = Scope()
        scope.parent = self
        scope.module_file = self.module_file
        scope.class_name_stack += self.class_name_stack
        scope.exposed_type_names = self.exposed_type_names
        scope.global_scope = self.global_scope
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

    def get_static_value_or_fail(self, name: str, arg_count=-1) -> object:
        if name in self.strong_variables:
            return self.strong_variables[name]

        if name in self.variable_name_stack:
            raise NameError(f"could not resolve static value of variable '{name}'")

        if self.parent is None:
            if name in self.STANDARD_LIBRARY_VALUES:
                if arg_count != -1 and arg_count in self.STANDARD_LIBRARY_VALUES[name]:
                    return self.STANDARD_LIBRARY_VALUES[name][arg_count]

                if "*" not in self.STANDARD_LIBRARY_VALUES[name]:
                    raise NameError(
                        f"could not resolve static value of variable '{name}' without explicit arg count"
                    )

                return self.STANDARD_LIBRARY_VALUES[name]["*"]

            raise NameError(f"could not resolve static value of variable '{name}'")

        return self.parent.get_static_value_or_fail(name, arg_count=arg_count)

    def get_module_global_variable_name(self, name: str) -> str | None:
        if name in self.global_scope.variable_name_stack:
            return self.global_scope.get_remapped_name(name)


class FilledScope:
    def __init__(self, scope: Scope):
        self.scope = scope
        # todo: also allow generic's as targets
        self.generic_name_fillings: typing.List[
            typing.Dict[str, ClassDefinitionNode]
        ] = [{} for _ in range(len(scope.generic_name_stack))]

    def copy_for_child(self, scope: Scope) -> FilledScope:
        filled_scope = FilledScope(scope)
        filled_scope.generic_name_fillings[
            : len(self.generic_name_fillings)
        ] = self.generic_name_fillings
        return filled_scope


class ParentAttributeSection(enum.Enum):
    LHS = enum.auto()
    RHS = enum.auto()

    PARAMETER = enum.auto()
    BODY = enum.auto()

    ELSE_BRANCH = enum.auto()


class CCodeEmitter:
    class CExpressionBuilder:
        def __init__(self, break_to_label: str = None):
            self.parent: CCodeEmitter.CExpressionBuilder | None = None
            self.snippets = []
            self.break_to_label: str = break_to_label
            self.indent = True

        def get_statement_builder(self, indent=True) -> CCodeEmitter.CExpressionBuilder:
            raise NotImplementedError

        def exit_statement_and_store(self) -> str:
            raise RuntimeError

        def add_code(self, code: str):
            self.snippets.append(code)

        def get_result(self) -> str:
            return "".join(self.snippets).rstrip()

        def clear(self):
            self.snippets.clear()

    class CFunctionBuilder(CExpressionBuilder):
        def __init__(
            self,
            name: str,
            parameter_decl: typing.List[str],
            return_type: str,
            scope: Scope,
            break_to_label: str = None,
        ):
            super().__init__(break_to_label=break_to_label)

            self.name = name
            self.parameter_decl = parameter_decl
            self.return_type = return_type
            self.scope = scope

        def get_statement_builder(self, indent=True):
            return CCodeEmitter.CStatementBuilder(
                self, indent=indent, break_to_label=self.break_to_label
            )

        def get_result(self) -> str:
            lines = super().get_result().split("\n")

            while lines and lines[0].strip() == "":
                lines.pop(0)

            while lines and lines[-1].strip() == "":
                lines.pop(-1)

            for i, line in enumerate(lines):
                lines[i] = "" if line.strip() == "" else f"    {lines[i]}"

            if inner := "\n".join(lines):
                return f"""{self.return_type} {self.name}({' , '.join(self.parameter_decl) if self.parameter_decl else 'void'}) {{
{inner}
}}"""
            return f"""{self.return_type} {self.name}({' , '.join(self.parameter_decl) if self.parameter_decl else 'void'}) {{
}}"""

        def get_declaration(self) -> str:
            return f"{self.return_type} {self.name}({' , '.join(self.parameter_decl)});"

    class CStatementBuilder(CExpressionBuilder):
        def __init__(
            self,
            parent: CCodeEmitter.CExpressionBuilder = None,
            indent=True,
            break_to_label: str = None,
        ):
            super().__init__(break_to_label=break_to_label)
            self.indent = indent
            self.parent = parent
            self.scope = self.parent.scope if self.parent else None

        def get_statement_builder(self, indent=True):
            return CCodeEmitter.CStatementBuilder(
                self, indent=indent, break_to_label=self.break_to_label
            )

        def __enter__(self):
            return self

        def __exit__(self, exc_type, exc_val, exc_tb):
            self.parent.add_code(self.get_result() + "\n")

        def exit_statement_and_store(self):
            temporary = self.parent.scope.get_fresh_name("temporary")
            self.parent.add_code(f"PyObjectContainer* {temporary} = ")
            self.parent.add_code(self.get_result() + "\n")
            self.parent.add_code(";\n")
            self.clear()
            return temporary

        def get_result(self) -> str:
            lines = super().get_result().split("\n")

            while lines and lines[0].strip() == "":
                lines.pop(0)

            while lines and lines[-1].strip() == "":
                lines.pop(-1)

            for i, line in enumerate(lines):
                lines[i] = (
                    ""
                    if line.strip() == ""
                    else (f"    {lines[i]}" if self.indent else lines[i])
                )

            return "\n".join(lines)

    def __init__(self, scope: Scope = None):
        self.module_name: str = None
        self._fresh_name_counter = 0
        self.functions: typing.List[CCodeEmitter.CFunctionBuilder] = []
        self.includes: typing.List[str] = []
        self.global_variables: typing.List[typing.Tuple[str, str]] = []
        self.add_top_init = []
        self.init_function: CCodeEmitter.CFunctionBuilder | None = None
        self.scope: Scope = scope
        self.scheduled_modules = []

    def get_fresh_name(self, base_name: str) -> str:
        name = f"{base_name}_{self._fresh_name_counter}"
        self._fresh_name_counter += 1
        return name

    def add_function(self, function: CCodeEmitter.CFunctionBuilder):
        self.functions.append(function)

    def add_include(self, target: str):
        if target not in self.includes:
            self.includes.append(target)

    def add_global_variable(self, var_type: str, var_name: str, ignore_error=False):
        if not ignore_error and not var_name.isidentifier():
            raise ValueError(var_name)

        if (var_type, var_name) in self.global_variables:
            return

        # if var_name.startswith("value"):
        #     raise ValueError(var_name)

        self.global_variables.append((var_type, var_name))

    def add_to_initializer_top(self, code: str):
        self.add_top_init.append(code)

    def add_to_initializer(self, code: str):
        self.init_function.add_code(code)


class AbstractDataType:
    pass


INTEGER_DATA_TYPE = AbstractDataType()
FLOAT_DATA_TYPE = AbstractDataType()


class ClassOrSubclassDataType(AbstractDataType):
    def __init__(self, ref: ClassDefinitionNode):
        if isinstance(ref, dict):
            raise ValueError(ref)

        self.ref = ref
        self.generics = []

    def __eq__(self, other):
        return (
            type(other) == type(self)
            and self.ref == other.ref
            and self.generics == other.generics
        )

    def __repr__(self):
        return f"{type(self).__name__}({self.ref}, {self.generics})"


class ClassExactDataType(ClassOrSubclassDataType):
    pass


class AbstractASTNode(abc.ABC):
    def __init__(self):
        self.scope = None
        self.parent: typing.Tuple[AbstractASTNode, ParentAttributeSection] | None = None
        self.static_value_type = None

    def set_parent(self, node: AbstractASTNode, section: ParentAttributeSection):
        self.parent = node, section
        return self

    def try_replace_child(
        self,
        original: AbstractASTNode | None,
        replacement: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        return False

    def try_insert_before(
        self,
        original: AbstractASTNode | None,
        insert: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        return False

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        pass

    def emit_c_code_for_write(
        self,
        base: CCodeEmitter,
        context: CCodeEmitter.CExpressionBuilder,
        value_source: AbstractASTNodeExpression,
    ):
        raise RuntimeError

    def copy(self):
        try:
            return type(self)()
        except:
            raise NotImplementedError(type(self).__name__)


class AbstractASTNodeExpression(AbstractASTNode, abc.ABC):
    pass


class PyNewlineNode(AbstractASTNode):
    def __init__(self, token: Lexer.Token = None):
        super().__init__()
        self.token = token or TokenType.IDENTIFIER("\n")

    def __eq__(self, other):
        return type(other) == PyNewlineNode

    def __repr__(self):
        return "NEWLINE"

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        context.add_code("\n")


class PyCommentNode(AbstractASTNode):
    def __init__(self, base_token: Lexer.Token, inner_string: Lexer.Token):
        super().__init__()
        self.base_token = base_token
        self.inner_string = inner_string

    def __eq__(self, other):
        return (
            type(other) == PyCommentNode
            and self.base_token == other.base_token
            and self.inner_string == other.inner_string
        )

    def __repr__(self):
        return f"COMMENT({self.base_token}|{self.inner_string})"

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        # context.add_code(f"// SOURCE: {self.inner_string.text}\n")
        pass


class PassStatement(AbstractASTNode):
    def __repr__(self):
        return "PASS"

    def __eq__(self, other):
        return type(other) == PassStatement

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        pass


class AssignmentExpression(AbstractASTNode):
    def __init__(
        self,
        lhs: typing.List[AbstractASTNode],
        eq_sign: Lexer.Token,
        rhs: AbstractASTNodeExpression,
    ):
        super().__init__()
        self.lhs = lhs
        self.eq_sign = eq_sign
        self.rhs = rhs

    def __eq__(self, other):
        return (
            type(other) == AssignmentExpression
            and self.lhs == other.lhs
            and self.eq_sign == other.eq_sign
            and self.rhs == other.rhs
        )

    def __repr__(self):
        return f"ASSIGNMENT({self.lhs}|{self.eq_sign}|{self.rhs})"

    def try_replace_child(
        self,
        original: AbstractASTNode | None,
        replacement: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        replacement.parent = self, position
        if position == ParentAttributeSection.LHS:
            if original is None:
                return False

            self.lhs[self.lhs.index(original)] = replacement
        elif position == ParentAttributeSection.RHS:
            self.rhs = replacement
        else:
            return False
        return True

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        assert len(self.lhs) > 0

        if len(self.lhs) == 1:
            self.lhs[0].emit_c_code_for_write(base, context, self.rhs)
            context.add_code(";")
            return

        # todo: do type stuff
        temporary = base.get_fresh_name("tas")

        context.add_code(f"PyObjectContainer* {temporary} = ")
        self.rhs.emit_c_code(base, context)
        context.add_code(";\n")

        for target in self.lhs:
            target.emit_c_code_for_write(
                base, context, GlobalCNameAccessExpression(temporary)
            )


class NameAccessExpression(AbstractASTNodeExpression):
    def __init__(self, name: Lexer.Token | str):
        super().__init__()
        self.name = (
            name if isinstance(name, Lexer.Token) else TokenType.IDENTIFIER(name)
        )

    def __eq__(self, other):
        return type(other) == NameAccessExpression and self.name == other.name

    def __repr__(self):
        return f"VARIABLE({self.name})"

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        context.add_code(self.scope.get_remapped_name(self.name.text))

    def emit_c_code_for_write(
        self,
        base: CCodeEmitter,
        context: CCodeEmitter.CExpressionBuilder,
        value_source: AbstractASTNodeExpression,
    ):
        context.add_code(self.scope.get_remapped_name(self.name.text))
        context.add_code(" = ")
        value_source.emit_c_code(base, context)


class GeneratorNameAccessExpression(NameAccessExpression):
    def __init__(self, name: Lexer.Token, index: int):
        super().__init__(name)
        self.index = index

    def __eq__(self, other):
        return (
            type(other) == GeneratorNameAccessExpression
            and self.name == other.name
            and self.index == other.index
        )

    def __repr__(self):
        return f"GENERATOR-VARIABLE({self.name})"

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        context.add_code(f"generator->locals[{self.index}]")

    def emit_c_code_for_write(
        self,
        base: CCodeEmitter,
        context: CCodeEmitter.CExpressionBuilder,
        value_source: AbstractASTNodeExpression,
    ):
        context.add_code(f"generator->locals[{self.index}] = ")
        value_source.emit_c_code(base, context)


class GlobalCNameAccessExpression(AbstractASTNodeExpression):
    def __init__(self, name: str, declare=True):
        super().__init__()
        self.name = self.normal_name = name
        self.declare = declare
        self.data_type: AbstractDataType | None = None

    def copy(self):
        obj = type(self)(self.name)
        obj.normal_name = self.normal_name
        return obj

    def __eq__(self, other):
        return type(other) == GlobalCNameAccessExpression and self.name == other.name

    def __repr__(self):
        return f"GLOBAL-C-VARIABLE({self.name})"

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        if self.name.isidentifier() and self.declare:
            base.add_global_variable("PyObjectContainer*", self.name)

        context.add_code(self.name)

    def emit_c_code_for_write(
        self,
        base: CCodeEmitter,
        context: CCodeEmitter.CExpressionBuilder,
        value_source: AbstractASTNodeExpression,
    ):
        context.add_code(f"{self.name} = ")
        value_source.emit_c_code(base, context)


class ConstantAccessExpression(AbstractASTNodeExpression):
    def __init__(self, value: typing.Any, token=None):
        super().__init__()
        self.value = value
        self.token = token

        if isinstance(value, int):
            self.static_value_type = INTEGER_DATA_TYPE
        elif isinstance(value, float):
            self.static_value_type = FLOAT_DATA_TYPE
        elif isinstance(value, str):
            self.static_value_type = ClassExactDataType(
                Scope.STANDARD_LIBRARY_VALUES["<str>"]["*"]
            )

    def __eq__(self, other):
        return type(other) == ConstantAccessExpression and self.value == other.value

    def __repr__(self):
        return f"CONSTANT({repr(self.value)})"

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        if isinstance(self.value, int):
            context.add_code(f"PY_createInteger({self.value})")

        elif self.value is None:
            context.add_code("PY_NONE")

        elif self.value is False:
            context.add_code("PY_FALSE")

        elif self.value is True:
            context.add_code("PY_TRUE")

        elif isinstance(self.value, str):
            norm = self.value.replace('"', '\\"')
            context.add_code(f'PY_createString("{norm}")')

        elif isinstance(self.value, GlobalCNameAccessExpression):
            context.add_code(self.value.name)

        elif isinstance(self.value, ModuleReference):
            context.add_code(
                f"PY_MODULE_INSTANCE_{self.value.name.replace('.', '___')}"
            )

        elif isinstance(self.value, FunctionDefinitionNode):
            context.add_code(self.value.global_container_name)

        else:
            print(self.parent)
            raise NotImplementedError(self.value)


class PriorityBrackets(AbstractASTNode):
    def __init__(self, inner_node: AbstractASTNode):
        super().__init__()
        self.inner_node = inner_node

    def __eq__(self, other):
        return type(other) == PriorityBrackets and self.inner_node == other.inner_node

    def __repr__(self):
        return f"BRACKET({self.inner_node})"

    def try_replace_child(
        self,
        original: AbstractASTNode | None,
        replacement: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        replacement.parent = self, position
        self.inner_node = replacement
        return True

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        self.inner_node.emit_c_code(base, context)

    def emit_c_code_for_write(
        self,
        base: CCodeEmitter,
        context: CCodeEmitter.CExpressionBuilder,
        value_source: AbstractASTNodeExpression,
    ):
        self.inner_node.emit_c_code_for_write(base, context, value_source)


class TupleConstructor(AbstractASTNodeExpression):
    def __init__(self, items: typing.List[AbstractASTNode]):
        super().__init__()
        self.items = items
        self.static_value_type = ClassExactDataType(
            Scope.STANDARD_LIBRARY_VALUES["tuple"]["*"]
        )

    def __eq__(self, other):
        return type(other) == TupleConstructor and self.items == other.items

    def __repr__(self):
        return f"TUPLE({repr(self.items)[1:-1]})"

    def try_replace_child(
        self,
        original: AbstractASTNode | None,
        replacement: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        replacement.parent = self, position
        self.items[self.items.index(original)] = replacement
        return True

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        if self.items:
            context.add_code(f"PY_STD_tuple_CREATE({len(self.items)}, ")

            for item in self.items[:-1]:
                item.emit_c_code(base, context)
                context.add_code(", ")

            self.items[-1].emit_c_code(base, context)

            context.add_code(")")
        else:
            context.add_code("PY_STD_tuple_CREATE(0)")

    def emit_c_code_for_write(
        self,
        base: CCodeEmitter,
        context: CCodeEmitter.CExpressionBuilder,
        value_source: AbstractASTNodeExpression,
    ):
        temporary = base.get_fresh_name("temporary_tuple")
        context.add_code(f"PyObjectContainer* {temporary} = ")
        value_source.emit_c_code(base, context)
        context.add_code(";\n")
        context.add_code(
            f"assert(PY_unpackInteger(PY_STD_operator_len({temporary})) == {len(self.items)});\n"
        )

        for i, item in enumerate(self.items):
            item.emit_c_code_for_write(
                base,
                context,
                GlobalCNameAccessExpression(
                    f"PY_GetSubscriptionValue({temporary}, PY_createInteger({i}))"
                ),
            )
            context.add_code(";\n")


class GeneratorExpression(AbstractASTNodeExpression):
    def __init__(
        self,
        base_expression: AbstractASTNodeExpression,
        target_expression: AssignmentExpression,
        iterable: AbstractASTNodeExpression,
        if_node: AbstractASTNodeExpression = None,
    ):
        super().__init__()
        self.base_expression = base_expression
        self.target_expression = target_expression
        self.iterable = iterable
        self.if_node = if_node

    def __repr__(self):
        return f"GENERATOR({self.base_expression} for {self.target_expression} in {self.iterable}{'' if self.if_node is None else f' if {repr(self.if_node)}'})"

    def __eq__(self, other):
        return (
            type(other) == GeneratorExpression
            and self.base_expression == other.base_expression
            and self.target_expression == other.target_expression
            and self.iterable == other.iterable
            and self.if_node == other.if_node
        )

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        """
        <result> = PY_STD_GENERATOR_CREATE_FILLED(<target>, <count>, <iterator-instance>, <local vars>)

        PyObjectContainer* <target>(GENERATOR gen)
        {
            value = next(iterator)
            while (!<if_node or TRUE>)
            {
                value = next(iterator, NULL)
                if (value == NULL)
                {
                    return NULL;
                }
            }
            return value;
        }
        """
        target_name = base.get_fresh_name("generator_target")

        inner_func = base.CFunctionBuilder(
            target_name,
            ["PyGeneratorContainer* generator"],
            "PyObjectContainer*",
            base.scope,
        )

        # todo: decide which locals to capture & rewrite them here!
        locals = []

        raise NotImplementedError("code emitted for generator expressions")


class ListConstructor(AbstractASTNodeExpression):
    def __init__(self, items: typing.List[AbstractASTNode]):
        super().__init__()
        self.items = items
        self.static_value_type = ClassExactDataType(
            Scope.STANDARD_LIBRARY_VALUES["list"]["*"]
        )

    def __eq__(self, other):
        return type(other) == ListConstructor and self.items == other.items

    def __repr__(self):
        return f"LIST({repr(self.items)[1:-1]})"

    def try_replace_child(
        self,
        original: AbstractASTNode | None,
        replacement: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        replacement.parent = self, position
        self.items[self.items.index(original)] = replacement
        return True

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        if self.items:
            context.add_code(f"PY_STD_list_CREATE({len(self.items)}, ")

            for item in self.items[:-1]:
                item.emit_c_code(base, context)
                context.add_code(", ")

            self.items[-1].emit_c_code(base, context)

            context.add_code(")")
        else:
            context.add_code("PY_STD_list_CREATE(0)")

    def emit_c_code_for_write(
        self,
        base: CCodeEmitter,
        context: CCodeEmitter.CExpressionBuilder,
        value_source: AbstractASTNodeExpression,
    ):
        raise RuntimeError("not implemented")


class ListComprehension(AbstractASTNodeExpression):
    def __init__(
        self,
        base_expression: AbstractASTNodeExpression,
        target_expression: AssignmentExpression,
        iterable: AbstractASTNodeExpression,
        if_node: AbstractASTNodeExpression = None,
    ):
        super().__init__()
        self.base_expression = base_expression
        self.target_expression = target_expression
        self.iterable = iterable
        self.if_node = if_node
        self.len_hint: AbstractASTNode | None = None
        self.iter_hint: AbstractASTNode | None = None
        self.variant: str | None = None

    def __repr__(self):
        return f"LIST-COMPREHENSION({self.base_expression} for {self.target_expression} in {self.iterable}{'' if self.if_node is None else f' if {repr(self.if_node)}'})"

    def __eq__(self, other):
        return (
            type(other) == ListComprehension
            and self.base_expression == other.base_expression
            and self.target_expression == other.target_expression
            and self.iterable == other.iterable
            and self.if_node == other.if_node
        )

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        from pycompiler.TypeResolver import GetCapturedNames

        declare_locals = list(
            sorted(list(self.base_expression.scope.variable_name_stack))
        )

        transfer_name = base.get_fresh_name("comprehension_transfer")
        base.add_global_variable(
            "PyObjectContainer*",
            f"{transfer_name}(PyObjectContainer* value , PyObjectContainer** locals)",
            ignore_error=True,
        )
        transfer_func = base.CFunctionBuilder(
            transfer_name,
            ["PyObjectContainer* value", "PyObjectContainer** locals"],
            "PyObjectContainer*",
            base.scope,
        )
        base.add_function(transfer_func)

        for local in declare_locals:
            transfer_func.add_code(
                f"PyObjectContainer* {self.base_expression.scope.get_remapped_name(local)};\n"
            )

        local_capture = "NULL"
        capturing = GetCapturedNames()
        capturing.visit_any(self.base_expression)
        capturing.visit_any(self.if_node)

        if capturing.names:
            local_capture = "(PyObjectContainer*[]) { "

            # todo: this is not enough, we need to do some resoling ahead of time
            #  to make sure our scope known about it!
            for name in capturing.names[:-1]:
                local_capture += f"{self.scope.get_remapped_name(name)}, "

            local_capture += f"{self.scope.get_remapped_name(capturing.names[-1])} }}"

        self.target_expression.emit_c_code_for_write(
            base, transfer_func, GlobalCNameAccessExpression("value")
        )
        transfer_func.add_code(";\nreturn ")
        self.base_expression.emit_c_code(base, transfer_func)
        transfer_func.add_code(";")

        condition_name = "NULL"
        if self.if_node:
            condition_name = base.get_fresh_name("comprehension_condition")
            base.add_global_variable(
                "PyObjectContainer*",
                f"{condition_name}(PyObjectContainer* value , PyObjectContainer** locals)",
                ignore_error=True,
            )
            condition_func = base.CFunctionBuilder(
                condition_name,
                ["PyObjectContainer* value", "PyObjectContainer** locals"],
                "PyObjectContainer*",
                base.scope,
            )
            base.add_function(condition_func)

            for local in declare_locals:
                condition_func.add_code(
                    f"PyObjectContainer* {self.base_expression.scope.get_remapped_name(local)};\n"
                )

            condition_func.add_code("return ")
            self.if_node.emit_c_code(base, condition_func)
            condition_func.add_code(";")

        if self.variant:
            context.add_code(self.variant + "(")
        else:
            context.add_code("PY_STD_list_CONSTRUCT_COMPREHENSION")

            if self.len_hint is not None:
                context.add_code("_with_len_hint")

            if self.iter_hint is not None:
                context.add_code("_with_iter_hint")

            context.add_code("(")

        self.iterable.emit_c_code(base, context)
        context.add_code(f", {transfer_name}, {condition_name}, {local_capture}")

        if self.variant is None:
            if self.len_hint is not None:
                context.add_code(", ")
                self.len_hint.emit_c_code(base, context)

            if self.iter_hint is not None:
                context.add_code(", ")
                self.iter_hint.emit_c_code(base, context)

        context.add_code(")")


class DictConstructor(AbstractASTNodeExpression):
    def __init__(
        self,
        key_value_pairs: typing.List[typing.Tuple[AbstractASTNode, AbstractASTNode]],
    ):
        super().__init__()
        self.key_value_pairs = key_value_pairs
        self.static_value_type = ClassExactDataType(
            Scope.STANDARD_LIBRARY_VALUES["dict"]["*"]
        )

    def __eq__(self, other):
        return (
            type(other) == DictConstructor
            and self.key_value_pairs == other.key_value_pairs
        )

    def __repr__(self):
        return f"DICT({repr(self.key_value_pairs)[1:-1]})"

    def try_replace_child(
        self,
        original: AbstractASTNode | None,
        replacement: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        replacement.parent = self, position

        for i, (key, value) in enumerate(self.key_value_pairs):
            if key is original:
                self.key_value_pairs[i] = replacement, value
                break
            elif value is original:
                self.key_value_pairs[i] = key, replacement
                break
        else:
            return False

        return True

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        if self.key_value_pairs:
            context.add_code(f"PY_STD_dict_CREATE({len(self.key_value_pairs)}, ")

            for key, value in self.key_value_pairs[:-1]:
                key.emit_c_code(base, context)
                context.add_code(", ")
                value.emit_c_code(base, context)
                context.add_code(", ")

            key, value = self.key_value_pairs[-1]
            key.emit_c_code(base, context)
            context.add_code(", ")
            value.emit_c_code(base, context)

            context.add_code(")")
        else:
            context.add_code("PY_STD_dict_CREATE(0)")

    def emit_c_code_for_write(
        self,
        base: CCodeEmitter,
        context: CCodeEmitter.CExpressionBuilder,
        value_source: AbstractASTNodeExpression,
    ):
        raise RuntimeError("not implemented")


class AttributeExpression(AbstractASTNodeExpression):
    def __init__(self, base: AbstractASTNode, dot: Lexer.Token, attribute: Lexer.Token):
        super().__init__()
        self.base = base
        self.dot = dot
        self.attribute = attribute

    def __eq__(self, other):
        return (
            type(other) == AttributeExpression
            and self.base == other.base
            and self.dot == other.dot
            and self.attribute == other.attribute
        )

    def __repr__(self):
        return f"ATTRIBUTE({self.base}|{self.dot}|{self.attribute})"

    def try_replace_child(
        self,
        original: AbstractASTNode | None,
        replacement: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        replacement.parent = self, position
        if position != ParentAttributeSection.LHS:
            return False

        self.base = replacement
        return True

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        context.add_code("PY_getObjectAttributeByNameOrStatic(")

        self.base.emit_c_code(base, context)
        context.add_code(f', "{self.attribute.text}")')

    def emit_c_code_for_write(
        self,
        base: CCodeEmitter,
        context: CCodeEmitter.CExpressionBuilder,
        value_source: AbstractASTNodeExpression,
    ):
        temporary = base.get_fresh_name("temp")
        context.add_code(f"PyObjectContainer* {temporary} = ")
        value_source.emit_c_code(base, context)
        context.add_code(f";\nPY_setObjectAttributeByName(")
        self.base.emit_c_code(base, context)
        context.add_code(f', {temporary}, "{self.attribute.text}")')


class SubscriptionExpression(AbstractASTNodeExpression):
    def __init__(
        self,
        base: AbstractASTNode,
        lhs_bracket: Lexer.Token,
        expression: AbstractASTNode,
        rhs_bracket: Lexer.Token,
    ):
        super().__init__()
        self.base = base
        self.lhs_bracket = lhs_bracket
        self.expression = expression
        self.rhs_bracket = rhs_bracket

    def __eq__(self, other):
        return (
            type(other) == SubscriptionExpression
            and self.base == other.base
            and self.lhs_bracket == other.lhs_bracket
            and self.expression == other.expression
            and self.rhs_bracket == other.rhs_bracket
        )

    def __repr__(self):
        return f"SUBSCRIPTION({self.base}|{self.lhs_bracket}|{self.expression}|{self.rhs_bracket})"

    def try_replace_child(
        self,
        original: AbstractASTNode | None,
        replacement: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        replacement.parent = self, position
        if position == ParentAttributeSection.LHS:
            self.base = replacement
        elif position == ParentAttributeSection.RHS:
            self.expression = replacement
        else:
            return False

        return True

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        context.add_code("PY_GetSubscriptionValue(")
        self.base.emit_c_code(base, context)
        context.add_code(", ")
        self.expression.emit_c_code(base, context)
        context.add_code(")")

    def emit_c_code_for_write(
        self,
        base: CCodeEmitter,
        context: CCodeEmitter.CExpressionBuilder,
        value_source: AbstractASTNodeExpression,
    ):
        temporary = base.get_fresh_name("temp")
        context.add_code(f"PyObjectContainer* {temporary} = ")
        value_source.emit_c_code(base, context)
        context.add_code(f";\nPY_SetSubscriptionValue(")
        self.base.emit_c_code(base, context)
        context.add_code(f", {temporary}, ")
        self.expression.emit_c_code(base, context)
        context.add_code(")")


class CallExpression(AbstractASTNodeExpression):
    class ParameterType(enum.Enum):
        NORMAL = "CALL_STRUCTURE_NORMAL"
        KEYWORD = "CALL_STRUCTURE_KEYWORD"
        STAR = "CALL_STRUCTURE_STAR"
        STAR_STAR = "CALL_STRUCTURE_STAR_STAR"

        def __init__(self, c_name: str):
            self.c_name = c_name

    class CallExpressionArgument(AbstractASTNode):
        def __init__(
            self,
            value: AbstractASTNode,
            mode: CallExpression.ParameterType,
            key: Lexer.Token = None,
        ):
            super().__init__()

            assert (mode == CallExpression.ParameterType.KEYWORD) == (key is not None)

            self.value = value
            self.mode = mode
            self.key = key

        def __eq__(self, other):
            return (
                type(other) == CallExpression.CallExpressionArgument
                and self.value == other.value
                and self.mode == other.mode
                and self.key == other.key
            )

        def __repr__(self):
            return f"ARG({self.value}|{self.mode}|{self.key})"

        def try_replace_child(
            self,
            original: AbstractASTNode | None,
            replacement: AbstractASTNode,
            position: ParentAttributeSection,
        ) -> bool:
            replacement.parent = self, position
            if position == ParentAttributeSection.PARAMETER:
                self.value = replacement
                return True
            return False

        def emit_c_code(
            self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder
        ):
            self.value.emit_c_code(base, context)

    def __init__(
        self,
        base: AbstractASTNode,
        generics: typing.List[AbstractASTNode],
        l_bracket: Lexer.Token,
        args: typing.List[CallExpression.CallExpressionArgument],
        r_bracket: Lexer.Token,
    ):
        super().__init__()
        self.base = base
        self.generics = generics
        self.l_bracket = l_bracket
        self.args = args
        self.r_bracket = r_bracket

        for arg in args:
            arg.set_parent(self, ParentAttributeSection.PARAMETER)

    def __eq__(self, other):
        return (
            type(other) == CallExpression
            and self.base == other.base
            and self.generics == other.generics
            and self.l_bracket == other.l_bracket
            and self.args == other.args
            and self.r_bracket == other.r_bracket
        )

    def __repr__(self):
        return f"CALL({self.base}|{self.generics}|{self.l_bracket}|{self.args}|{self.r_bracket})"

    def try_replace_child(
        self,
        original: AbstractASTNode | None,
        replacement: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        replacement.parent = self, position
        if position == ParentAttributeSection.LHS:
            self.base = replacement
        elif position == ParentAttributeSection.PARAMETER:
            self.args.replace(original, replacement)
        else:
            return False
        return True

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        if isinstance(
            self.base, (GlobalCNameAccessExpression, StandardLibraryBoundOperator)
        ):
            obj = self.base
        elif not isinstance(self.base, ConstantAccessExpression):
            self.emit_c_code_any_call(base, context)
            return
        else:
            obj = typing.cast(ConstantAccessExpression, self.base).value

        if isinstance(obj, FunctionDefinitionNode):
            func_name = obj.normal_name
        elif isinstance(obj, ClassDefinitionNode):
            self.emit_c_code_constructor(base, context)
            return
        elif isinstance(obj, StandardLibraryBoundOperator):
            func_name = obj.exposed_operator
        elif isinstance(obj, GlobalCNameAccessExpression):
            func_name = obj.name

        else:
            raise NotImplementedError(obj)

        context.add_code(f"PY_CHECK_EXCEPTION({func_name} (")

        for arg in self.args[:-1]:
            arg.emit_c_code(base, context)
            context.add_code(" , ")

        if self.args:
            self.args[-1].emit_c_code(base, context)

        context.add_code("))")

    def emit_c_code_constructor(
        self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder
    ):
        is_special = False
        for arg in self.args:
            if arg.mode != CallExpression.ParameterType.NORMAL:
                is_special = True
                break

        call_info = "NULL"
        if is_special:
            call_info = self.emit_c_code_any_special(base, context)

        temporary = base.get_fresh_name("obj_instance")
        constructor = base.get_fresh_name("constructor")
        cls: ClassDefinitionNode = typing.cast(
            ClassDefinitionNode, typing.cast(ConstantAccessExpression, self.base).value
        )

        is_direct_ref = False
        func_decl = None

        if "__init__" in cls.function_table and not is_special:
            func_decl = cls.function_table["__init__"].normal_name
            is_direct_ref = True
        elif ("__init__", len(self.args)) in cls.function_table and not is_special:
            func_decl = cls.function_table["__init__", len(self.args)].normal_name
            is_direct_ref = True
        else:
            args = ""
            if len(self.args) == 1:
                temp = base.get_fresh_name("temp_arg")
                context.parent.add_code(f"PyObjectContainer* {temp} = ")
                self.args[0].emit_c_code(base, context.parent)
                context.parent.add_code(f";\nPyObjectContainer** {args} = &{temp};")

            elif self.args:
                args = base.get_fresh_name("args")

                context.parent.add_code(f"PyObjectContainer* {args}[{len(self.args)}];")
                for i, arg in enumerate(self.args):
                    context.parent.add_code(f"{args}[{i}] = ")
                    arg.emit_c_code(base, context.parent)
                    context.parent.add_code(";\n")

            # todo: set exception type for attribute error
            # todo: allow keyword args and similar by treating this like a normal function call
            context.parent.add_code(
                f"""
PyObjectContainer* {temporary} = PY_createClassInstance({'' if isinstance(cls, StandardLibraryClass) else 'PY_CLASS_'}{cls.normal_name});
PyObjectContainer* {constructor} = PY_getObjectAttributeByNameOrStatic({temporary}, "__init__");

PY_THROW_EXCEPTION_IF({constructor} == NULL, NULL);
PY_CHECK_EXCEPTION(PY_invokeBoxedMethod({constructor}, NULL, {len(self.args)}, {args if self.args else 'NULL'}, {call_info}));
DECREF({constructor});
"""
            )

        if is_direct_ref:
            context.parent.add_code(
                f"PyObjectContainer* {temporary} = PY_createClassInstance({'' if isinstance(cls, StandardLibraryClass) else 'PY_CLASS_'}{cls.normal_name});\n"
            )
            context.parent.add_code(f"PY_CHECK_EXCEPTION({func_decl}({temporary}")

            if self.args:
                for arg in self.args:
                    context.parent.add_code(" , ")
                    arg.emit_c_code(base, context.parent)

            context.parent.add_code("));\n\n")

        context.add_code(temporary)

    def emit_c_code_any_call(
        self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder
    ):
        is_special = False
        for arg in self.args:
            if arg.mode != CallExpression.ParameterType.NORMAL:
                is_special = True
                break

        call_info = "NULL"
        if is_special:
            call_info = self.emit_c_code_any_special(base, context)

        if len(self.args) == 1:
            temporary = base.get_fresh_name("temporary")

            with context.parent.get_statement_builder(indent=context.indent) as intro:
                intro.add_code(f"PyObjectContainer* {temporary} = ")
                self.args[0].emit_c_code(base, intro)
                intro.add_code(";\n")

            context.add_code("PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(")
            self.base.emit_c_code(base, context)
            context.add_code(f", NULL, {len(self.args)}, &{temporary}, {call_info}))")

        elif self.args:
            temporary = base.get_fresh_name("temporary")

            context.add_code("PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(")
            self.base.emit_c_code(base, context)
            context.add_code(f", NULL, {len(self.args)}, (PyObjectContainer*[]) {{")
            for arg in self.args[:-1]:
                arg.emit_c_code(base, context)
                context.add_code(", ")
            self.args[-1].emit_c_code(base, context)
            context.add_code(f"}}, {call_info}))")
        else:
            context.add_code("PY_CHECK_EXCEPTION(PY_invokeBoxedMethod(")
            self.base.emit_c_code(base, context)
            context.add_code(", NULL, 0, NULL, NULL))")

    def emit_c_code_any_special(
        self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder
    ):
        offset = 0
        entries = []
        keys = []

        for arg in self.args:
            if arg.mode == CallExpression.ParameterType.NORMAL and not entries:
                offset += 1
            else:
                entries.append(arg.mode.c_name)
                keys.append(
                    arg.key.text
                    if arg.mode == CallExpression.ParameterType.KEYWORD
                    else None
                )

        merged_entries = [
            entries[32 * i : min(32 * (i + 1), len(entries))]
            for i in range(math.ceil(len(entries) / 32))
        ]
        merged_entries += ["0"] * (8 - len(entries))

        keyword_data = "NULL"

        if any(keys):
            keyword_var = base.get_fresh_name("keyword_name_var")
            base.add_global_variable("PyObjectContainer**", keyword_var)
            inner = ", ".join(f'PY_createString("{e}")' if e else "NULL" for e in keys)
            base.init_function.add_code(
                f"{keyword_var} = (PyObjectContainer*[]) {{{inner}}};\n"
            )
            keyword_data = keyword_var

        return f"PY_ARGS_createCallInfo({offset}, {len(entries)}, (uint64_t[]) {{{', '.join(' | '.join(e) for e in merged_entries)}}}, {keyword_data})"


class ReturnStatement(AbstractASTNode):
    def __init__(self, return_value: AbstractASTNode):
        super().__init__()
        self.return_value = return_value

    def __eq__(self, other):
        return (
            type(other) == ReturnStatement and self.return_value == other.return_value
        )

    def __repr__(self):
        return f"RETURN({self.return_value})"

    def try_replace_child(
        self,
        original: AbstractASTNode | None,
        replacement: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        replacement.parent = self, position
        if position == ParentAttributeSection.RHS:
            self.return_value = replacement
            return True
        return False

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        context.add_code("return ")
        self.return_value.emit_c_code(base, context)
        context.add_code(";")


class GeneratorExitReturnStatement(ReturnStatement):
    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        context.add_code("generator->next_section = NULL;\n")
        super().emit_c_code(base, context)


class YieldStatement(AbstractASTNode):
    def __init__(self, yield_expression: AbstractASTNode, is_yield_from=False):
        super().__init__()
        self.yield_expression = yield_expression
        self.yield_label_id: int = -1
        self.is_yield_from = is_yield_from
        self.is_rebuild = False

    def __eq__(self, other):
        return (
            type(other) == ReturnStatement
            and self.yield_expression == other.yield_expression
        )

    def __repr__(self):
        return f"YIELD({self.yield_expression}|{self.is_yield_from})"

    def try_replace_child(
        self,
        original: AbstractASTNode | None,
        replacement: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        replacement.parent = self, position
        if position == ParentAttributeSection.RHS:
            self.yield_expression = replacement
            return True

        return False

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        if not self.is_yield_from:
            context.add_code(f"generator->section_id = {self.yield_label_id};\nreturn ")
            self.yield_expression.emit_c_code(base, context)
            context.add_code(f";\ngen_{self.yield_label_id}:;\n")
        else:
            iterator = base.get_fresh_name("curr_value")
            context.add_code(f"generator->yield_from_source = PY_STD_operator_iter(")
            self.yield_expression.emit_c_code(base, context)
            context.add_code(");\n")
            context.add_code(
                f"""generator->section_id = {self.yield_label_id};
gen_{self.yield_label_id}:;
PyObjectContainer* {iterator} = PY_STD_operator_next(generator->yield_from_source);

if ({iterator} == NULL)
{{
    generator->section_id = {self.yield_label_id+1};
    goto gen_{self.yield_label_id+1};
}}
return {iterator};
gen_{self.yield_label_id+1}:;\n
"""
            )


class FunctionDefinitionNode(AbstractASTNode):
    class ParameterType(enum.Enum):
        NORMAL = enum.auto()
        KEYWORD = enum.auto()
        STAR = enum.auto()
        STAR_STAR = enum.auto()

    class FunctionDefinitionParameter(AbstractASTNode):
        def __init__(
            self,
            name: Lexer.Token,
            mode: FunctionDefinitionNode.ParameterType,
            hint=None,
            default: AbstractASTNode = None,
        ):
            super().__init__()

            assert (default is not None) == (
                mode == FunctionDefinitionNode.ParameterType.KEYWORD
            )

            self.name = name
            self.normal_name = name.text
            self.mode = mode
            self.hint = hint
            self.default = default

        def __eq__(self, other):
            return (
                type(other) == FunctionDefinitionNode.FunctionDefinitionParameter
                and self.name == other.name
                and self.mode == other.mode
                and self.hint == other.hint
                and self.default == other.default
            )

        def __repr__(self):
            return f"PARAMETER({self.name}|{self.mode}|{self.hint}|{self.default})"

        def try_replace_child(
            self,
            original: AbstractASTNode | None,
            replacement: AbstractASTNode,
            position: ParentAttributeSection,
        ) -> bool:
            replacement.parent = self, position
            if (
                self.mode == FunctionDefinitionNode.ParameterType.KEYWORD
                and position == ParentAttributeSection.PARAMETER
            ):
                self.default = replacement
                return True
            return False

    def __init__(
        self,
        name: Lexer.Token,
        generics: typing.List[Lexer.Token],
        parameters: typing.List[FunctionDefinitionNode.FunctionDefinitionParameter],
        body: typing.List[AbstractASTNode],
        is_generator=False,
    ):
        super().__init__()
        self.name = name
        self.generics = generics
        self.parameters = parameters
        self.body = body
        self.normal_name = name.text
        self.is_generator = is_generator
        self.return_type: AbstractDataType = None
        self.global_container_name = None

        if self.is_generator:
            # is guaranteed to return a generator object
            self.static_value_type = ClassExactDataType(
                Scope.STANDARD_LIBRARY_VALUES["<generator>"]["*"]
            )

    def __eq__(self, other):
        return (
            type(other) == FunctionDefinitionNode
            and self.name == other.name
            and self.generics == other.generics
            and self.parameters == other.parameters
            and self.body == other.body
            and self.is_generator == other.is_generator
        )

    def __repr__(self):
        return f"FUNCTION({self.name}|{self.generics}|{self.parameters}|{self.is_generator}|{self.body})"

    def try_replace_child(
        self,
        original: AbstractASTNode | None,
        replacement: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        replacement.parent = self, position
        for i, node in enumerate(self.body):
            if node is original:
                self.body[i] = replacement
                return True

        return False

    def try_insert_before(
        self,
        original: AbstractASTNode | None,
        insert: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        insert.parent = self, position
        for i, node in enumerate(self.body[:]):
            if node is original:
                self.body.insert(i, insert)
                return True

        return False

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        if self.is_generator:
            return self.emit_c_code_for_generator(base, context)

        func_name = self.normal_name

        func = base.CFunctionBuilder(
            func_name,
            [f"PyObjectContainer* {param.normal_name}" for param in self.parameters],
            "PyObjectContainer*",
            base.scope,
        )
        base.add_function(func)

        func.add_code(
            f"// Source Location: {'.'.join(self.scope.class_name_stack)}.{self.name.text}\n"
        )

        if len(self.body) > 0:
            args = [arg.name.text for arg in self.parameters]

            for var in list(sorted(list(self.body[0].scope.variable_name_stack))):
                if var not in args:
                    norm_name = self.body[0].scope.get_normalised_name(var)
                    self.body[0].scope.add_remapped_name(var, norm_name)
                    func.add_code(f"PyObjectContainer* {norm_name};\n")

        for line in self.body:
            inner_section = func.get_statement_builder(indent=False)

            line.emit_c_code(base, inner_section)

            if isinstance(line, AbstractASTNodeExpression):
                inner_section.add_code(";\n")
            else:
                inner_section.add_code("\n")

            func.add_code(inner_section.get_result() + "\n")

        if not func.snippets[-1].startswith("return"):
            func.add_code("return PY_NONE;")

        self.generate_safe_wrapper(base, func_name)

        base.init_function.add_code("#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE\n")
        assert self.global_container_name is not None
        base.init_function.add_code(
            f'PY_setObjectAttributeByName(PY_MODULE_INSTANCE_{base.module_name.replace(".", "__")}, "{self.name.text}", ({self.global_container_name} = PY_createBoxForFunction({self.normal_name}_safeWrap)));\n'
        )
        base.init_function.add_code("#endif\n")

    def emit_c_code_for_generator(
        self,
        base: CCodeEmitter,
        context: CCodeEmitter.CExpressionBuilder,
        is_target=False,
    ):
        from pycompiler.GeneratorHelper import (
            GetValidYieldStatements,
            RewriteReturnToGeneratorExit,
            LocalNameAccessRewriter,
        )

        func_name = self.normal_name

        func = base.CFunctionBuilder(
            func_name,
            [f"PyObjectContainer* {param.normal_name}" for param in self.parameters],
            "PyObjectContainer*",
            base.scope,
        )
        base.add_function(func)

        local_count = len(self.parameters)

        if self.body:
            # todo: what is about internal-but-same-frame locals?
            local_count += len(self.body[0].scope.variable_name_stack)

        base.add_include('"standard_library/generator.h"')

        func.add_code(
            f"""PyObjectContainer* generator = PY_STD_GENERATOR_create({local_count});
PyGeneratorContainer* container = generator->raw_value;
container->next_section = {func_name}_ENTRY;
"""
        )

        for i, param in enumerate(self.parameters):
            func.add_code(f"container->locals[{i}] = {param.normal_name};\n")

        func.add_code("return generator;")

        inner_func = base.CFunctionBuilder(
            func_name + "_ENTRY",
            ["PyGeneratorContainer* generator"],
            "PyObjectContainer*",
            base.scope,
        )
        base.add_function(inner_func)

        inner_func.add_code("switch (generator->section_id){\n")
        inner_func.add_code("    case 0: goto gen_0;\n")

        yield_finder = GetValidYieldStatements()
        yield_finder.visit_any_list(self.body)

        i = 0
        for statement in yield_finder.statements:
            inner_func.add_code(f"    case {i+1}: goto gen_{i+1};\n")
            statement.yield_label_id = i + 1

            if statement.is_yield_from:
                i += 2
                inner_func.add_code(f"    case {i}: goto gen_{i};\n")
            else:
                i += 1

        inner_func.add_code("};\n\ngen_0:;\n")

        RewriteReturnToGeneratorExit().visit_any_list(self.body)
        LocalNameAccessRewriter().visit_any_list(self.body)

        for line in self.body:
            inner_section = inner_func.get_statement_builder(indent=False)

            line.emit_c_code(base, inner_section)

            if isinstance(line, AbstractASTNodeExpression):
                inner_section.add_code(";\n")
            else:
                inner_section.add_code("\n")

            inner_func.add_code(inner_section.get_result() + "\n")

        if not inner_func.snippets[-1].startswith("return"):
            inner_func.add_code("return NULL;")

        self.generate_safe_wrapper(base, func_name)

    def generate_safe_wrapper(self, base, func_name):
        # todo: when bound object method, forward 'self' as first argument!
        base.add_include("<assert.h>")
        safe_name = f"{func_name}_safeWrap"
        safe_func = base.CFunctionBuilder(
            safe_name,
            [
                "PyObjectContainer* self",
                "uint8_t argc",
                "PyObjectContainer** args",
                "CallStructureInfo* info",
            ],
            "PyObjectContainer*",
            base.scope,
        )
        base.add_function(safe_func)

        # todo: there are other arg types!

        arg_unbox = [f"new_args[{i}]" for i, param in enumerate(self.parameters)]
        arg_unbox_2 = [f"new_args[{i}]" for i, param in enumerate(self.parameters[1:])]

        unbox = " , ".join(arg_unbox)
        unbox_2 = " , ".join(arg_unbox_2)

        if len(self.parameters) > 0:
            has_keyword = False
            for param in self.parameters:
                if param.mode != FunctionDefinitionNode.ParameterType.NORMAL:
                    has_keyword = True
                    break

            if has_keyword:
                self.emit_safe_wrap_with_keywords(
                    base, func_name, safe_func, unbox, unbox_2
                )
            else:
                safe_func.add_code(
                    f"""
PyObjectContainer** new_args = PY_ARGS_unpackPositionalArgs(args, info, &argc);
PyObjectContainer* result;

if (self == NULL) {{
    assert(argc == {len(self.parameters)});
    result = {func_name}({unbox});
}}
else {{
    assert(argc == {len(self.parameters) - 1});
    result = {func_name}(self{f' , {unbox_2}' if unbox_2 else ''});
}}

if (info) free(new_args);
return result;

"""
                )
        else:
            safe_func.add_code(
                f"""
assert(self == NULL);
assert(argc == {len(self.parameters)});
return {func_name}({unbox});
"""
            )

    def emit_safe_wrap_with_keywords(self, base, func_name, safe_func, unbox, unbox_2):
        positional_count = 0
        keyword_keys = []
        keyword_default_names = []

        for arg in self.parameters:
            if arg.mode == FunctionDefinitionNode.ParameterType.NORMAL:
                positional_count += 1
            elif arg.mode == FunctionDefinitionNode.ParameterType.KEYWORD:
                keyword_keys.append(arg.name.text)
                default_var = base.get_fresh_name(f"default_keyword_{arg.name.text}")
                keyword_default_names.append(default_var)
                base.add_global_variable("PyObjectContainer*", default_var)
                base.init_function.add_code(f"{default_var} = ")
                arg.default.emit_c_code(base, base.init_function)
                base.init_function.add_code(";\n")
            else:
                raise RuntimeError(f"{arg} not implemented!")

        kwd_keys = '", "'.join(keyword_keys)
        if kwd_keys:
            kwd_keys = f'PY_createString("{kwd_keys}")'

        keyword_mem = base.get_fresh_name("keyword_name_table")

        base.add_global_variable("PyObjectContainer**", keyword_mem)
        base.init_function.add_code(
            f"{keyword_mem} = (PyObjectContainer*[]){{{kwd_keys}}};\n"
        )

        # todo: handle star and star-star args!
        safe_func.add_code(
            f"""
PyObjectContainer** new_args = PY_ARGS_unpackArgTableForUnsafeCall({positional_count}, args, info, &argc, {len(keyword_keys)}, {keyword_mem}, (PyObjectContainer*[]) {{{', '.join(keyword_default_names)}}});
PyObjectContainer* result;

if (self == NULL) {{
    assert(argc == {len(self.parameters)});
    result = {func_name}({unbox});
}}
else {{
    assert(argc == {len(self.parameters) - 1});
    result = {func_name}(self{f' , {unbox_2}' if unbox_2 else ''});
}}

if (info) free(new_args);
return result;

"""
        )


class ClassDefinitionNode(AbstractASTNode):
    def __init__(
        self,
        name: Lexer.Token,
        generics: typing.List[Lexer.Token],
        parents: typing.List[AbstractASTNode],
        body: typing.List[AbstractASTNode],
    ):
        super().__init__()
        self.name = name
        self.generics = generics
        self.parents = parents
        self.body = body
        self.normal_name = name.text
        self.function_table: typing.Dict[
            str | typing.Tuple[str, int], AbstractASTNode
        ] = {}

    def __eq__(self, other):
        return (
            type(other) == ClassDefinitionNode
            and self.name == other.name
            and self.generics == other.generics
            and self.parents == other.parents
            and self.body == other.body
        )

    def __repr__(self):
        return f"CLASS({self.name}|{self.generics}|{self.parents}|{self.body})"

    def try_replace_child(
        self,
        original: AbstractASTNode | None,
        replacement: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        replacement.parent = self, position
        if original is None:
            return False

        if position == ParentAttributeSection.PARAMETER:
            self.parents[self.parents.index(original)] = replacement
            return True
        elif position == ParentAttributeSection.BODY:
            self.body[self.body.index(original)] = replacement
            return True

        return False

    def try_insert_before(
        self,
        original: AbstractASTNode | None,
        insert: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        if position != ParentAttributeSection.BODY:
            return False
        index = self.body.index(original)
        self.body.insert(index, insert)
        return True

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        variable_name = f"PY_CLASS_{self.normal_name}"

        base.add_global_variable("PyClassContainer*", variable_name)

        init_class = CCodeEmitter.CFunctionBuilder(
            f"PY_CLASS_INIT_{variable_name}", [], "PyObjectContainer*", base.scope
        )
        base.add_function(init_class)

        if len(self.body) > 0:
            external = [
                line.name.text
                for line in self.body
                if isinstance(line, (FunctionDefinitionNode, ClassDefinitionNode))
            ]
            for var in list(sorted(list(self.body[0].scope.variable_name_stack))):
                if var not in external:
                    init_class.add_code(
                        f"PyObjectContainer* {self.body[0].scope.get_remapped_name(var)};\n"
                    )

        init_class.add_code(
            f"""
// Create Class {variable_name} ('{self.name.text}' in source code)
{variable_name} = PY_createClassContainer("{self.name.text}");
PY_ClassContainer_AllocateParentArray({variable_name}, {max(len(self.parents), 1)});
"""
        )  # todo: include all the other stuff here!

        init_class.add_code(
            f"\n// Create Parent Objects for class '{self.name.text}'\n"
        )
        if self.parents:
            for i, parent in enumerate(self.parents):
                if isinstance(parent, ClassDefinitionNode):
                    init_class.add_code(
                        f"{variable_name} -> parents[{i}] = PY_CLASS_{parent.normal_name};\n"
                    )
                else:
                    init_class.add_code(
                        f"{variable_name} -> parents[{i}] = PY_unwrapClassContainer(PY_CHECK_EXCEPTION("
                    )
                    parent.emit_c_code(base, init_class)
                    init_class.add_code("));\n")

                    init_subclass = base.get_fresh_name("init_subclass")
                    init_class.add_code(
                        f"""PyObjectContainer* {init_subclass} = PY_getClassAttributeByName({variable_name}->parents[{i}], "__init_subclass__");
if ({init_subclass} != NULL) {{
    PY_CHECK_EXCEPTION(PY_invokeBoxedMethod({init_subclass}, PY_createClassWrapper({variable_name}), 0, NULL, NULL));
}}\n"""
                    )

        else:
            init_class.add_code(f"{variable_name} -> parents[0] = PY_TYPE_OBJECT;\n")

        init_class.add_code("\n// Attributes\n")

        for line in self.body:
            if isinstance(line, FunctionDefinitionNode):
                init_class.add_code(
                    f'PY_setClassAttributeByNameOrCreate({variable_name}, "{line.name.text}", PY_createBoxForFunction({line.normal_name}_safeWrap));\n'
                )

        for line in self.body:
            inner_block = init_class.get_statement_builder(indent=False)

            line.emit_c_code(base, inner_block)

            if isinstance(line, AbstractASTNodeExpression):
                inner_block.add_code(";\n")
            else:
                inner_block.add_code("\n")

            init_class.add_code(inner_block.get_result() + "\n")

        base.add_to_initializer(f"PY_CLASS_INIT_{variable_name}();")


class StandardLibraryClass(ClassDefinitionNode):
    def __init__(self, name: str, exposed_name: str):
        super().__init__(TokenType.IDENTIFIER(name), [], [], [])
        self.normal_name = exposed_name

    def __eq__(self, other):
        return self is other

    def __repr__(self):
        return f"STANDARD_LIBRARY_CLASS({self.name.text})"

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        raise RuntimeError

    def try_replace_child(
        self,
        original: AbstractASTNode | None,
        replacement: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        raise RuntimeError


class StandardLibraryBoundOperator(AbstractASTNode):
    def __init__(self, name: str, exposed_operator: str):
        super().__init__()
        self.name = name
        self.exposed_operator = exposed_operator

    def __eq__(self, other):
        return (
            type(other) == StandardLibraryBoundOperator
            and self.name == other.name
            and self.exposed_operator == other.exposed_operator
        )

    def __repr__(self):
        return f"STANDRAD_LIBRARY_OPERATOR({self.name}, {self.exposed_operator})"

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        context.add_code(self.exposed_operator)


class WhileStatement(AbstractASTNode):
    def __init__(
        self,
        condition: AbstractASTNode,
        body: typing.List[AbstractASTNode],
        else_node: typing.List[AbstractASTNode] = None,
    ):
        super().__init__()
        self.condition = condition
        self.body = body
        self.else_node = else_node or []

    def __eq__(self, other):
        return (
            type(other) == WhileStatement
            and self.condition == other.condition
            and self.body == other.body
            and self.else_node == other.else_node
        )

    def __repr__(self):
        return f"WHILE({self.condition}|{self.body}|{self.else_node})"

    def try_replace_child(
        self,
        original: AbstractASTNode | None,
        replacement: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        replacement.parent = self, position
        if position == ParentAttributeSection.LHS:
            self.condition = replacement
            return True
        elif position == ParentAttributeSection.BODY and original is not None:
            self.body[self.body.index(original)] = replacement
            return True
        elif position == ParentAttributeSection.ELSE_BRANCH:
            self.else_node[self.else_node.index(original)] = replacement
            return True
        return False

    def try_insert_before(
        self,
        original: AbstractASTNode | None,
        insert: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        if position == ParentAttributeSection.BODY:
            index = self.body.index(original)
            self.body.insert(index, insert)
            return True
        elif position == ParentAttributeSection.ELSE_BRANCH:
            index = self.else_node.index(original)
            self.else_node.insert(index, insert)
            return True
        return False

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        context.add_code("\nwhile (PY_getTruthValueOf(")
        self.condition.emit_c_code(base, context)
        context.add_code(")) {\n")

        exit_label = (
            base.get_fresh_name("while_exit_label") if self.else_node else "<break>"
        )

        block = context.get_statement_builder()

        for line in self.body:
            inner_block = block.get_statement_builder(indent=False)
            inner_block.parent = block
            inner_block.break_to_label = exit_label

            line.emit_c_code(base, inner_block)

            if isinstance(line, AbstractASTNodeExpression):
                inner_block.add_code(";\n")
            else:
                inner_block.add_code("\n")

            block.add_code(inner_block.get_result() + "\n")

        context.add_code(block.get_result())

        context.add_code("\n}\n")

        if self.else_node:
            for line in self.else_node:
                inner_block = block.get_statement_builder(indent=False)
                inner_block.parent = block

                line.emit_c_code(base, inner_block)

                if isinstance(line, AbstractASTNodeExpression):
                    inner_block.add_code(";\n")
                else:
                    inner_block.add_code("\n")

                context.add_code(inner_block.get_result() + "\n")

            context.add_code(f'{exit_label}:\n"marker";')


class ForLoopStatement(AbstractASTNode):
    def __init__(
        self,
        target: AbstractASTNode,
        iterator: AbstractASTNodeExpression,
        body: typing.List[AbstractASTNode],
        else_block: typing.List[AbstractASTNode],
    ):
        super().__init__()
        self.target = target
        self.iterator = iterator
        self.body = body
        self.else_block = else_block

    def __eq__(self, other):
        return (
            type(other) == ForLoopStatement
            and self.target == other.target
            and self.iterator == other.iterator
            and self.body == other.body
        )

    def __repr__(self):
        return f"FOR-LOOP({self.target} <- {self.iterator} | {self.body})"

    def try_replace_child(
        self,
        original: AbstractASTNode | None,
        replacement: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        pass

    def try_insert_before(
        self,
        original: AbstractASTNode | None,
        insert: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        pass

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        """
        PyObjectContainer* iterator = (@iterator).__iter__();
        PyObjectContainer* value = 'next'(iterator, NULL);
        while (value != NULL)
        {
            PY_CHECK_EXCEPTION(value);
            @target := value;
            @body;
            PyObjectContainer* value = 'next'(iterator, NULL);
        }
        """

        iterator = base.get_fresh_name("iterator")
        value = base.get_fresh_name("value")
        exit_label = (
            base.get_fresh_name("for_exit_label") if self.else_block else "<break>"
        )

        context.add_code(
            f"PyObjectContainer* {iterator} = PY_CHECK_EXCEPTION(PY_STD_operator_iter("
        )
        self.iterator.emit_c_code(base, context)
        context.add_code("));\n")
        context.add_code(
            f"PyObjectContainer* {value} = PY_STD_NEXT_FORWARD_arg_1({iterator}, NULL);\n"
        )
        context.add_code(f"while ({value} != NULL) {{\n")

        block = context.get_statement_builder()
        block.add_code(f"PY_CHECK_EXCEPTION({value});\n")

        source = GlobalCNameAccessExpression(value)
        source.scope = self.scope

        self.target.emit_c_code_for_write(base, block, source)
        block.add_code(";")

        for line in self.body:
            inner_block = block.get_statement_builder(indent=False)
            inner_block.parent = block
            inner_block.break_to_label = exit_label

            line.emit_c_code(base, inner_block)

            if isinstance(line, AbstractASTNodeExpression):
                inner_block.add_code(";\n")
            else:
                inner_block.add_code("\n")

            block.add_code(inner_block.get_result() + "\n")

        block.add_code(f"{value} = PY_STD_NEXT_FORWARD_arg_1({iterator}, NULL);")

        context.add_code(block.get_result())

        context.add_code("\n}\n")

        if self.else_block:
            for line in self.else_block:
                inner_block = block.get_statement_builder(indent=False)
                inner_block.parent = block

                line.emit_c_code(base, inner_block)

                if isinstance(line, AbstractASTNodeExpression):
                    inner_block.add_code(";\n")
                else:
                    inner_block.add_code("\n")

                context.add_code(inner_block.get_result() + "\n")

            context.add_code(f'{exit_label}:\n"marker";')


class IfStatement(AbstractASTNode):
    def __init__(
        self,
        main_condition: AbstractASTNodeExpression,
        main_block: typing.List[AbstractASTNode],
        elif_blocks: typing.List[
            typing.Tuple[AbstractASTNodeExpression, typing.List[AbstractASTNode]]
        ] = None,
        else_block: typing.List[AbstractASTNode] = None,
    ):
        super().__init__()
        self.main_condition = main_condition
        self.main_block = main_block
        self.elif_blocks = elif_blocks or []
        self.else_block = else_block

    def __eq__(self, other):
        return (
            type(other) == IfStatement
            and self.main_condition == other.main_condition
            and self.main_block == other.main_block
            and self.elif_blocks == other.elif_blocks
            and self.else_block == other.else_block
        )

    def __repr__(self):
        return f"IF-STATEMENT({self.main_condition}|{self.main_block}|{self.elif_blocks}|{self.else_block})"

    def try_replace_child(
        self,
        original: AbstractASTNode | None,
        replacement: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        if position == ParentAttributeSection.LHS:
            self.main_condition = replacement
        elif position == ParentAttributeSection.RHS:
            for i, line in enumerate(self.main_block):
                if line is original:
                    self.main_block[i] = replacement
                    break
            else:
                raise ValueError(original)
        elif position == ParentAttributeSection.PARAMETER:
            for i, (cond, nodes) in enumerate(self.elif_blocks):
                if cond is original:
                    self.elif_blocks[i] = replacement, nodes
                    break
            else:
                raise ValueError(original)
        elif position == ParentAttributeSection.BODY:
            for i, (cond, nodes) in enumerate(self.elif_blocks):
                for j, node in enumerate(nodes):
                    if node is original:
                        self.elif_blocks[i][j] = replacement
                        break
                else:
                    continue
                break
            else:
                raise ValueError(original)
        elif position == ParentAttributeSection.ELSE_BRANCH:
            for i, node in enumerate(self.else_block):
                if node is original:
                    self.else_block[i] = replacement
                    break
            else:
                raise ValueError(original)
        else:
            raise ValueError(position)

    def try_insert_before(
        self,
        original: AbstractASTNode | None,
        insert: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        raise RuntimeError("IfStatement try_insert_before")

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        context.add_code("if (PY_unpackBoolean(PY_CHECK_EXCEPTION(")
        self.main_condition.emit_c_code(base, context)
        context.add_code("))) {\n")
        self.emit_block(base, context, self.main_block)
        context.add_code("\n}\n")

        for cond, nodes in self.elif_blocks:
            context.add_code("else if (PY_unpackBoolean(PY_CHECK_EXCEPTION(")
            cond.emit_c_code(base, context)
            context.add_code("))) {\n")
            self.emit_block(base, context, nodes)
            context.add_code("\n}\n")

        if self.else_block:
            context.add_code("else {\n")
            self.emit_block(base, context, self.else_block)
            context.add_code("\n}\n")

    def emit_block(
        self,
        base: CCodeEmitter,
        context: CCodeEmitter.CExpressionBuilder,
        nodes: typing.List[AbstractASTNode],
    ):
        block = context.get_statement_builder()

        for line in nodes:
            inner_block = block.get_statement_builder(indent=False)
            inner_block.parent = block

            line.emit_c_code(base, inner_block)

            if isinstance(line, AbstractASTNodeExpression):
                inner_block.add_code(";\n")
            else:
                inner_block.add_code("\n")

            block.add_code(inner_block.get_result() + "\n")

        context.add_code(block.get_result())


class BinaryOperatorExpression(AbstractASTNodeExpression):
    class BinaryOperation(enum.Enum):
        PLUS = enum.auto()
        MINUS = enum.auto()
        MULTIPLY = enum.auto()
        FLOOR_DIV = enum.auto()
        TRUE_DIV = enum.auto()
        MODULO = enum.auto()
        POW = enum.auto()
        MATRIX_MULTIPLY = enum.auto()
        BIN_OR = enum.auto()
        BIN_AND = enum.auto()
        BIN_XOR = enum.auto()
        LOGIC_AND = enum.auto()
        LOGIC_OR = enum.auto()
        SHL = enum.auto()  # todo
        SHR = enum.auto()  # todo
        EQUALS = enum.auto()  # todo
        NOT_EQUALS = enum.auto()  # todo
        GREATER = enum.auto()  # todo
        GREATER_EQUAL = enum.auto()  # todo
        SMALLER = enum.auto()  # todo
        SMALLER_EQUAL = enum.auto()  # todo
        CONTAINS = enum.auto()
        CONTAINS_NOT = enum.auto()
        IS_SAME = enum.auto()
        IS_SAME_NOT = enum.auto()

    String2Type = {
        "+": BinaryOperation.PLUS,
        "-": BinaryOperation.MINUS,
        "*": BinaryOperation.MULTIPLY,
        "//": BinaryOperation.FLOOR_DIV,
        "/": BinaryOperation.TRUE_DIV,
        "%": BinaryOperation.MODULO,
        "**": BinaryOperation.POW,
        "@": BinaryOperation.MATRIX_MULTIPLY,
        "|": BinaryOperation.BIN_OR,
        "&": BinaryOperation.BIN_AND,
        "^": BinaryOperation.BIN_XOR,
        "==": BinaryOperation.EQUALS,
        "!=": BinaryOperation.NOT_EQUALS,
        ">": BinaryOperation.GREATER,
        ">=": BinaryOperation.GREATER_EQUAL,
        "<": BinaryOperation.SMALLER,
        "<=": BinaryOperation.SMALLER_EQUAL,
        "in": BinaryOperation.CONTAINS,
        "not in": BinaryOperation.CONTAINS_NOT,
        "is": BinaryOperation.IS_SAME,
        "is not": BinaryOperation.IS_SAME_NOT,
    }

    PRIORITIES: typing.Dict[BinaryOperation, int] = {
        BinaryOperation.LOGIC_AND: -20,
        BinaryOperation.LOGIC_OR: -20,
        BinaryOperation.EQUALS: -10,
        BinaryOperation.NOT_EQUALS: -10,
        BinaryOperation.GREATER: -10,
        BinaryOperation.GREATER_EQUAL: -10,
        BinaryOperation.SMALLER: -10,
        BinaryOperation.SMALLER_EQUAL: -10,
        BinaryOperation.PLUS: 0,
        BinaryOperation.MINUS: 0,
        BinaryOperation.BIN_OR: 0,
        BinaryOperation.BIN_AND: 0,
        BinaryOperation.BIN_XOR: 0,
        BinaryOperation.SHL: 0,
        BinaryOperation.SHR: 0,
        BinaryOperation.MULTIPLY: 10,
        BinaryOperation.TRUE_DIV: 10,
        BinaryOperation.FLOOR_DIV: 10,
        BinaryOperation.MODULO: 10,
        BinaryOperation.MATRIX_MULTIPLY: 10,
        BinaryOperation.POW: 20,
        BinaryOperation.CONTAINS: 30,  # warn: rhs is holder of __contains__, not lhs!
        BinaryOperation.CONTAINS_NOT: 30,
        BinaryOperation.IS_SAME: 40,
        BinaryOperation.IS_SAME_NOT: 40,
    }

    OPERATOR_CALL_FUNCTIONS = {
        BinaryOperation.PLUS: "PY_STD_operator_add",
        BinaryOperation.MINUS: "PY_STD_operator_sub",
        BinaryOperation.MULTIPLY: "PY_STD_operator_mul",
        BinaryOperation.TRUE_DIV: "PY_STD_operator_truediv",
        BinaryOperation.FLOOR_DIV: "PY_STD_operator_floordiv",
        BinaryOperation.MODULO: "PY_STD_operator_modulo",
        BinaryOperation.POW: "PY_STD_operator_pow",
        BinaryOperation.MATRIX_MULTIPLY: "PY_STD_operator_matrix_multiply",
        BinaryOperation.BIN_OR: "PY_STD_operator_bin_or",
        BinaryOperation.BIN_AND: "PY_STD_operator_bin_and",
        BinaryOperation.BIN_XOR: "PY_STD_operator_bin_xor",
        BinaryOperation.EQUALS: "PY_STD_operator_equals",
        BinaryOperation.NOT_EQUALS: "PY_STD_operator_not_equals",
        BinaryOperation.CONTAINS: "PY_STD_operator_contains",
        BinaryOperation.CONTAINS_NOT: "PY_STD_operator_not_contains",
        BinaryOperation.IS_SAME: "PY_STD_operator_is",
        BinaryOperation.IS_SAME_NOT: "PY_STD_operator_is_not",
    }

    PYTHON_OPERATOR_REFS = {
        BinaryOperation.PLUS: "__add__",
        BinaryOperation.MINUS: "__sub__",
        BinaryOperation.MULTIPLY: "__mul__",
        BinaryOperation.TRUE_DIV: "__truediv__",
        BinaryOperation.FLOOR_DIV: "__floordiv__",
        BinaryOperation.MODULO: "__mod__",
        BinaryOperation.POW: "__pow__",
        BinaryOperation.MATRIX_MULTIPLY: "__matmul__",
        BinaryOperation.BIN_OR: "__or__",
        BinaryOperation.BIN_AND: "__and__",
        BinaryOperation.BIN_XOR: "__xor__",
        BinaryOperation.EQUALS: "__eq__",
        BinaryOperation.CONTAINS: "__contains__",
    }

    def __init__(
        self, lhs: AbstractASTNode, operator: BinaryOperation, rhs: AbstractASTNode
    ):
        super().__init__()
        self.lhs = lhs
        self.operator = operator
        self.rhs = rhs

    def __eq__(self, other):
        return (
            type(other) == BinaryOperatorExpression
            and self.lhs == other.lhs
            and self.operator == other.operator
            and self.rhs == other.rhs
        )

    def __repr__(self):
        return f"OPERATION({self.lhs}|{self.operator.name}|{self.rhs})"

    def try_replace_child(
        self,
        original: AbstractASTNode | None,
        replacement: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        replacement.parent = self, position
        if position == ParentAttributeSection.LHS:
            self.lhs = replacement
        elif position == ParentAttributeSection.RHS:
            self.rhs = replacement
        else:
            return False
        return True

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        if self.operator in self.OPERATOR_CALL_FUNCTIONS:
            reverse = self.operator == BinaryOperatorExpression.BinaryOperation.CONTAINS

            func_name = self.OPERATOR_CALL_FUNCTIONS[self.operator]
            context.add_code(f"{func_name}(")
            (self.rhs if reverse else self.lhs).emit_c_code(base, context)
            context.add_code(", ")
            (self.lhs if reverse else self.rhs).emit_c_code(base, context)
            context.add_code(")")
        elif self.operator == self.BinaryOperation.LOGIC_OR:
            context.add_code(f"PY_createBoolean(PY_unpackBoolean(")
            self.lhs.emit_c_code(base, context)
            context.add_code(") || PY_unpackBoolean(")
            self.rhs.emit_c_code(base, context)
            context.add_code("))")
        elif self.operator == self.BinaryOperation.LOGIC_AND:
            context.add_code(f"PY_createBoolean(PY_unpackBoolean(")
            self.lhs.emit_c_code(base, context)
            context.add_code(") && PY_unpackBoolean(")
            self.rhs.emit_c_code(base, context)
            context.add_code("))")
        else:
            raise RuntimeError(self.operator)


class PrefixOperation(AbstractASTNodeExpression):
    class PrefixOperator(enum.Enum):
        NOT = enum.auto()
        NEGATE = enum.auto()
        POSITIVE = enum.auto()
        INVERT = enum.auto()

    OPERATOR_CALL_FUNCTIONS = {
        PrefixOperator.NOT: "PY_STD_operator_not",
        PrefixOperator.NEGATE: "PY_STD_operator_negate",
        PrefixOperator.POSITIVE: "PY_STD_operator_positive",
        PrefixOperator.INVERT: "PY_STD_operator_invert",
    }

    def __init__(
        self, operator: PrefixOperation.PrefixOperator, value: AbstractASTNode
    ):
        super().__init__()
        self.operator = operator
        self.value = value

    def __eq__(self, other):
        return (
            type(other) == PrefixOperation
            and self.operator == other.operator
            and self.value == other.value
        )

    def __repr__(self):
        return f"OPERATION({self.operator.name}|{self.value})"

    def try_replace_child(
        self,
        original: AbstractASTNode | None,
        replacement: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        replacement.parent = self, position
        if position == ParentAttributeSection.LHS:
            self.value = replacement
        else:
            return False
        return True

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        if self.operator in self.OPERATOR_CALL_FUNCTIONS:
            func_name = self.OPERATOR_CALL_FUNCTIONS[self.operator]
            context.add_code(f"{func_name}(")
            self.value.emit_c_code(base, context)
            context.add_code(")")
        else:
            raise RuntimeError(self.operator)


class InplaceOperator(AbstractASTNode):
    class InplaceOperation(enum.Enum):
        PLUS = enum.auto()
        MINUS = enum.auto()
        MULTIPLY = enum.auto()
        FLOOR_DIV = enum.auto()
        TRUE_DIV = enum.auto()
        MODULO = enum.auto()
        POW = enum.auto()
        MATRIX_MULTIPLY = enum.auto()
        BIN_OR = enum.auto()
        BIN_AND = enum.auto()
        BIN_XOR = enum.auto()
        SHL = enum.auto()  # todo
        SHR = enum.auto()  # todo

    OPERATOR_CALL_FUNCTIONS = {
        InplaceOperation.PLUS: "PY_STD_operator_inplace_add",
        InplaceOperation.MINUS: "PY_STD_operator_inplace_sub",
        InplaceOperation.MULTIPLY: "PY_STD_operator_inplace_mul",
        InplaceOperation.TRUE_DIV: "PY_STD_operator_inplace_truediv",
        InplaceOperation.FLOOR_DIV: "PY_STD_operator_inplace_floordiv",
        InplaceOperation.MODULO: "PY_STD_operator_inplace_modulo",
        InplaceOperation.POW: "PY_STD_operator_inplace_pow",
        InplaceOperation.MATRIX_MULTIPLY: "PY_STD_operator_inplace_matrix_multiply",
        InplaceOperation.BIN_OR: "PY_STD_operator_inplace_bin_or",
        InplaceOperation.BIN_AND: "PY_STD_operator_inplace_bin_and",
        InplaceOperation.BIN_XOR: "PY_STD_operator_inplace_bin_xor",
    }

    PYTHON_OPERATOR_REFS = {
        InplaceOperation.PLUS: "__iadd__",
        InplaceOperation.MINUS: "__isub__",
        InplaceOperation.MULTIPLY: "__imul__",
        InplaceOperation.TRUE_DIV: "__itruediv__",
        InplaceOperation.FLOOR_DIV: "__ifloordiv__",
        InplaceOperation.MODULO: "__imod__",
        InplaceOperation.POW: "__ipow__",
        InplaceOperation.MATRIX_MULTIPLY: "__imatmul__",
        InplaceOperation.BIN_OR: "__ior__",
        InplaceOperation.BIN_AND: "__iand__",
        InplaceOperation.BIN_XOR: "__ixor__",
    }

    def __init__(
        self, lhs: AbstractASTNode, operator: InplaceOperation, rhs: AbstractASTNode
    ):
        super().__init__()
        self.lhs = lhs
        self.operator = operator
        self.rhs = rhs

    def __eq__(self, other):
        return (
            type(other) == BinaryOperatorExpression
            and self.lhs == other.lhs
            and self.operator == other.operator
            and self.rhs == other.rhs
        )

    def __repr__(self):
        return f"INPLACE-OPERATION({self.lhs}|{self.operator.name}|{self.rhs})"

    def try_replace_child(
        self,
        original: AbstractASTNode | None,
        replacement: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        replacement.parent = self, position
        if position == ParentAttributeSection.LHS:
            self.lhs = replacement
        elif position == ParentAttributeSection.RHS:
            self.rhs = replacement
        else:
            return False
        return True

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        if self.operator in self.OPERATOR_CALL_FUNCTIONS:
            func_name = self.OPERATOR_CALL_FUNCTIONS[self.operator]

            self.lhs.emit_c_code_for_write(
                base,
                context,
                CallExpression(
                    GlobalCNameAccessExpression(func_name),
                    [],
                    None,
                    [
                        CallExpression.CallExpressionArgument(
                            self.lhs,
                            CallExpression.ParameterType.NORMAL,
                        ),
                        CallExpression.CallExpressionArgument(
                            self.rhs,
                            CallExpression.ParameterType.NORMAL,
                        ),
                    ],
                    None,
                ),
            )
            context.add_code(";")
        else:
            raise RuntimeError(self.operator)


class WalrusOperatorExpression(AbstractASTNodeExpression):
    def __init__(self, target: AbstractASTNode, value: AbstractASTNode):
        super().__init__()
        self.target = target
        self.value = value

    def __eq__(self, other):
        return (
            type(other) == WalrusOperatorExpression
            and self.target == other.target
            and self.value == other.value
        )

    def __repr__(self):
        return f"WALRUS_OPERATOR({self.target}|{self.value})"

    def try_replace_child(
        self,
        original: AbstractASTNode | None,
        replacement: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        replacement.parent = self, position
        if position == ParentAttributeSection.LHS:
            self.target = replacement
        elif position == ParentAttributeSection.RHS:
            self.value = replacement
        else:
            return False
        return True

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        self.target.emit_c_code(base, context)
        context.add_code(" = ")
        self.value.emit_c_code(base, context)


class AssertStatement(AbstractASTNode):
    def __init__(self, statement: AbstractASTNode, message: AbstractASTNode | None):
        super().__init__()
        self.statement = statement
        self.message = message

    def __eq__(self, other):
        return (
            type(other) == AssertStatement
            and self.statement == other.statement
            and self.message == other.message
        )

    def __repr__(self):
        return f"ASSERT({self.statement}|{self.message})"

    def try_replace_child(
        self,
        original: AbstractASTNode | None,
        replacement: AbstractASTNode,
        position: ParentAttributeSection,
    ) -> bool:
        replacement.parent = self, position
        if position == ParentAttributeSection.LHS:
            self.statement = replacement
        elif position == ParentAttributeSection.RHS:
            self.message = replacement
        else:
            return False
        return True

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        base.add_include("<assert.h>")
        name = base.get_fresh_name("assert_target")
        context.add_code(f"PyObjectContainer* {name} = PY_CHECK_EXCEPTION(")
        self.statement.emit_c_code(base, context)
        context.add_code(");\n")
        if self.message is None:
            context.add_code(f"assert(PY_getTruthValueOf({name}));\n")
        else:
            context.add_code(f"assert(PY_getTruthValueOf({name}) && ")
            self.message.emit_c_code(base, context)
            context.add_code(");\n")


class ImportStatement(AbstractASTNode):
    def __init__(self, module: str, as_name: str = None):
        super().__init__()
        self.module = module
        self.as_name = as_name

    def __repr__(self):
        return f"MODULE_IMPORT({self.module}{'' if self.as_name is None else f', {self.as_name}'})"

    def __eq__(self, other):
        return (
            type(other) == ImportStatement
            and self.module == other.module
            and self.as_name == other.as_name
        )

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        # initialise all modules in the path to our module
        for i in range(self.module.count(".") - 1):
            partial_module = "___".join(self.module.split(".")[: i + 1])

            base.add_include(f'"{partial_module}.h"')
            context.add_code(f"PY_CHECK_EXCEPTION(PY_MODULE_{partial_module}_init());")

        name = self.module.replace(".", "___")

        if self.module not in Scope.STANDARD_LIBRARY_MODULES:
            base.add_include(f'"{name}.h"')
        else:
            base.add_include(
                f'"{Scope.STANDARD_LIBRARY_MODULES[self.module].header_name}"'
            )

        context.add_code(f"PY_CHECK_EXCEPTION(PY_MODULE_{name}_init());\n")
        context.add_code(
            f"{self.scope.get_remapped_name(self.as_name or self.module.split('.')[0])} = PY_MODULE_INSTANCE_{name};\n"
        )


class ModuleReference(AbstractASTNode):
    def __init__(self, name: str):
        super().__init__()
        self.name = name
        self.base_scope = {}

    def __repr__(self):
        return f"MODULE-REF({self.name})"

    def __eq__(self, other):
        return (
            type(other) == ModuleReference
            and self.name == other.name
            and self.base_scope == other.base_scope
        )

    def emit_c_code(self, base: CCodeEmitter, context: CCodeEmitter.CExpressionBuilder):
        return f"PY_MODULE_INSTANCE_{self.name.replace('.', '___')}"


class StandardLibraryModuleReference(ModuleReference):
    def __init__(self, name: str, header_name: str):
        super().__init__(name)
        self.header_name = header_name


class SyntaxTreeVisitor:
    def __init__(self):
        self.node_cache = set()

    def reset(self):
        self.node_cache.clear()

    def visit_any(self, obj: AbstractASTNode):
        if obj is None:
            return

        if id(obj) in self.node_cache:
            return

        self.node_cache.add(id(obj))

        obj_type = type(obj)

        if obj_type == PyNewlineNode:
            return self.visit_newline(obj)
        elif obj_type == PyCommentNode:
            return self.visit_comment(obj)
        elif obj_type == AssignmentExpression:
            return self.visit_assignment(obj)
        elif obj_type == NameAccessExpression:
            return self.visit_name_access(obj)
        elif obj_type == GlobalCNameAccessExpression:
            return self.visit_global_c_name_access(obj)
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
        elif obj_type == GeneratorExitReturnStatement:
            return self.visit_return_statement(obj)
        elif obj_type == ClassDefinitionNode:
            return self.visit_class_definition(obj)
        elif obj_type == ConstantAccessExpression:
            return self.visit_constant(obj)
        elif obj_type == WhileStatement:
            return self.visit_while_statement(obj)
        elif obj_type == ForLoopStatement:
            return self.visit_for_statement(obj)
        elif obj_type == PriorityBrackets:
            return self.visit_priority_bracket(obj)
        elif obj_type == TupleConstructor:
            return self.visit_tuple_constructor(obj)
        elif obj_type == ListConstructor:
            return self.visit_list_constructor(obj)
        elif obj_type == DictConstructor:
            return self.visit_dict_constructor(obj)
        elif obj_type == PassStatement:
            return self.visit_pass_statement(obj)
        elif obj_type == BinaryOperatorExpression:
            return self.visit_binary_operator(obj)
        elif obj_type == InplaceOperator:
            return self.visit_inplace_operator(obj)
        elif obj_type == AssertStatement:
            return self.visit_assert_statement(obj)
        elif obj_type == ModuleReference:
            return self.visit_module_reference(obj)
        elif obj_type == ImportStatement:
            return self.visit_import_statement(obj)
        elif obj_type == StandardLibraryClass:
            return self.visit_standard_library_class(obj)
        elif obj_type == StandardLibraryBoundOperator:
            return self.visit_standard_library_operator(obj)
        elif obj_type == YieldStatement:
            return self.visit_yield_statement(obj)
        elif obj_type == GeneratorNameAccessExpression:
            return self.visit_name_access(obj)
        elif obj_type == IfStatement:
            return self.visit_if_statement(obj)
        elif obj_type == PrefixOperation:
            return self.visit_prefix_operation(obj)
        elif obj_type == ListComprehension:
            return self.visit_list_comprehension(obj)
        elif obj_type == WalrusOperatorExpression:
            return self.visit_walrus_operator(obj)
        else:
            print(type(obj))
            raise RuntimeError(obj)

    def visit_any_list(self, objs: typing.List[AbstractASTNode]):
        if objs is None:
            return None
        return [self.visit_any(obj) for obj in objs]

    def visit_newline(self, newline: PyNewlineNode):
        pass

    def visit_comment(self, comment: PyCommentNode):
        pass

    def visit_assignment(self, assignment: AssignmentExpression):
        return [self.visit_any(target) for target in assignment.lhs], self.visit_any(
            assignment.rhs
        )

    def visit_name_access(self, access: NameAccessExpression):
        pass

    def visit_global_c_name_access(self, access: GlobalCNameAccessExpression):
        pass

    def visit_attribute_expression(self, expression: AttributeExpression):
        return (self.visit_any(expression.base),)

    def visit_subscription_expression(self, expression: SubscriptionExpression):
        return self.visit_any(expression.base), self.visit_any(expression.expression)

    def visit_call_expression(self, node: CallExpression):
        return self.visit_any(node.base), [
            self.visit_call_argument(arg) for arg in node.args
        ]

    def visit_call_argument(self, arg: CallExpression.CallExpressionArgument):
        return (self.visit_any(arg.value),)

    def visit_function_definition(self, node: FunctionDefinitionNode):
        return [
            self.visit_function_definition_parameter(param) for param in node.parameters
        ], self.visit_any_list(node.body)

    def visit_function_definition_parameter(
        self, node: FunctionDefinitionNode.FunctionDefinitionParameter
    ):
        if node.mode == FunctionDefinitionNode.ParameterType.KEYWORD:
            assert node.default is not None

            return (self.visit_any(node.default),)

        return (None,)

    def visit_class_definition(self, node: ClassDefinitionNode):
        return self.visit_any_list(node.parents), self.visit_any_list(node.body)

    def visit_constant(self, constant: ConstantAccessExpression):
        if isinstance(constant.value, AbstractASTNode):
            self.visit_any(constant.value)

    def visit_return_statement(self, return_statement: ReturnStatement):
        return (self.visit_any(return_statement.return_value),)

    def visit_yield_statement(self, yield_statement: YieldStatement):
        return (self.visit_any(yield_statement.yield_expression),)

    def visit_while_statement(self, while_statement: WhileStatement):
        return (
            self.visit_any(while_statement.condition),
            self.visit_any_list(while_statement.body),
            self.visit_any_list(while_statement.else_node),
        )

    def visit_for_statement(self, for_statement: ForLoopStatement):
        return (
            self.visit_any(for_statement.iterator),
            self.visit_any(for_statement.target),
            self.visit_any_list(for_statement.body),
            self.visit_any_list(for_statement.else_block),
        )

    def visit_if_statement(self, if_statement: IfStatement):
        return (
            self.visit_any(if_statement.main_condition),
            self.visit_any_list(if_statement.main_block),
            [
                (
                    self.visit_any(cond),
                    self.visit_any_list(nodes),
                )
                for cond, nodes in if_statement.elif_blocks
            ],
            self.visit_any_list(if_statement.else_block),
        )

    def visit_binary_operator(self, operator: BinaryOperatorExpression):
        return self.visit_any(operator.lhs), self.visit_any(operator.rhs)

    def visit_inplace_operator(self, operator: InplaceOperator):
        return self.visit_any(operator.lhs), self.visit_any(operator.rhs)

    def visit_walrus_operator(self, operator: WalrusOperatorExpression):
        return self.visit_any(operator.target), self.visit_any(operator.value)

    def visit_priority_bracket(self, node: PriorityBrackets):
        return (self.visit_any(node.inner_node),)

    def visit_tuple_constructor(self, node: TupleConstructor):
        return (self.visit_any_list(node.items),)

    def visit_list_constructor(self, node: ListConstructor):
        return (self.visit_any_list(node.items),)

    def visit_dict_constructor(self, node: DictConstructor):
        return (
            [
                (self.visit_any(key), self.visit_any(value))
                for key, value in node.key_value_pairs
            ],
        )

    def visit_pass_statement(self, node: PassStatement):
        pass

    def visit_assert_statement(self, node: AssertStatement):
        return self.visit_any(node.statement), (
            self.visit_any(node.message) if node.message else None
        )

    def visit_module_reference(self, module: ModuleReference):
        pass

    def visit_import_statement(self, node: ImportStatement):
        pass

    def visit_standard_library_class(self, cls: StandardLibraryClass):
        pass

    def visit_standard_library_operator(self, instance: StandardLibraryBoundOperator):
        pass

    def visit_prefix_operation(self, operation: PrefixOperation):
        return (self.visit_any(operation.value),)

    def visit_list_comprehension(self, comprehension: ListComprehension):
        return (
            self.visit_any(comprehension.base_expression),
            self.visit_any(comprehension.target_expression),
            self.visit_any(comprehension.iterable),
            self.visit_any(comprehension.if_node),
        )


def _parse_data_type(entry: dict) -> AbstractDataType | None:
    pass  # todo: implement


def _parse_std_lib_decl_entry(entry: dict) -> AbstractASTNode:
    if entry["type"] == "class":
        cls = StandardLibraryClass(entry["name"], entry["type variable"])

        for attr in entry.get("static attributes", []):
            if "arguments" in attr:
                cls.function_table[
                    (attr["name"], attr["arguments"])
                ] = _parse_std_lib_decl_entry(attr)
            else:
                cls.function_table[attr["name"]] = _parse_std_lib_decl_entry(attr)

        return cls

    elif entry["type"] in ("method", "constant"):
        obj = GlobalCNameAccessExpression(entry["c name"], declare=False)

        if entry["type"] == "method" and "return type" in entry:
            obj.data_type = _parse_data_type(entry["return type"])
        elif entry["type"] == "constant" and "data type" in entry:
            obj.data_type = _parse_data_type(entry["data type"])

        return obj

    elif entry["type"] == "operator wrapper":
        return StandardLibraryBoundOperator(entry["name"], entry["c name"])

    raise NotImplementedError(entry["type"])


def load_std_data():
    with open(
        os.path.join(os.path.dirname(__file__), "standard_library_config.json")
    ) as f:
        std_lib_data = json.load(f)

    for module in std_lib_data:
        if module["module"] == "builtins":
            target = Scope.STANDARD_LIBRARY_VALUES

            for entry in module["items"]:
                target.setdefault(entry["name"], {})[
                    entry.get("arguments", "*")
                ] = _parse_std_lib_decl_entry(entry)
        else:
            module_obj = StandardLibraryModuleReference(
                module["module"], module["header"]
            )
            Scope.STANDARD_LIBRARY_MODULES[module["module"]] = module_obj

            for entry in module["items"]:
                module_obj.base_scope[entry["name"]] = _parse_std_lib_decl_entry(entry)


load_std_data()


class Parser:
    def __init__(self, source: str):
        self.source = source
        self.lexer = Lexer.Lexer(source)
        self.indent_level = 0
        self.indent_markers: str | None = None
        self.is_in_function = False
        self.skip_end_check = False
        self.is_in_singleline_expression = False

    def parse(
        self, stop_on_indention_exit=False, mention_on_yield=None
    ) -> typing.List[AbstractASTNode]:
        ast_stream: typing.List[AbstractASTNode] = []

        require_indent = True

        while self.lexer.has_text():
            while newline := self.lexer.try_parse_newline():
                ast_stream.append(PyNewlineNode(newline))

            if not self.lexer.has_text():
                break

            try:
                node = self.parse_line(
                    require_indent=require_indent, mention_on_yield=mention_on_yield
                )
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
                elif self.lexer.inspect_chars(1) == "#":
                    node = self.try_parse_comment()
                else:
                    require_indent = True

                    if self.lexer.inspect_chars(1) not in ("\n", None):
                        print("count:", len(ast_stream))
                        for n in ast_stream:
                            print(n)
                        print("current:", node)
                        print(self.indent_level)
                        print(repr(self.lexer.file[self.lexer.file_cursor :]))
                        raise SyntaxError(
                            f"expected <newline> or ';' after expression, got {repr(self.lexer.get_chars(1))}"
                        )

            self.skip_end_check = False

            if node is not None:
                ast_stream.append(node)
            else:
                print(
                    repr(self.lexer.file[self.lexer.file_cursor :]),
                    len(self.lexer.file[self.lexer.file_cursor :]),
                )
                raise SyntaxError("no valid instruction found")

        return ast_stream

    def emit_pure_c_code(
        self, expr: typing.List[AbstractASTNode] = None, module_name: str = None
    ) -> str:
        from pycompiler.TypeResolver import (
            ResolveParentAttribute,
            ScopeGeneratorVisitor,
            LocalNameValidator,
            ResolveKnownDataTypes,
            ResolveLocalVariableAccessTypes,
            ResolveClassFunctionNode,
            ResolveStaticNames,
            ResolveGlobalNames,
            NameNormalizer,
            BinaryOperatorPriorityRewriter,
        )

        scope = Scope()

        if expr is None:
            expr = self.parse()

        ResolveParentAttribute().visit_any_list(expr)
        BinaryOperatorPriorityRewriter().visit_any_list(expr)
        ScopeGeneratorVisitor(scope).visit_any_list(expr)
        NameNormalizer().visit_any_list(expr)
        LocalNameValidator().visit_any_list(expr)
        ResolveStaticNames().visit_any_list(expr)

        ResolveLocalVariableAccessTypes.DIRTY = True
        while ResolveLocalVariableAccessTypes.DIRTY:
            ResolveKnownDataTypes().visit_any_list(expr)
            ResolveClassFunctionNode().visit_any_list(expr)

            ResolveLocalVariableAccessTypes.DIRTY = False
            ResolveLocalVariableAccessTypes().visit_any_list(expr)

        ResolveGlobalNames().visit_any_list(expr)

        return self.emit_c_code(expr, module_name, scope=scope)

    def emit_c_code(
        self,
        expr: typing.List[AbstractASTNode] = None,
        module_name: str = None,
        scope: Scope = None,
    ) -> str:
        normal_module_name = module_name.replace(".", "___")

        scope = scope or Scope()

        if expr is None:
            expr = self.parse()

        builder = CCodeEmitter(scope)
        builder.module_name = module_name
        main = builder.CFunctionBuilder(
            f"PY_MODULE_{module_name.replace('.', '___') if module_name else 'unknown'}_init",
            [],
            "PyObjectContainer*",
            scope,
        )

        if module_name is None:
            raise RuntimeError

        builder.add_function(main)
        builder.init_function = main

        if expr:
            skip_names = [
                line.name.text
                for line in expr
                if isinstance(line, (FunctionDefinitionNode, ClassDefinitionNode))
            ]

            # for var in expr[0].scope.variable_name_stack:
            #     if var not in skip_names:
            #         main.add_code(
            #             f"PyObjectContainer* {expr[0].scope.get_remapped_name(var)};\n"
            #         )

        vars = set()
        for line in expr:
            if not isinstance(line, (FunctionDefinitionNode, ClassDefinitionNode)):
                vars |= line.scope.variable_name_stack

        main.add_code("INVOKE_SINGLE();\n")
        main.add_code("PY_STD_INIT();\n")
        main.add_code("#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE\n")
        main.add_code(
            f'PY_MODULE_INSTANCE_{normal_module_name} = PY_createModuleObject("{module_name}");\n'
        )
        main.add_code("#endif\n")

        for var in sorted(list(vars)):
            main.add_code(f"PyObjectContainer* {scope.get_remapped_name(var)};\n")

        class FuncDefVisitor(SyntaxTreeVisitor):
            def visit_function_definition(self, node: FunctionDefinitionNode):
                global_name = builder.get_fresh_name(
                    f"function_container_{node.name.text}"
                )
                builder.add_global_variable("PyObjectContainer*", global_name)
                node.global_container_name = global_name

        FuncDefVisitor().visit_any_list(expr)

        for line in expr:
            inner_block = main.get_statement_builder(indent=False)

            line.emit_c_code(builder, inner_block)

            if isinstance(line, AbstractASTNodeExpression):
                inner_block.add_code(";\n")
            else:
                inner_block.add_code("\n")

            main.add_code(inner_block.get_result() + "\n")

        # for var in sorted(list(vars)):
        #     main.add_code(
        #         f"PY_setObjectAttributeByName(PY_MODULE_INSTANCE_{normal_module_name}, \"{main.scope.get_unmapped_name(var)}\", {var});\n"
        #     )

        main.add_code("#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE\n")
        main.add_code(
            f"PY_exposeModuleObject(PY_MODULE_INSTANCE_{normal_module_name});\n"
        )
        main.add_code("#endif\n")

        code = f"""#include <stdlib.h>

#include "pyinclude.h"
#include "standard_library/config.h"

#include "standard_library/init.h"
#include "standard_library/exceptions.h"

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
#include "standard_library/importhelper.h"
#endif

#include "{normal_module_name}.h"

#ifdef PY_ENABLE_DYNAMIC_OBJECT_ATTRIBUTE
PyObjectContainer* PY_MODULE_INSTANCE_{normal_module_name};
#endif

// code compiled from python to c via PyCodeCompiler

"""

        for include in builder.includes:
            code += f"#include {include}\n"

        if builder.includes:
            code += "\n\n"

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

    def try_get_indent(self) -> str | None:
        if self.indent_level == 0:
            return ""

        self.lexer.save_state()
        empty = self.lexer.try_parse_whitespaces()

        if self.lexer.inspect_chars(1) == "\n":
            self.lexer.rollback_state()
            return

        if self.indent_markers:
            if not empty or empty.text != self.indent_markers * self.indent_level:
                self.lexer.rollback_state()
                return

        else:
            if not empty or not empty.text:
                self.lexer.rollback_state()
                return

            self.indent_markers = empty.text[: len(empty.text) // self.indent_level]

            if empty.text != self.indent_markers * self.indent_level:
                self.lexer.rollback_state()
                return

        self.lexer.discard_save_state()
        return empty

    def parse_line(
        self, require_indent=True, include_comment=True, mention_on_yield=None
    ) -> AbstractASTNode | None:
        if include_comment and (comment := self.try_parse_comment()):
            return comment

        if require_indent:
            if self.try_get_indent() is None:
                raise IndentationError

        if function := self.try_parse_function_definition():
            return function

        if cls := self.try_parse_class_node():
            return cls

        if while_statement := self.try_parse_while_statement():
            return while_statement

        if for_statement := self.try_parse_for_statement():
            return for_statement

        if if_statement := self.try_parse_if_statement():
            return if_statement

        if (self.indent_level != 0 or self.is_in_singleline_expression) and (
            pass_statement := self.try_parse_pass_statement()
        ):
            return pass_statement

        if assert_statement := self.try_parse_assert_statement():
            return assert_statement

        if import_statement := self.try_parse_import_statement():
            return import_statement

        if self.is_in_function and (
            return_statement := self.try_parse_return_statement()
        ):
            return return_statement

        if self.is_in_function and (
            yield_statement := self.try_parse_yield_statement()
        ):
            if mention_on_yield:
                mention_on_yield()

            return yield_statement

        if assignment := self.try_parse_assignment():
            return assignment

        if expression := self.try_parse_expression():
            return expression

    def try_parse_assignment_target(
        self, tuple_assignment_requires_brackets=True
    ) -> AbstractASTNode | None:
        if self.lexer.inspect_chars(1) == "(":
            return self.try_parse_prim_unpack(
                ")", TupleConstructor, single_is_inner=True
            )

        # if self.lexer.inspect_chars(1) == "[":
        #     return self.try_parse_prim_unpack("]", ListConstructor)

        identifier = self.lexer.try_parse_identifier()

        if identifier is None:
            return

        base = NameAccessExpression(identifier)

        while True:
            if opening_square_bracket := self.lexer.try_parse_opening_square_bracket():
                expression = self.try_parse_expression()

                if expression is None or not (
                    closing_bracket := self.lexer.try_parse_closing_square_bracket()
                ):
                    raise SyntaxError

                base = SubscriptionExpression(
                    base,
                    opening_square_bracket,
                    expression,
                    closing_bracket,
                )

            else:
                break

        self.lexer.try_parse_whitespaces()
        if (
            not tuple_assignment_requires_brackets
            and self.lexer.inspect_chars(1) == ","
        ):
            self.lexer.get_chars(1)
            base = TupleConstructor([base])

            while True:
                self.lexer.try_parse_whitespaces()
                target = self.try_parse_assignment_target()

                if target is None:
                    return base

                base.items.append(target)

                self.lexer.try_parse_whitespaces()
                if self.lexer.inspect_chars(1) != ",":
                    return base

                self.lexer.get_chars(1)

        return base

    def try_parse_prim_unpack(
        self, closing_bracket: str, class_type: typing.Type, single_is_inner=False
    ):
        self.lexer.save_state()
        self.lexer.get_chars(1)

        if self.lexer.inspect_chars(1) == closing_bracket:
            if single_is_inner:
                self.lexer.rollback_state()
                return

            return class_type([])

        target = self.try_parse_assignment_target()

        if target is None:
            self.lexer.rollback_state()
            return

        self.lexer.discard_save_state()
        self.lexer.save_state()
        self.lexer.try_parse_whitespaces()

        if self.lexer.inspect_chars(1) == closing_bracket:
            if single_is_inner:
                return target

            return class_type([target])

        if self.lexer.inspect_chars(1) != ",":
            self.lexer.rollback_state()
            return

        self.lexer.get_chars(1)
        target = class_type([target])

        while True:
            self.lexer.try_parse_whitespaces()
            if self.lexer.inspect_chars(1) == closing_bracket:
                self.lexer.get_chars(1)
                self.lexer.discard_save_state()
                return target

            item = self.try_parse_assignment_target()
            self.lexer.try_parse_whitespaces()

            if item is None:
                self.lexer.discard_save_state()
                return target

            target.items.append(item)

            if self.lexer.inspect_chars(1) != ",":
                self.lexer.discard_save_state()
                if self.lexer.inspect_chars(1) != closing_bracket:
                    raise SyntaxError

                self.lexer.get_chars(1)
                return target

            self.lexer.get_chars(1)

    def try_parse_expression(
        self, generators_require_brackets=True
    ) -> AbstractASTNode | None:
        self.lexer.try_parse_whitespaces()
        identifier = self.lexer.try_parse_identifier()

        if identifier is None:
            c = self.lexer.inspect_chars(1)

            if not c:
                return

            if c.isdigit() or c == "-" or c == ".":
                base = self.try_parse_integer_or_float()

                if base is None:
                    self.lexer.get_chars(1)
                    expr = self.try_parse_expression()
                    return PrefixOperation(PrefixOperation.PrefixOperator.NEGATE, expr)

            elif c == "+":
                self.lexer.get_chars(1)
                expr = self.try_parse_expression()
                return PrefixOperation(PrefixOperation.PrefixOperator.POSITIVE, expr)

            elif c == "~":
                self.lexer.get_chars(1)
                expr = self.try_parse_expression()
                return PrefixOperation(PrefixOperation.PrefixOperator.INVERT, expr)

            elif c == "'":
                base = self.parse_quoted_string("'")
            elif c == '"':
                base = self.parse_quoted_string('"')

            elif c == "(":  # PriorityBracket or TUPLE
                self.lexer.save_state()
                self.lexer.get_chars(1)
                self.lexer.try_parse_whitespaces()

                if self.lexer.inspect_chars(1) == ")":
                    self.lexer.get_chars(1)
                    return TupleConstructor([])

                inner = self.try_parse_expression()
                if inner is None:
                    raise SyntaxError("expected <inner expression>, got 'None'")

                self.lexer.try_parse_whitespaces()
                if self.lexer.inspect_chars(1) == ",":  # TUPLE
                    base = self.try_parse_expression_tuple_like(inner)

                elif self.lexer.inspect_chars(1) == ")":  # PriorityBracket
                    self.lexer.get_chars(1)
                    self.lexer.discard_save_state()

                    base = PriorityBrackets(inner)

                elif self.lexer.inspect_chars(3) == "for":
                    self.lexer.get_chars(3)
                    self.lexer.try_parse_whitespaces()

                    target = self.try_parse_assignment_target(
                        tuple_assignment_requires_brackets=False
                    )

                    if target is None:
                        self.lexer.rollback_state()
                        return

                    self.lexer.try_parse_whitespaces()

                    if self.lexer.get_chars(2) != "in":
                        self.lexer.rollback_state()
                        return

                    self.lexer.try_parse_whitespaces()
                    iterable = self.try_parse_expression()

                    if iterable is None:
                        self.lexer.rollback_state()
                        return

                    if_node = None
                    if self.lexer.inspect_chars(2) == "if":
                        self.lexer.get_chars(2)

                        if_node = self.try_parse_expression()

                        if if_node is None:
                            self.lexer.rollback_state()
                            return

                    self.lexer.discard_save_state()
                    return GeneratorExpression(inner, target, iterable, if_node)

                else:
                    self.lexer.rollback_state()
                    return

            elif c == "[":
                base = self.try_pase_expression_list_like()

            elif c == "{":
                base = self.try_pase_expression_dict_like()

            else:
                return

        elif identifier.text == "not":
            expr = self.try_parse_expression()

            return PrefixOperation(PrefixOperation.PrefixOperator.NOT, expr)

        else:
            base = NameAccessExpression(identifier)

        can_be_target = True

        while True:
            self.lexer.try_parse_whitespaces()

            # todo: allow slices
            if opening_square_bracket := self.lexer.try_parse_opening_square_bracket():
                expression = self.try_parse_expression()

                if expression is None or not (
                    closing_bracket := self.lexer.try_parse_closing_square_bracket()
                ):
                    print(base)
                    raise SyntaxError(
                        f"expected ')', got '{self.lexer.inspect_chars(4)}'"
                    )

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
                can_be_target = False

            elif self.lexer.inspect_chars(2) == ":=" and can_be_target:
                self.lexer.get_chars(2)
                self.lexer.try_parse_whitespaces()
                expression = self.try_parse_expression()
                if expression is None:
                    raise SyntaxError
                base = WalrusOperatorExpression(base, expression)

            elif (
                self.lexer.inspect_chars(1)
                and self.lexer.inspect_chars(1) in "+-*%/&|^@i"
            ):
                if self.lexer.inspect_chars(2) in ("**", "//", "in", "is"):
                    operator = self.lexer.get_chars(2)

                    if operator == "is":
                        self.lexer.try_parse_whitespaces()

                        if self.lexer.inspect_chars(3) == "not":
                            self.lexer.get_chars(3)
                            operator = "is not"
                else:
                    operator = self.lexer.get_chars(1)

                expression = self.try_parse_expression()
                if expression is None:
                    raise SyntaxError

                base = BinaryOperatorExpression(
                    base, BinaryOperatorExpression.String2Type[operator], expression
                )

            elif self.lexer.inspect_chars(len("not in")) == "not in":
                operator = "not in"
                expression = self.try_parse_expression()
                if expression is None:
                    raise SyntaxError

                base = BinaryOperatorExpression(
                    base, BinaryOperatorExpression.String2Type[operator], expression
                )

            elif self.lexer.inspect_chars(4) == "and ":
                self.lexer.get_chars(4)
                expression = self.try_parse_expression()
                if expression is None:
                    raise SyntaxError

                base = BinaryOperatorExpression(
                    base, BinaryOperatorExpression.BinaryOperation.LOGIC_AND, expression
                )

            elif self.lexer.inspect_chars(3) == "or ":
                self.lexer.get_chars(3)
                expression = self.try_parse_expression()
                if expression is None:
                    raise SyntaxError

                base = BinaryOperatorExpression(
                    base, BinaryOperatorExpression.BinaryOperation.LOGIC_OR, expression
                )

            elif self.lexer.inspect_chars(2) == "==":
                self.lexer.get_chars(2)
                expression = self.try_parse_expression()
                base = BinaryOperatorExpression(
                    base, BinaryOperatorExpression.BinaryOperation.EQUALS, expression
                )

            elif self.lexer.inspect_chars(2) == "!=":
                self.lexer.get_chars(2)
                expression = self.try_parse_expression()
                base = BinaryOperatorExpression(
                    base,
                    BinaryOperatorExpression.BinaryOperation.NOT_EQUALS,
                    expression,
                )

            elif self.lexer.inspect_chars(2) == ">=":
                self.lexer.get_chars(2)
                expression = self.try_parse_expression()
                base = BinaryOperatorExpression(
                    base,
                    BinaryOperatorExpression.BinaryOperation.GREATER_EQUAL,
                    expression,
                )

            elif self.lexer.inspect_chars(1) == ">":
                self.lexer.get_chars(1)
                expression = self.try_parse_expression()
                base = BinaryOperatorExpression(
                    base, BinaryOperatorExpression.BinaryOperation.GREATER, expression
                )

            elif self.lexer.inspect_chars(2) == "<=":
                self.lexer.get_chars(2)
                expression = self.try_parse_expression()
                base = BinaryOperatorExpression(
                    base,
                    BinaryOperatorExpression.BinaryOperation.SMALLER_EQUAL,
                    expression,
                )

            elif self.lexer.inspect_chars(1) == "<":
                self.lexer.get_chars(1)
                expression = self.try_parse_expression()
                base = BinaryOperatorExpression(
                    base, BinaryOperatorExpression.BinaryOperation.SMALLER, expression
                )

            else:
                break

        self.lexer.try_parse_whitespaces()

        if not generators_require_brackets and self.lexer.inspect_chars(2) == "for":
            self.lexer.save_state()
            self.lexer.get_chars(3)
            self.lexer.try_parse_whitespaces()

            target = self.try_parse_assignment_target(
                tuple_assignment_requires_brackets=False
            )

            if target is None:
                self.lexer.rollback_state()
                return base

            self.lexer.try_parse_whitespaces()

            if self.lexer.get_chars(2) != "in":
                self.lexer.rollback_state()
                return base

            self.lexer.try_parse_whitespaces()
            iterable = self.try_parse_expression()

            if iterable is None:
                self.lexer.rollback_state()
                return base

            if_node = None
            if self.lexer.inspect_chars(2) == "if":
                self.lexer.get_chars(2)

                if_node = self.try_parse_expression()

                if if_node is None:
                    self.lexer.rollback_state()
                    return base

            self.lexer.discard_save_state()
            return GeneratorExpression(base, target, iterable, if_node)

        return base

    def try_pase_expression_list_like(self):
        self.lexer.get_chars(1)
        elements = []

        self.lexer.try_parse_whitespaces()

        if self.lexer.inspect_chars(1) == "]":
            self.lexer.get_chars(1)
            return ListConstructor([])

        expression = self.try_parse_expression()
        self.lexer.try_parse_whitespaces()

        if expression is None:
            raise SyntaxError

        elements.append(expression)

        if self.lexer.inspect_chars(1) == ",":
            self.lexer.get_chars(1)

            while self.lexer.inspect_chars(1) != "]":
                self.lexer.try_parse_whitespaces(include_newline=True)
                expression = self.try_parse_expression()
                self.lexer.try_parse_whitespaces()

                if expression is None:
                    raise SyntaxError

                elements.append(expression)

                if self.lexer.inspect_chars(1) != ",":
                    break

                self.lexer.get_chars(1)

        elif self.lexer.inspect_chars(3) == "for":
            self.lexer.save_state()
            self.lexer.get_chars(3)
            self.lexer.try_parse_whitespaces()

            target = self.try_parse_assignment_target(
                tuple_assignment_requires_brackets=False
            )

            if target is None:
                self.lexer.rollback_state()
                return

            self.lexer.try_parse_whitespaces()

            if self.lexer.get_chars(2) != "in":
                self.lexer.rollback_state()
                return

            self.lexer.try_parse_whitespaces()
            iterable = self.try_parse_expression()

            if iterable is None:
                self.lexer.rollback_state()
                return

            self.lexer.try_parse_whitespaces()

            if_node = None
            if self.lexer.inspect_chars(2) == "if":
                self.lexer.get_chars(2)

                if_node = self.try_parse_expression()

                if if_node is None:
                    self.lexer.rollback_state()
                    return

                self.lexer.try_parse_whitespaces()

            if self.lexer.get_chars(1) != "]":
                raise SyntaxError("expected ']'")

            self.lexer.discard_save_state()
            return ListComprehension(elements[0], target, iterable, if_node)

        self.lexer.try_parse_whitespaces(include_newline=True)

        if self.lexer.get_chars(1) != "]":
            raise SyntaxError

        return ListConstructor(elements)

    def try_pase_expression_dict_like(self):
        self.lexer.save_state()
        self.lexer.get_chars(1)
        elements = []

        self.lexer.try_parse_whitespaces()

        while self.lexer.inspect_chars(1) != "}":
            self.lexer.try_parse_whitespaces(include_newline=True)
            key = self.try_parse_expression()
            self.lexer.try_parse_whitespaces()

            if key is None:
                raise SyntaxError

            if self.lexer.inspect_chars(1) != ":":
                self.lexer.rollback_state()
                return

            self.lexer.get_chars(1)

            self.lexer.try_parse_whitespaces()
            value = self.try_parse_expression()
            self.lexer.try_parse_whitespaces()

            elements.append((key, value))

            if self.lexer.inspect_chars(1) != ",":
                break

            self.lexer.get_chars(1)

        self.lexer.try_parse_whitespaces(include_newline=True)

        if self.lexer.get_chars(1) != "}":
            raise SyntaxError

        self.lexer.discard_save_state()

        return DictConstructor(elements)

    def try_parse_expression_tuple_like(self, inner):
        self.lexer.get_chars(1)
        self.lexer.discard_save_state()

        elements = [inner]

        while True:
            self.lexer.try_parse_whitespaces()
            expression = self.try_parse_expression()
            self.lexer.try_parse_whitespaces()

            if expression is None:
                break

            elements.append(expression)

            if self.lexer.inspect_chars(1) != ",":
                break

            self.lexer.get_chars(1)

        if self.lexer.get_chars(1) != ")":
            raise SyntaxError

        return TupleConstructor(elements)

    def parse_function_call(
        self, base: AbstractASTNode, opening_bracket: Lexer.Token
    ) -> CallExpression:
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
                if not (
                    closing_bracket := self.lexer.try_parse_closing_round_bracket()
                ):
                    print(args)
                    raise SyntaxError(
                        f"expected ')', got '{self.lexer.inspect_chars(4)}'"
                    )

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
            if keyword and keyword.startswith("return"):
                if keyword[-1] == "\n":
                    self.lexer.give_back("\n")
                    return ReturnStatement(ConstantAccessExpression(None))

                white = self.lexer.try_parse_whitespaces()

                if self.lexer.inspect_chars(1) == "\n":
                    return ReturnStatement(ConstantAccessExpression(None))

                self.lexer.give_back(white)

            self.lexer.give_back(keyword)

            return

        self.lexer.save_state()
        return_value = self.try_parse_expression()

        if return_value is None:
            return_value = ConstantAccessExpression(None)
            self.lexer.rollback_state()
        else:
            self.lexer.discard_save_state()

        return ReturnStatement(return_value)

    def try_parse_yield_statement(self) -> YieldStatement | None:
        keyword = self.lexer.get_chars(len("yield "))

        if keyword != "yield ":
            self.lexer.give_back(keyword)
            return

        is_yield_from = False
        if self.lexer.inspect_chars(len("from ")) == "from ":
            is_yield_from = True
            self.lexer.get_chars(len("from "))

        yield_expression = self.try_parse_expression()

        if yield_expression is None:
            raise SyntaxError

        return YieldStatement(yield_expression, is_yield_from=is_yield_from)

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

    def parse_multiline_quoted_string(
        self, quote_type: str
    ) -> ConstantAccessExpression:
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

    def try_parse_integer_or_float(self) -> ConstantAccessExpression | None:
        text = self.lexer.get_chars(1)

        while True:
            c = self.lexer.get_chars(1)

            if c and c.isdigit():
                text += c
            elif c == "." and "." not in text:
                text += c
            else:
                break

        if text == "-":
            self.lexer.give_back("  ")
            return

        self.lexer.give_back(c)
        return ConstantAccessExpression(int(text) if "." not in text else float(text))

    def try_parse_comment(self) -> PyCommentNode | None:
        if comment_start := self.lexer.try_parse_hashtag():
            return PyCommentNode(comment_start, self.lexer.parse_until_newline())

    def try_parse_assignment(self) -> AssignmentExpression | InplaceOperator | None:
        self.lexer.save_state()
        assigned_variables = [
            self.try_parse_assignment_target(tuple_assignment_requires_brackets=False)
        ]

        if assigned_variables[0] is None:
            self.lexer.rollback_state()
            return

        self.lexer.try_parse_whitespaces()

        eq_sign = self.lexer.try_parse_equal_sign()

        if eq_sign is None:
            prefix = self.lexer.inspect_chars(2)

            operator: InplaceOperator.InplaceOperation | None = None
            count = 2

            if prefix == "+=":
                operator = InplaceOperator.InplaceOperation.PLUS
            elif prefix == "-=":
                operator = InplaceOperator.InplaceOperation.MINUS
            elif prefix == "*=":
                operator = InplaceOperator.InplaceOperation.MULTIPLY
            elif self.lexer.inspect_chars(3) == "**=":
                operator = InplaceOperator.InplaceOperation.POW
                count = 3
            elif prefix == "/=":
                operator = InplaceOperator.InplaceOperation.TRUE_DIV
            elif self.lexer.inspect_chars(3) == "//=":
                operator = InplaceOperator.InplaceOperation.FLOOR_DIV
                count = 3
            elif prefix == "%=":
                operator = InplaceOperator.InplaceOperation.MODULO
            elif prefix == "@=":
                operator = InplaceOperator.InplaceOperation.MATRIX_MULTIPLY
            elif prefix == "|=":
                operator = InplaceOperator.InplaceOperation.BIN_OR
            elif prefix == "&=":
                operator = InplaceOperator.InplaceOperation.BIN_AND
            elif prefix == "^=":
                operator = InplaceOperator.InplaceOperation.BIN_XOR
            elif self.lexer.inspect_chars(3) == "<<=":
                operator = InplaceOperator.InplaceOperation.SHL
                count = 3
            elif self.lexer.inspect_chars(3) == ">>=":
                operator = InplaceOperator.InplaceOperation.SHR
                count = 3

            if operator:
                self.lexer.get_chars(count)
                self.lexer.try_parse_whitespaces()
                rhs = self.try_parse_expression()

                if rhs:
                    return InplaceOperator(
                        assigned_variables[0],
                        operator,
                        rhs,
                    )

            self.lexer.rollback_state()
            return

        self.lexer.discard_save_state()

        while True:
            self.lexer.save_state()
            self.lexer.try_parse_whitespaces()
            expression = self.try_parse_assignment_target(
                tuple_assignment_requires_brackets=False
            )
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
            raise SyntaxError(
                "expected '(' after <function name> or <generic parameters>"
            )

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

        is_generator = False

        def feedback():
            nonlocal is_generator
            is_generator = True

        if self.lexer.inspect_chars(1) != "\n":
            body = [self.parse_line(include_comment=False, mention_on_yield=feedback)]
        else:
            self.indent_level += 1
            body = self.parse(stop_on_indention_exit=True, mention_on_yield=feedback)

            if len(body) == 0:
                raise SyntaxError("expected <body>")

            self.indent_level -= 1

        self.is_in_function = prev_in_function

        return FunctionDefinitionNode(
            function_name,
            generic_names,
            parameters,
            body,
            is_generator=is_generator,
        )

    def try_parse_generic_parameters(
        self, duplicate_name_check
    ) -> typing.List[Lexer.Token]:
        generic_names = []

        while (name := self.lexer.try_parse_identifier()) and name is not None:
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

    def try_parse_function_parameter(
        self,
    ) -> FunctionDefinitionNode.FunctionDefinitionParameter | None:
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

        cls = ClassDefinitionNode(
            class_name,
            generics,
            parents,
            body,
        )

        for node in body:
            if isinstance(node, FunctionDefinitionNode):
                cls.function_table[node.name.text] = node

        return cls

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
            self.is_in_singleline_expression = True
            body = [self.parse_line(include_comment=False)]
            self.is_in_singleline_expression = False
        else:
            self.indent_level += 1
            body = self.parse(stop_on_indention_exit=True)

            if len(body) == 0:
                raise SyntaxError("expected <body>")

            self.indent_level -= 1

        self.lexer.save_state()
        else_branch = []

        if self.try_get_indent() is None:
            self.lexer.rollback_state()

        elif self.lexer.inspect_chars(len("else:")) == "else:":
            self.lexer.discard_save_state()
            self.lexer.get_chars(len("else:"))

            self.indent_level += 1
            else_branch = self.parse(stop_on_indention_exit=True)

            if len(else_branch) == 0:
                raise SyntaxError("expected <body> after 'else'")

            self.indent_level -= 1

        else:
            self.lexer.rollback_state()

        return WhileStatement(
            condition,
            body,
            else_node=else_branch,
        )

    def try_parse_for_statement(self) -> ForLoopStatement | None:
        # for <target> in <iterable>:
        for_token = self.lexer.get_chars(len("for "))

        if for_token != "for ":
            self.lexer.give_back(for_token)
            return

        self.lexer.try_parse_whitespaces()

        target = self.try_parse_assignment_target(
            tuple_assignment_requires_brackets=False
        )

        if target is None:
            raise SyntaxError("expected <target> after 'for'")

        self.lexer.try_parse_whitespaces()

        if self.lexer.get_chars(3) != "in ":
            raise SyntaxError("expected 'in' after <target>")

        self.lexer.try_parse_whitespaces()

        iterator = self.try_parse_expression()

        if iterator is None:
            raise SyntaxError("expected <expression> after 'while'")

        if self.lexer.get_chars(1) != ":":
            raise SyntaxError("expected ':' after <iterator>")

        self.lexer.try_parse_whitespaces()

        if self.lexer.inspect_chars(1) != "\n":
            self.is_in_singleline_expression = True
            body = [self.parse_line(include_comment=False)]
            self.is_in_singleline_expression = False
        else:
            self.indent_level += 1
            body = self.parse(stop_on_indention_exit=True)

            if len(body) == 0:
                raise SyntaxError("expected <body>")

            self.indent_level -= 1

        self.lexer.save_state()
        else_branch = []

        if self.try_get_indent() is None:
            self.lexer.rollback_state()

        elif self.lexer.inspect_chars(len("else:")) == "else:":
            self.lexer.discard_save_state()
            self.lexer.get_chars(len("else:"))

            self.indent_level += 1
            else_branch = self.parse(stop_on_indention_exit=True)

            if len(else_branch) == 0:
                raise SyntaxError("expected <body> after 'else'")

            self.indent_level -= 1

        else:
            self.lexer.rollback_state()

        return ForLoopStatement(
            target,
            iterator,
            body,
            else_branch,
        )

    def try_parse_if_statement(self) -> IfStatement | None:
        if_token = self.lexer.get_chars(len("if "))

        if if_token != "if ":
            self.lexer.give_back(if_token)
            return

        self.lexer.try_parse_whitespaces()

        main_condition = self.try_parse_expression()

        if main_condition is None:
            raise SyntaxError("expected <expression> after 'if'")

        if self.lexer.get_chars(1) != ":":
            raise SyntaxError("expected ':' after <condition> in 'if'")

        self.lexer.try_parse_whitespaces()

        if self.lexer.inspect_chars(1) != "\n":
            self.is_in_singleline_expression = True
            main_body = [self.parse_line(include_comment=False)]
            self.is_in_singleline_expression = False

            if main_body[0] == None:
                raise SyntaxError("expected <expression>")

        else:
            self.indent_level += 1
            main_body = self.parse(stop_on_indention_exit=True)

            if len(main_body) == 0:
                raise SyntaxError("expected <body>")

            self.indent_level -= 1

        self.lexer.try_parse_whitespaces()

        elif_nodes = []

        while self.lexer.inspect_chars(len("elif ")) == "elif ":
            self.lexer.get_chars(len("elif"))
            self.lexer.try_parse_whitespaces()

            condition = self.try_parse_expression()

            if condition is None:
                raise SyntaxError("expected <expression> after 'if'")

            if self.lexer.get_chars(1) != ":":
                raise SyntaxError("expected ':' after <condition> in 'if'")

            self.lexer.try_parse_whitespaces()

            if self.lexer.inspect_chars(1) != "\n":
                self.is_in_singleline_expression = True
                body = [self.parse_line(include_comment=False)]
                self.is_in_singleline_expression = False
                if self.lexer.inspect_chars(1) == "\n":
                    self.lexer.get_chars(1)
            else:
                self.indent_level += 1
                body = self.parse(stop_on_indention_exit=True)

                if len(body) == 0:
                    raise SyntaxError("expected <body>")

                self.indent_level -= 1

            self.lexer.try_parse_whitespaces()

            elif_nodes.append((condition, body))

        else_body = None

        if self.lexer.inspect_chars(len("else:")) == "else:":
            self.lexer.get_chars(len("else:"))
            self.lexer.try_parse_whitespaces()

            if self.lexer.inspect_chars(1) != "\n":
                self.is_in_singleline_expression = True
                else_body = [self.parse_line(include_comment=False)]
                self.is_in_singleline_expression = False

                if else_body[0] is None:
                    raise SyntaxError("expected <expression> after 'else'")

            else:
                self.indent_level += 1
                else_body = self.parse(stop_on_indention_exit=True)

                if len(else_body) == 0:
                    raise SyntaxError("expected <body>")

                self.indent_level -= 1

            self.lexer.try_parse_whitespaces()

        return IfStatement(main_condition, main_body, elif_nodes, else_body)

    def try_parse_pass_statement(self) -> PassStatement | None:
        pass_token = self.lexer.get_chars(len("pass "))

        if (
            pass_token != "pass "
            and pass_token != "pass\n"
            and not (
                pass_token is None
                and (pass_token := self.lexer.get_chars(len("pass")) == "pass")
            )
        ):
            self.lexer.give_back(pass_token)
            return

        return PassStatement()

    def try_parse_assert_statement(self) -> AssertStatement | None:
        assert_token = self.lexer.get_chars(len("assert "))

        if assert_token != "assert ":
            self.lexer.give_back(assert_token)
            return

        expression = self.try_parse_expression()
        if expression is None:
            raise SyntaxError

        self.lexer.try_parse_whitespaces()
        message = None
        if self.lexer.inspect_chars(1) == ",":
            self.lexer.get_chars(1)
            message = self.try_parse_expression()

            if message is None:
                raise SyntaxError

        return AssertStatement(expression, message)

    def try_parse_import_statement(self) -> ImportStatement | None:
        import_token = self.lexer.get_chars(len("import "))

        if import_token != "import ":
            self.lexer.give_back(import_token)
            return

        self.lexer.try_parse_whitespaces()
        name = [identifier := self.lexer.try_parse_token(TokenType.IDENTIFIER)]
        if identifier is None:
            raise SyntaxError("expected <identifier> after 'import'")
        self.lexer.try_parse_whitespaces()

        while self.lexer.inspect_chars(1) == ".":
            self.lexer.get_chars(1)
            name.append(identifier := self.lexer.try_parse_token(TokenType.IDENTIFIER))
            if identifier is None:
                raise SyntaxError("expected <identifier> after '.'")
            self.lexer.try_parse_whitespaces()

        if self.lexer.inspect_chars(3) == "as ":
            self.lexer.get_chars(2)
            self.lexer.try_parse_whitespaces()
            as_name = self.lexer.try_parse_token(TokenType.IDENTIFIER)
            if as_name is None:
                raise SyntaxError("expected <identifier> after 'as'")
        else:
            as_name = None

        return ImportStatement(
            ".".join(e.text for e in name),
            as_name.text if as_name else None,
        )

    def get_module_content(self, ast_nodes: typing.List[AbstractASTNode]) -> dict:
        result = {}

        for node in ast_nodes:
            if isinstance(node, ClassDefinitionNode):
                result[node.name.text] = GlobalCNameAccessExpression(
                    "PY_TYPE_" + node.normal_name
                )
            elif isinstance(node, FunctionDefinitionNode):
                result[node.name.text] = GlobalCNameAccessExpression(node.normal_name)

        return result
