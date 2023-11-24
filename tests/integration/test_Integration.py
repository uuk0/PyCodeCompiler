from __future__ import annotations

import difflib
import os
import unittest

from pycompiler.Compiler import FileInstance


local = os.path.dirname(__file__)


class TestIntegration(unittest.TestCase):
    def helper(self, file: str):
        file_obj = FileInstance(f"{local}/tests/{file}/test.py")
        file_obj.parse()
        file_obj.apply_ast_operations()
        code = file_obj.get_c_code()
        ecode = open(f"{local}/tests/{file}/test.c").read()

        if code != ecode:
            print(
                "\n\n".join(
                    list(difflib.unified_diff(ecode.split("\n"), code.split("\n")))
                )
            )
            self.assertEqual(code, ecode)

    def test_basic(self):
        self.helper("basic")

    def test_function_definition(self):
        self.helper("function_definition")

    def test_operators(self):
        self.helper("operators")
