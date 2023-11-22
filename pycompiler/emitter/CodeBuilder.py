from __future__ import annotations

import typing
from abc import ABC


INVALID_CHARS_IN_HINT = " \t\n\r+-*~'#.,:;()&%$§\"!{[]}\\€@"


class CodeBuilder:
    """
    CodeBuilder - Building Tools for creating c-code

    The basic element are 'Source'-objects, which are created by certain 'push_XX' calls
    on the builder object.
    To evaluate these expressions, use push_evaluate_value(<source>).

    Source-objects are required for certain expressions, like operators requiring the operands to be 'Source' objects.

    With 'source' objects, you can also create control structures, like loops.

    Variable Assignments also require a 'Source' object.

    The Builder decides automatically (when not specified) what variables should be stored in temporary variables,
    and will optimise cases where it is not needed.
    """

    class Source:
        def __init__(
            self,
            real_source: CodeBuilder.Source = None,
            enforce_local_storage=False,
            name_hint: str = None,
        ):
            self.real_value: CodeBuilder.Source = real_source
            self.enforce_local_storage = enforce_local_storage
            self.name_hint = name_hint
            self._access_name: str | None = None
            self.usage_count = 0

        def get_access_text(
            self, builder: CodeBuilder, include_base_assignment=True
        ) -> str:
            if not self._access_name:
                self._access_name = builder.get_fresh_name(self.name_hint)
            return self._access_name

    class AbstractBlock(Source, ABC):
        def __init__(self, real_source: CodeBuilder.Source = None):
            super().__init__(real_source)
            self.target: CodeBuilder.Source | None = None

        def check_for_merging(self):
            pass

        def get_code(self, builder: CodeBuilder) -> str:
            raise NotImplementedError

        def get_access_text(
            self, builder: CodeBuilder, include_base_assignment=True
        ) -> str:
            if not self.enforce_local_storage:
                return self.get_code(builder)

            if self._access_name:
                return self._access_name

            code = self.get_code(builder)

            if (
                not include_base_assignment
                and self.usage_count == 0
                and (not self.target or self.target.usage_count == 0)
            ):
                return code

            name = (
                builder.get_fresh_name(type(self).__name__)
                if self.target is None
                else self.target.get_access_text(builder)
            )

            if include_base_assignment:
                builder.add_code_line(f"void* {name} = {code};")
                self._access_name = name
                return name
            else:
                return f"void* {name} = {code}"

    class CallBlock(AbstractBlock):
        def __init__(
            self,
            target: CodeBuilder.Source,
            base: CodeBuilder.Source,
            args: typing.List[CodeBuilder.Source],
        ):
            super().__init__(self)
            self.target = target
            self.base = base
            self.base.usage_count += 1
            self.args = args

            for arg in self.args:
                assert isinstance(arg, CodeBuilder.Source), arg
                arg.usage_count += 1

            self.enforce_local_storage = True

        def check_for_merging(self):
            self.target.enforce_local_storage = True
            for arg in self.args:
                arg.enforce_local_storage = True

        def get_code(self, builder: CodeBuilder) -> str:
            return f"{self.base.get_access_text(builder)}({', '.join(e.get_access_text(builder) for e in self.args)})"

    class SingletonOperatorBlock(AbstractBlock):
        def __init__(
            self, target: CodeBuilder.Source, operator: str, base: CodeBuilder.Source
        ):
            super().__init__(self)
            self.target = target
            self.operator = operator
            self.base = base
            self.base.usage_count += 1

        def check_for_merging(self):
            if self.base.real_value is not None:
                self.base = self.base.real_value

        def get_code(self, builder: CodeBuilder) -> str:
            return f"({self.operator}{self.base.get_access_text(builder)})"

    class BinaryOperatorBlock(AbstractBlock):
        def __init__(
            self,
            target: CodeBuilder.Source,
            operator: str,
            lhs: CodeBuilder.Source,
            rhs: CodeBuilder.Source,
        ):
            super().__init__(self)
            self.target = target
            self.operator = operator
            self.lhs = lhs
            self.lhs.usage_count += 1
            self.rhs = rhs
            self.rhs.usage_count += 1

        def check_for_merging(self):
            if self.lhs.real_value is not None:
                self.lhs = self.lhs.real_value

            if self.rhs.real_value is not None:
                self.rhs = self.rhs.real_value

        def get_code(self, builder: CodeBuilder) -> str:
            return f"({self.lhs.get_access_text(builder)} {self.operator} {self.rhs.get_access_text(builder)})"

    class StoreLocalBlock(AbstractBlock):
        def __init__(self, local: CodeBuilder.Source, base: CodeBuilder.Source):
            super().__init__(self)
            self.enforce_local_storage = True
            self.local = local
            self.base = base
            self.base.usage_count += 1

        def check_for_merging(self):
            if self.base.real_value is not None:
                self.base = self.base.real_value

        def get_code(self, builder: CodeBuilder) -> str:
            return f"void* {self.local.get_access_text(builder)} = {self.base.get_access_text(builder)}"

    PY_NONE = None
    PY_TRUE = None
    PY_FALSE = None

    def __init__(self, parent: CodeBuilder = None):
        self.parent = parent
        self.blocks: typing.List[CodeBuilder.AbstractBlock] = []
        self.local_source_cache: typing.Dict[str, CodeBuilder.Source] = {}
        self._is_building = False
        self.name_cache_counter = 0

        # The Block currently being targets for break and continue
        self.enclosing_loop = parent.enclosing_loop if parent else None

        # The Block in use currently for building if-elseif-else statements
        # todo: this is very tricky!
        self.if_building_block = None

        if parent is not None:
            # replace our variant of get_fresh_name with the parent variant, so we don't get conflicting names
            self.get_fresh_name = parent.get_fresh_name

    def get_stdlib_function(self, name: str) -> CodeBuilder.Source:
        """
        Returns a 'Source' object onto a 'function' definition somewhere in the standard-library

        Ensures that the necessary files are included.
        """
        raise NotImplementedError

    def get_stdlib_struct(self, name: str) -> CodeBuilder.Source:
        """
        Returns a 'Source' object onto a 'struct' definition somewhere in the standard-library

        Ensures that the necessary files are included.
        """
        raise NotImplementedError

    def get_fresh_name(self, hint: str = None) -> str:
        """
        Returns a new unique name for code generation.

        In most cases only useful for internal functions

        WARNING: when using child-CodeBuilder objects, this function will be replaced with the parent variant,
        to avoid name conflicts
        """
        i = self.name_cache_counter
        self.name_cache_counter += 1
        if not hint:
            return f"var{i}"

        for e in INVALID_CHARS_IN_HINT:
            hint = hint.replace(e, "")

        if not hint[0].isidentifier():
            hint = f"var_{hint}"

        if not hint.isidentifier():
            hint += "_"

        return f"{hint}{i}"

    def push_call(
        self, base: CodeBuilder.Source, *args: CodeBuilder.Source
    ) -> CodeBuilder.Source:
        """
        Returns a 'Source' representing a function call to 'base' with 'args'.

        The function ensures parameter evaluation order to be left-to-right, and as such must create
        local temporary variables.
        """
        target = CodeBuilder.Source()
        target.real_value = CodeBuilder.CallBlock(target, base, list(args))
        self.blocks.append(target.real_value)
        return target

    def push_singleton_operator(self, operator: str, base: CodeBuilder.Source):
        target = CodeBuilder.Source()
        target.real_value = CodeBuilder.SingletonOperatorBlock(target, operator, base)
        self.blocks.append(target.real_value)
        return target

    def push_binary_operator(
        self, operator: str, lhs: CodeBuilder.Source, rhs: CodeBuilder.Source
    ):
        target = CodeBuilder.Source()
        target.real_value = CodeBuilder.BinaryOperatorBlock(target, operator, lhs, rhs)
        self.blocks.append(target.real_value)
        return target

    def push_if_condition(self, condition: CodeBuilder.Source) -> CodeBuilder:
        # todo: set self.if_building_block
        raise NotImplementedError

    def push_else_if_condition(self, condition: CodeBuilder.Source) -> CodeBuilder:
        raise NotImplementedError

    def push_else_block(self) -> CodeBuilder:
        # todo: set self.if_building_block
        raise NotImplementedError

    def push_while_loop(self, condition: CodeBuilder.Source) -> CodeBuilder:
        # todo: set self.if_building_block
        raise NotImplementedError

    def push_for_loop(
        self,
        base_target: CodeBuilder.Source,
        base_expression: CodeBuilder.Source,
        condition: CodeBuilder.Source,
        step: CodeBuilder.Source,
    ) -> CodeBuilder:
        raise NotImplementedError

    def push_store_local(
        self, source: CodeBuilder.Source, name: str | CodeBuilder.Source
    ) -> CodeBuilder.Source:
        local = self.get_source_for_local(name) if isinstance(name, str) else name
        local.real_value = CodeBuilder.StoreLocalBlock(local, source)
        self.blocks.append(local.real_value)
        self.if_building_block = None
        return local

    def push_continue_statement(self, loop: CodeBuilder = None):
        raise NotImplementedError

    def push_break_statement(self, loop: CodeBuilder = None):
        raise NotImplementedError

    def push_return_statement(self, value: CodeBuilder.Source = None):
        raise NotImplementedError

    def push_evaluate_value(self, expr: CodeBuilder.Source) -> typing.Self:
        """
        Pushes the given 'expr' as a single-line statement into the source;
        this ensures that the given expression will be evaluated and not discarded

        :param expr: the expr to use
        :return: the builder itself
        """
        expr.usage_count += 1
        expr.enforce_local_storage = True
        return self

    def get_source_for_local(self, name: str) -> CodeBuilder.Source:
        return self.local_source_cache.get(
            name, None
        ) or self.local_source_cache.setdefault(
            name, CodeBuilder.Source(enforce_local_storage=True, name_hint=name)
        )

    def get_temporary(self, hint: str = None) -> CodeBuilder.Source:
        return self.get_source_for_local(self.get_fresh_name(hint))

    def merge_blocks_if_possible(self):
        """
        Util function for merging blocks from the current block list together

        WARNING: modifies the internal state of some Source-like objects
        """
        for block in self.blocks:
            block.check_for_merging()

        for i, block in reversed(list(enumerate(self.blocks))):
            # todo: need a better check
            if (
                not block.enforce_local_storage
                and not block.target.enforce_local_storage
            ):
                del self.blocks[i]

    def add_code_line(self, line: str):
        raise RuntimeError("only allowed while building code")

    def get_full_code(self) -> str:
        self._is_building = True
        self.merge_blocks_if_possible()

        lines = []

        old_add_line = self.add_code_line
        self.add_code_line = lines.append  # temporarily replace this function

        # Prevent Sourcery in this case, as we dynamically append from outside while in the loop
        # sourcery skip: for-append-to-extend
        for block in self.blocks:
            lines.append(
                block.get_access_text(self, include_base_assignment=False) + ";"
            )

        self.add_code_line = old_add_line
        self._is_building = False
        return "\n".join(lines)
