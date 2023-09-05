import os
import pathlib
import shutil
import subprocess
import sys

import typing
from unittest import TestCase
from pycompiler import Parser, Lexer, TypeResolver
from pycompiler.Parser import (
    AssignmentExpression,
    NameAccessExpression,
    ConstantAccessExpression,
    CallExpression,
)
from pycompiler.Lexer import TokenType


root = os.path.dirname(os.path.dirname(os.path.dirname(__file__)))
example_folder = f"{os.path.dirname(__file__)}/examples"


STANDARD_LIBRARY_FILES = [
    f"{root}/pycompiler/templates/standard_library/{file}"
    for file in os.listdir(f"{root}/pycompiler/templates/standard_library")
    if file.endswith(".c")
]


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
        ast_nodes = parser.parse()

        if os.path.exists(f"{folder}/ast.txt"):
            data = pathlib.Path(f"{folder}/ast.txt").read_text()
            self.assertEqual(
                "".join(e.strip() for e in data.split("\n"))
                .replace(" ", "")
                .replace(",NEWLINE", "")
                .replace("NEWLINE,", ""),
                repr(ast_nodes)
                .replace(" ", "")
                .replace(",NEWLINE", "")
                .replace("NEWLINE,", ""),
            )

        c_compare = parser.emit_c_code(expr=ast_nodes)

        with open(f"{folder}/result.c", mode="w") as f:
            f.write(c_compare)

        if os.path.exists(f"{folder}/source.c"):
            c = pathlib.Path(f"{folder}/source.c").read_text()
            self.assertEqual(c, c_compare)

        if os.path.exists(f"{folder}/test.c"):
            self.compile_and_run(folder, compiler)
        else:
            self.compile_only(folder, compiler)

    def compile_and_run(self, folder, compiler):
        command = [
            compiler.replace("\\", "/"),
            "-g",
            f"{folder}/test.c".replace("\\", "/"),
            f"{folder}/result.c".replace("\\", "/"),
            f"{root}/pycompiler/templates/pyinclude.c",
            f"-I{root}/pycompiler/templates",
            "-o",
            f"{folder}/test.exe",
        ] + STANDARD_LIBRARY_FILES

        print(" ".join(command))
        exit_code = subprocess.call(command)
        self.assertEqual(exit_code, 0)

        exit_code = subprocess.call([f"{folder}/test.exe"])
        self.assertEqual(exit_code, 0)

    def compile_only(self, folder, compiler):
        command = [
            compiler.replace("\\", "/"),
            "-g",
            "-c",
            f"{folder}/result.c".replace("\\", "/"),
            f"-I{root}/pycompiler/templates",
        ]

        print(" ".join(command))
        exit_code = subprocess.call(command)
        self.assertEqual(exit_code, 0)

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

    def test_class_instance_init(self):
        self.run_named_folder_test("class_instance_init")

    def test_callable_object(self):
        self.run_named_folder_test("callable_object")

    def test_list(self):
        self.run_named_folder_test("list_tests")

    def test_tuple(self):
        self.run_named_folder_test("tuple_tests")

    def test_integer_operations(self):
        self.run_named_folder_test("integer_operations")

    def test_assert_statement(self):
        self.run_named_folder_test("assert_test")
