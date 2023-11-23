from __future__ import annotations

import os
import unittest

from pycompiler.Compiler import Project


local = os.path.dirname(__file__)


class TestIntegration(unittest.TestCase):
    def helper(self, file: str):
        project = Project()
        code = project.compile_file(open(f"{local}/tests/{file}/test.py").read())
        self.assertEqual(open(f"{local}/tests/{file}/test.c").read(), code)

    def test_basic(self):
        self.helper("basic")

    def test_function_definition(self):
        self.helper("function_definition")
