import difflib
import os
import pathlib
import subprocess

from unittest import TestCase
from pycompiler import Parser
from pycompiler.Compiler import Project


root = os.path.dirname(os.path.dirname(os.path.dirname(__file__)))
example_folder = f"{os.path.dirname(__file__)}/examples"


class TestCCodeEmitter(TestCase):
    def run_named_folder_test(self, name: str):
        if "PY_CODE_COMPILER_BACKEND_COMPILER" in os.environ:
            compiler = os.environ["PY_CODE_COMPILER_BACKEND_COMPILER"]
        elif os.path.exists(f"{root}/compiler.txt"):
            with open(f"{root}/compiler.txt", mode="r") as f:
                compiler = f.read().strip()
        else:
            compiler = "gcc"

        folder = f"{example_folder}/{name}"
        self.assertTrue(os.path.isdir(folder))
        os.makedirs(f"{folder}/build", exist_ok=True)

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
                "ast nodes",
            )

        c_compare = parser.emit_pure_c_code(expr=ast_nodes, module_name="source")

        if os.path.exists(f"{folder}/source.c"):
            c = pathlib.Path(f"{folder}/source.c").read_text()

            with open(f"{folder}/build/source.c", mode="w") as f:
                f.write(c_compare)

            # with open(f"{folder}/source.c", mode="w") as f:
            #     f.write(c_compare)
            # c = c_compare

            self.assertEqual(c, c_compare, "c source")
        else:
            with open(f"{folder}/source.c", mode="w") as f:
                f.write(c_compare)

        if os.path.exists(f"{folder}/test.c"):
            self.compile_and_run(folder, compiler)
        else:
            self.compile_only(folder, compiler)

    def compile_and_run(self, folder, compiler):
        p = Project(
            build_folder=f"{folder}/build",
            compiler=compiler,
            compiler_output=f"{folder}/test.exe",
        )
        p.add_file(f"{folder}/test.c", is_entry=True)
        p.add_file(f"{folder}/source.py", is_entry=True)
        p.add_folder(folder)  # include the folder in the analysis
        p.build()

        exit_code = subprocess.call([f"{folder}/test.exe"])
        self.assertEqual(exit_code, 0, "tests")

    def compile_only(self, folder, compiler):
        p = Project(
            build_folder=f"{folder}/build",
            compiler=compiler,
            compile_only=True,
        )
        p.add_file(f"{folder}/source.py", is_entry=True)
        p.add_folder(folder)  # include the folder in the analysis
        p.build()

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

    def test_dict(self):
        self.run_named_folder_test("dict_tests")

    def test_integer_operations(self):
        self.run_named_folder_test("integer_operations")

    def test_assert_statement(self):
        self.run_named_folder_test("assert_test")

    def test_import_mechanism(self):
        self.run_named_folder_test("import_mechanism_test")

    def test_generators(self):
        self.run_named_folder_test("generators")

    def test_for_loop(self):
        self.run_named_folder_test("for_loop")

    def test_if_statement(self):
        self.run_named_folder_test("if_statement")

    def test_range(self):
        self.run_named_folder_test("range_tests")
