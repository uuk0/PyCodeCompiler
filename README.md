
# PyCodeCompiler

PyCodeCompiler is a tool for compiling python-like source code into
an executable .exe file.

It allows the programmer to add harder type guards on variables
than normal python, enforcing certain types.

In contrast to normal python code, type annotations are hard types, not
type hints.

Violating such types might result in a compile-time or runtime error.

Not annotating a variable with a type might result in a dynamic
container holding the value.

## Variable Types

The compiler might decide to assign a certain static type
to a variable in a certain program region.

E.g. when you have the following code:
```python
a = 10
print(a)

a = "test"
print(a)
```

The compiler can create two internal variables not sharing the same name,
both having a strict type in this scope.

## Dynamic Types in Objects

A variable might hold a certain type, e.g. int, float, long, ...,
or a holding container of such type.

The compiler will create a function handling the code with only holding containers,
and might decide to create functions with primitive arguments and return value.

## Generics

We support (only) the python >= 3.12 generic syntax, and count
it like other type-hints as enforced.

Type hints in python < 3.12 style via typing.TypeVar are ignored in type checking.

Feature: the generic name is exported as a name in all children-scopes
so you can do something like this:
```python
def test[X](arg) -> X:
    return X(arg)
```

You can also specify the types for generic parameters for functions explicit like:
```python
def test[X](arg) -> X:
    return X(arg)
    
test[int](10)
```

At runtime, if the function could not be resolved statically, the
'[]' operator will return an optional boxed variant of itself for that type set

## Goals

Make the compiler compile itself

Make the compiled code run not much slower than cpython's implementation

Make the compiled test suite from python not fail in the major test cases
(implementation internals are expected to fail)

## Supported Syntax

- constants and variables
- variable assignments, including multiple lhs and complex lhs objects, like e.g. `target[0] = x.y = 10`
- the subscription operator (`[]`), attribute access (`.`)
- function calls (`()`)
- function declarations (python 3.12 syntax with generics via `[]` after the function name)
  - TODO: yield
- class declarations (python 3.12 syntax with generics via `[]` after the function name)
- while loops
  - TODO: continue, break
- TODO: pass, if-elif-else, for, comparisons, arithmetic
