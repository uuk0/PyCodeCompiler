"""
File holding the options the system has
"""

"""
Toggles if to emit code related to generics at runtime; disabling this will disable
the export of generic references outside the compiler, so no access can happen when running the code.

This does NOT affect type references, as these are mostly used at compile type only

todo: implement
"""
ENABLE_RUNTIME_GENERIC_VALUES = True

"""
This enables the return value of type(...) to use types.GenericAlias when the type has specified generic parameters.
WARNING: this is non-cpython behaviour, and could lead to issues with libraries expecting type(...) to return
a <type> object instead of a types.GenericAlias

This also enables isinstance() checks with types.GenericAlias as type parameter.

todo: implement
"""
ENABLE_GENERIC_ANNOTATIONS_ON_TYPE_CALL = False

"""
When enabled, will allow dynamic access of attributes on objects.
Disabling this will lead to enforcing hard-compiled code, and exactly-known types.

WARNING: this WILL lead to big issues with code written in a way that requires dynamic-typing

todo: implement
"""
ENABLE_RUNTIME_LOOKUP_TABLES = True

"""
When enabled, python builtins objects may be overridden in local scopes.
Disabling this will enforce python code which lead to faster code, by allowing the compiler
to resolve these names fully ahead of time.

WARNING: disabling this might lead to issues in code relying on this behaviour
"""
ENABLE_BUILTIN_SHADOWING = True

"""
This toggles if globals() is allowed or not.

When such function is used in code, it requires costly code in the region, as
globals() needs to be accounted for.

WARNING: disabling this will render code using globals() useless!

todo: implement
todo: optimise ahead-of-time [...] access on the object to use the correct global instead
"""
ENABLE_GLOBALS_FUNCTION = True

"""
Similar to ENABLE_GLOBAL_FUNCTION, but for locals()
Note that locals() is even more costly than globals().

todo: implement
todo: optimise ahead-of-time [...] access on the object to use the correct local instead
"""
ENABLE_LOCALS_FUNCTION = True

"""
This option toggles if stack frames are arrival at runtime.

WARNING: this feature is highly costly for the whole code, not only sections affected by the stack,
and will lead to a lot more memory be used. Use with caution.

WARNING: this feature is REQUIRED when interacting in any way or form with the stack directly

This is a more complex feature than correct exception stacks, as it also requires local references and similar
to be moved permanently onto the stack.

todo: implement
"""
ENABLE_STACK_INFORMATION = False

"""
This option toggles if type information should be seen strict (like Java types) or only 'hints'
(can be broken without consequence).

Disabling this will lead to high performance penalties, as this disables a lot of code optimisation.

WARNING: Disabling this and ENABLE_RUNTIME_LOOKUP_TABLES will lead to major issues, as most of the
lookup is no longer possible!
"""
ENABLE_STRICT_TYPE_ANNOTATIONS = True

"""
Enabling this will add guards for the correct annotated type.
This has a performance penalty, but is useful for debugging.

WARNING: only affective when ENABLE_STRICT_TYPE_ANNOTATIONS is enabled, as otherwise this option is never considered.
"""
ENABLE_DEBUG_TYPE_CHECKS_FOR_ANNOTATIONS = False
