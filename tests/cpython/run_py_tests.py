import unittest
import os

from pycompiler.Compiler import Project


folder = os.path.dirname(__file__)


class TestGenerator(unittest.TestCase):
    def compile_and_run(self, module_name: str):
        project = Project(f"{folder}/test_build/{module_name}")
        project.add_entry_point(f"{folder}/tests/test_{module_name}.py")
        project.build()

    # def test_unittest(self):
    #     self.compile_and_run("unittest")
