
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

Currently, the compiler forbids in some cases reassigning with another data type.

## Dynamic Types in Objects

A variable might hold a certain type, e.g. int, float, long, ...,
or a holding container of such type.

The compiler will create a function handling the code with only holding containers,
and might decide to create functions with primitive arguments and return value.

Dynamic attribute names are by default disabled for general use.
The only case when they are required are in modules, as they are complex objects.

In the future, there will be an option to generally enable dynamic attribute names.

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
- function calls (`()`) including keyword, '*' and '**'
- function declarations (python 3.12 syntax with generics via `[]` after the function name), including generators
  (WIP)
  - no inner functions (TODO: make them work with a wrapper)
- class declarations (python 3.12 syntax with generics via `[]` after the class name)
  - instantiation (only for static-know classes currently)
  - no inner classes (TODO: make them work, PyClassContainer supports it already!)
  - TODO: class references, call mechanism should be able to construct class dynamically
- while loops, including continue, break and else
- list, tuple and dict explict construction (using `(a, b)`,`[a, b]` and `{a: b}`)
  - TODO: comprehensions
- tuple-like deconstruction
  - TODO: allow generator destruction (requires some transforms before)
- `for`(each)-loops
  - using the `__iter__` function which can be defined on objects
- if-elif-else and ternary expressions
- TODO: compare-chains resolving
- TODO: dynamic imports (`__import__`, `importlib`)

## Supported Builtin Modules

### typing

The `TYPE_CHECKING` variable is set to forced `False`

### unittest

Implementing `main` and basic `TestCase`

### itertools

Implemented `chain`

## Command Line Interface

TODO

Usage:
```
pycompiler <source files...> [-o <output file>] [--enable-dynamic-attributes] [--disable-module-generation] [--disable-generators]
[--add-to-path=<file or folder>]
```
