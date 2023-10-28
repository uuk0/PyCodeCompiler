from __future__ import annotations

import inspect
import types
import typing


if typing.TYPE_CHECKING:
    from pycompiler.parser.AbstractSyntaxTreeNode import AbstractSyntaxTreeExpressionNode
    
    
def typeof(obj: object) -> type:
    t = type(obj)

    if t == slice:
        return SliceWrapper

    return t


class SliceWrapperMeta(type):
    def __subclasscheck__(self, subclass):
        return super().__subclasscheck__(subclass) or subclass == slice


class SliceWrapper[A, B, C](metaclass=SliceWrapperMeta):
    """
    Wrapper around the 'slice' class, where the attribute cannot be generics, so
    think of this like a slice
    """

    @classmethod
    def __class_getitem__(cls, item: tuple | type) -> types.GenericAlias:
        if isinstance(item, tuple):
            if len(item) == 0:
                return types.GenericAlias(cls, (None, None, None))
            elif len(item) == 1:
                return types.GenericAlias(cls, (item[0], None, None))
            elif len(item) == 2:
                return types.GenericAlias(cls, (item[0], item[1], None))
            elif len(item) == 3:
                return types.GenericAlias(cls, item)
            else:
                raise ValueError(f"expected 0 to 3 generic parameters, got {len(item)}")

        return types.GenericAlias(cls, (item, None, None))

    def __init__(self, start: A = None, stop: B = None, step: C = None):
        self.start = start
        self.stop = stop
        self.step = step


class TypeInformationHolder:
    class TypeDescriptor:
        def __init__(
            self,
            attribute_types: typing.Dict[str, type | types.GenericAlias | TypeInformationHolder.GenericReference] = None,
            subscription_type: type | types.GenericAlias | TypeInformationHolder.GenericReference | typing.Callable[[AbstractSyntaxTreeExpressionNode | None], type | types.GenericAlias | TypeInformationHolder.GenericReference] = typing.Any,
            call_result_type: type | types.GenericAlias | TypeInformationHolder.GenericReference | typing.Callable[[typing.List[AbstractSyntaxTreeExpressionNode] | None], type | types.GenericAlias | TypeInformationHolder.GenericReference] = typing.Any,
        ):
            self.attribute_types = attribute_types or {}
            self.subscription_type = subscription_type
            self.call_result_type = call_result_type

        def resolve_generic_reference(self, t: type | types.GenericAlias | TypeInformationHolder.GenericReference, context: TypeInformationHolder) -> type | types.GenericAlias:
            if isinstance(t, type):
                return t

            elif isinstance(t, types.GenericAlias):
                return types.GenericAlias(
                    self.resolve_generic_reference(t.__origin__, context),
                    [
                        self.resolve_generic_reference(arg, context)
                        for arg in t.__args__
                    ],
                )

            elif isinstance(t, TypeInformationHolder.GenericReference):
                return context.get_generic_value(t.index)

            raise ValueError("invalid type")

        def add_attribute_type(self, name: str, t: type | types.GenericAlias | TypeInformationHolder.GenericReference) -> typing.Self:
            self.attribute_types[name] = t
            return self

        def add_subscription_type(self, t: type | types.GenericAlias | TypeInformationHolder.GenericReference | typing.Callable[[AbstractSyntaxTreeExpressionNode | None], type | types.GenericAlias | TypeInformationHolder.GenericReference]) -> typing.Self:
            self.subscription_type = t
            return self

        def add_call_result_type(self, t: type | types.GenericAlias | TypeInformationHolder.GenericReference | typing.Callable[[typing.List[AbstractSyntaxTreeExpressionNode] | None], type | types.GenericAlias | TypeInformationHolder.GenericReference]) -> typing.Self:
            self.call_result_type = t
            return self

    class GenericReference:
        def __init__(self, index: int):
            self.index = index

    TYPE_INFORMATION_DATA: typing.Dict[type, TypeDescriptor] = {
        typing.Any: TypeDescriptor(),
        SliceWrapper: TypeDescriptor()
        .add_attribute_type("start", GenericReference(0))
        .add_attribute_type("stop", GenericReference(1))
        .add_attribute_type("step", GenericReference(2)),
        list: TypeDescriptor()
        .add_subscription_type(GenericReference(0)),  # todo: slices -> list[T]
        tuple: TypeDescriptor()
        .add_subscription_type(GenericReference(0)),  # todo: slices -> tuple[T]
        dict: TypeDescriptor()
        .add_subscription_type(GenericReference(1))
        .add_attribute_type("get", typing.Callable[[GenericReference(0)], GenericReference(1)])
        .add_attribute_type("set", typing.Callable[[GenericReference(0), GenericReference(1)], None])
        .add_attribute_type("setdefault", typing.Callable[[GenericReference(0), GenericReference(1)], GenericReference(1)]),
        str: TypeDescriptor()
        .add_subscription_type(str),
    }

    def __init__(self, base_type: type | types.GenericAlias):
        self.base_type = base_type
        self.descriptor = self.TYPE_INFORMATION_DATA.get(base_type, self.TYPE_INFORMATION_DATA.get(typing.Any))

    def get_generic_value(self, index: int) -> type | types.GenericAlias:
        if isinstance(self.base_type, type):
            # Is the underlying a generic-able?
            if issubclass(self.base_type, typing.Generic):
                return typing.Any  # than we have not filled generic values, so insert typing.Any

            raise ValueError("type is no generic reference!")

        # Is the index in bounds
        if index < 0 or (isinstance(self.base_type, types.GenericAlias) and len(self.base_type.__args__) <= index):
            raise ValueError("invalid index; cannot access")

        return self.base_type.__args__[index]

    def get_attribute_type(self, name: str) -> type | types.GenericAlias:
        return self.descriptor.resolve_generic_reference(self.descriptor.attribute_types.get(name, typing.Any), self)

    def get_subscription_type(self, argument: AbstractSyntaxTreeExpressionNode = None) -> type | types.GenericAlias:
        return self.descriptor.resolve_generic_reference(self.descriptor.subscription_type if isinstance(self.descriptor.subscription_type, (type, types.GenericAlias)) else self.descriptor.subscription_type(argument), self)

    def get_call_result_type(self, parameters: typing.List[AbstractSyntaxTreeExpressionNode] = None) -> type | types.GenericAlias:
        return self.descriptor.resolve_generic_reference(self.descriptor.call_result_type if isinstance(self.descriptor.call_result_type, (type, types.GenericAlias)) else self.descriptor.call_result_type(parameters), self)


def get_type_info(t: type | types.GenericAlias) -> TypeInformationHolder:
    if not hasattr(t, "_TYPE_INFO_CONTAINER"):
        t._TYPE_INFO_CONTAINER = TypeInformationHolder(t)

    return t._TYPE_INFO_CONTAINER


def check_signature_compatible(
    expected: inspect.Signature, possible: inspect.Signature
) -> bool:
    provided_keywords = set()
    used_keywords = set()
    arg_types: dict[str, type] = {}
    provided_arg_count = 0

    for arg in possible.parameters.values():
        if arg.kind == inspect.Parameter.POSITIONAL_OR_KEYWORD:
            # is it a non-keyword?
            if arg.default == inspect._empty:
                if provided_arg_count != -1:
                    provided_arg_count += 1
            else:
                if provided_keywords:
                    provided_keywords.add(arg.name)

                if arg.annotation != inspect.Parameter.empty:
                    arg_types[arg.name] = arg.annotation

        elif arg.kind == inspect.Parameter.VAR_KEYWORD:
            provided_keywords = None

        elif arg.kind == inspect.Parameter.VAR_POSITIONAL:
            provided_arg_count = -1

    for i, arg in enumerate(expected.parameters.values()):
        arg: inspect.Parameter

        if arg.kind == inspect.Parameter.POSITIONAL_OR_KEYWORD:
            # is it a non-keyword?
            if arg.default == inspect._empty:
                if 0 <= provided_arg_count:
                    if provided_arg_count <= i:
                        return False

                    earg = list(expected.parameters.values())[i]
                    parg = list(possible.parameters.values())[i]

                    return (
                        earg.annotation == inspect.Parameter.empty
                        or parg.annotation == inspect.Parameter.empty
                        or check_type_matching(earg.annotation, parg.annotation)
                    )

            else:
                if (
                    arg.name in arg_types
                    and arg.annotation != inspect.Parameter.empty
                    and not check_type_matching(arg.annotation, arg_types[arg.name])
                ):
                    return False

                used_keywords.add(arg.name)

    if provided_keywords and provided_keywords - used_keywords:
        return False

    return True


def check_type_matching(
    expected: type | types.UnionType, possible: type | types.UnionType
) -> bool:
    if expected == typing.Any:
        return True

    if isinstance(expected, types.UnionType):
        if not isinstance(possible, types.UnionType):
            return any(check_type_matching(t, possible) for t in expected.__args__)

        pending = list(possible.__args__)

        for t in expected.__args__:
            for p in pending:
                if check_type_matching(t, p):
                    pending.remove(p)
                    break

        return not pending

    if isinstance(possible, types.UnionType):
        return len(possible.__args__) == 1 and check_type_matching(
            expected, possible.__args__[0]
        )

    if not isinstance(expected, types.GenericAlias):
        if isinstance(possible, types.GenericAlias):
            return issubclass(possible.__origin__, expected)

        return issubclass(possible, expected)

    if not isinstance(possible, types.GenericAlias):
        return False

    etype = expected.__origin__
    ptype = possible.__origin__

    if not issubclass(ptype, etype):
        return False

    if len(possible.__args__) != len(expected.__args__):
        return False

    return all(
        check_type_matching(ex, po)
        for ex, po in zip(expected.__args__, possible.__args__)
    )


def merge_type_declarations(a: type | types.GenericAlias, b: type | types.GenericAlias):
    if isinstance(a, types.UnionType):
        if isinstance(b, types.UnionType):
            entries = list(a.__args__)
            for e in b.__args__:
                if e not in entries:
                    entries.append(e)
            return typing.Union[entries]

        return a | b if b not in a.__args__ else a

    elif isinstance(b, types.UnionType):
        return a | b if a not in b.__args__ else b

    return a | b if a != b else a
