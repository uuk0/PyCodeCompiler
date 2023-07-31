

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
the type information and name of the attribute.

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

