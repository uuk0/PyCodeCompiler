import shutil
import sys
import unittest
import os
import subprocess
import difflib

from pycompiler.Compiler import Project


folder = os.path.dirname(__file__)


class TestGenerator(unittest.TestCase):
    def compile_and_run(self, module_name: str):
        os.makedirs(f"{folder}/test_build/{module_name}", exist_ok=True)
        project = Project(f"{folder}/test_build/{module_name}")
        project.add_main_function()
        project.add_entry_point(f"{folder}/tests/test_{module_name}.py")
        project.build()

        if not os.path.exists(f"{folder}/references/test_{module_name}.c"):
            shutil.copy(
                f"{folder}/test_build/{module_name}/test_{module_name}.c",
                f"{folder}/references/test_{module_name}.c",
            )
        else:
            with open(f"{folder}/references/test_{module_name}.c") as fc, open(
                f"{folder}/test_build/{module_name}/test_{module_name}.c"
            ) as fn:
                a = fc.read()
                b = fn.read()

                if a != b:
                    diff = "\n".join(difflib.unified_diff(a.split("\n"), b.split("\n")))
                    print(diff, file=sys.stdout)
                    self.fail("result differs from reference code!")

        exit_code = subprocess.call(f"{folder}/test_build/{module_name}/result.exe")

        if exit_code == 3221225477:
            self.fail("segfault in test")

        self.assertEqual(exit_code, 0, "running test as result.exe")

    def test_unittest(self):
        self.compile_and_run("unittest")

    def test_itertools(self):
        self.compile_and_run("itertools")

    def test_list(self):
        self.compile_and_run("list")

    def test_calling_conventions(self):
        self.compile_and_run("calling_conventions")

    def test_class_conventions(self):
        self.compile_and_run("class_conventions")
