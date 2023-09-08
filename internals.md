
# Parsing

We use a custom parser, which parses expressions right-recursive.
It uses a special rewriter class (`BinaryOperatorPriorityRewriter`)
for ordering the AST nodes in the correct way.


# Modules


Each module is generating their own .c file and .h file.
The file naming scheme is 'pymodule_[module name replacing '.' with three '_'].c' / '[...].h'
Each module exposes an global variable called 'PY_MODULE_INSTANCE_[the above normalized name]',
which holds the associated module object, and a method 'void PY_MODULE_[the above normalized name]_init(void)'
for initialising that module.

The init function is invoked in places where the 'import' statement would generating other code into.
As such, the init method might be invoked multiple times, and should ignore all but the first call.

During optimisation, the module reference will most likely be inlined, and later hard-referenced
(so static function references are resolved).

TODO: prefix all generated functions / constants in a module with the normalised name!


# Runtime evaluation vs. Static Evaluation

The default model of python is "creation on import" for modules and everything which is not in a function,
where each function body is only evaluated on each execution.

This brings the problem that c does not allow inlined functions, so we need to container references to
non-static functions.

This requires some logic when trying to access some global symbol without calling it, as it
needs to be boxed, and than later unboxed again.

## Classes and dynamic attributes

Users should use ideally the ```__slots__``` attribute to declare what attributes they will use,
otherwise we need to keep a special table for dynamic attributes, holding besides the value also
the type information and name of the attribute (-> HashMap implementation!).

Classes are getting transformed where possible to structs.
Inner classes get a generic struct and are container-ed so everybody knows
what they are dealing with.

If a dynamic class uses static dimensions (when e.g. using only in the attribute values / function
declarations), they might be partially static treated, or in some cases,
a box around a static variant of that class might be used (which hold some config values).

## Generators

Generators will use a special wrapper function,
handling entries point into the function via a jump table;
at each yield, a return from a function section will happen.
From each section, one may reach any other section.

Function variables are saved in the wrapper function by allocating
a corresponding section of memory, used to hold all information about the generator.

## Exceptions

Currently not supported; Functions will crash with an assertion error

