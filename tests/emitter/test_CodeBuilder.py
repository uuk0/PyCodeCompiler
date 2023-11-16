from __future__ import annotations

import unittest
import typing

from pycompiler.emitter.CodeBuilder import CodeBuilder


class TestCodeBuilder(unittest.TestCase):
    def test_empty(self):
        builder = CodeBuilder()
        self.assertEqual(builder.get_full_code(), "")

    def test_call(self):
        builder = CodeBuilder()
        target = builder.get_source_for_local("test")
        builder.push_call(target)
        self.assertEqual("test1();", builder.get_full_code())

    def test_call_not_merge(self):
        builder = CodeBuilder()
        target = builder.get_source_for_local("test")
        call1 = builder.push_call(target)
        call2 = builder.push_call(call1)
        self.assertEqual(
            "void* var0 = test1();\nvar0();",
            builder.get_full_code(),
        )

    def test_singleton_operator(self):
        builder = CodeBuilder()
        target = builder.get_source_for_local("test")
        builder.push_evaluate_value(builder.push_singleton_operator("+", target))
        self.assertEqual("(+test0);", builder.get_full_code())

    def test_singleton_operator_merge(self):
        builder = CodeBuilder()
        target = builder.get_source_for_local("test")
        inner = builder.push_singleton_operator("+", target)
        builder.push_evaluate_value(builder.push_singleton_operator("-", inner))
        self.assertEqual("(-(+test0));", builder.get_full_code())

    def test_binary_operator(self):
        builder = CodeBuilder()
        lhs = builder.get_source_for_local("lhs")
        rhs = builder.get_source_for_local("rhs")
        builder.push_evaluate_value(builder.push_binary_operator("+", lhs, rhs))
        self.assertEqual("(lhs0 + rhs1);", builder.get_full_code())

    def test_variable_assignment(self):
        builder = CodeBuilder()
        target = builder.get_source_for_local("test")
        builder.push_store_local(target, "var")
        self.assertEqual("void* var1 = test2;", builder.get_full_code())
