import os
import pathlib
import shutil
import subprocess
import sys

import typing
from unittest import TestCase
from pycompiler import Parser, Lexer, TypeResolver
from pycompiler.Parser import AssignmentExpression, NameAccessExpression, ConstantAccessExpression, CallExpression
from pycompiler.Lexer import TokenType


root = os.path.dirname(os.path.dirname(os.path.dirname(__file__)))
example_folder = f"{os.path.dirname(__file__)}/examples"


class TestCCodeEmitter(TestCase):
    def run_named_folder_test(self, name: str):
        if not os.path.exists(f"{root}/compiler.txt"):
            compiler = "gcc"
        else:
            with open(f"{root}/compiler.txt", mode="r") as f:
                compiler = f.read().strip()

        folder = f"{example_folder}/{name}"
        self.assertTrue(os.path.isdir(folder))

        self.assertTrue(os.path.exists(f"{folder}/source.py"))

        py = pathlib.Path(f"{folder}/source.py").read_text()
        parser = Parser.Parser(py)
        c_compare = parser.emit_c_code()

        if os.path.exists(f"{folder}/source.c"):
            c = pathlib.Path(f"{folder}/source.c").read_text()
            self.assertEqual(c, c_compare)

        if os.path.exists(f"{folder}/test.c"):
            self.compile_and_run(folder, c_compare, compiler)

    def compile_and_run(self, folder, c_compare, compiler):
        shutil.copy(f"{root}/pycompiler/templates/pyinclude.h", f"{folder}/pyinclude.h")

        with open(f"{folder}/result.c", mode="w") as f:
            f.write(c_compare)

        command = [
            compiler.replace("\\", "/"),
            "-g",
            f"{folder}/test.c".replace("\\", "/"),
            f"{folder}/result.c".replace("\\", "/"),
            f"{root}/pycompiler/templates/pyinclude.c",
            "-o",
            f"{folder}/test.exe",
        ]

        print(" ".join(command))
        exit_code = subprocess.call(command)
        self.assertEqual(exit_code, 0)

        exit_code = subprocess.call([f"{folder}/test.exe"])
        self.assertEqual(exit_code, 0)

        # os.remove(f"{folder}/test.exe")
        # os.remove(f"{folder}/pyinclude.h")
        # os.remove(f"{folder}/result.c")

    def test_simple_assignment(self):
        self.run_named_folder_test("simple_assignment")

    def test_function_export(self):
        self.run_named_folder_test("function_export")

    def test_class_declaration(self):
        self.run_named_folder_test("class_declaration")

    def test_class_declaration_with_function(self):
        self.run_named_folder_test("class_declaration_with_function")

    def test_while_statement(self):
        self.run_named_folder_test("while_statement")

