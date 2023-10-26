from __future__ import annotations

import inspect
import types
import typing


def check_signature_compatible(
    expected: inspect.Signature, possible: inspect.Signature
) -> bool:
    provided_keywords = set()
    used_keywords = set()
    arg_types: typing.Dict[str, type] = {}
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
