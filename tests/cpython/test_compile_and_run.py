import unittest
import os
import subprocess

from pycompiler.Compiler import Project


folder = os.path.dirname(__file__)


class TestGenerator(unittest.TestCase):
    def compile_and_run(self, module_name: str):
        os.makedirs(f"{folder}/test_build/{module_name}", exist_ok=True)
        project = Project(f"{folder}/test_build/{module_name}")
        project.add_main_function()
        project.add_entry_point(f"{folder}/tests/test_{module_name}.py")
        project.build()

        exit_code = subprocess.call(f"{folder}/test_build/{module_name}/result.exe")
        self.assertEqual(exit_code, 0)

    def test_unittest(self):
        self.compile_and_run("unittest")

    def test_itertools(self):
        self.compile_and_run("itertools")

    # def test_list(self):
    #     self.compile_and_run("list")
