import os
import pathlib
import shutil
import subprocess
import typing

from pycompiler.Parser import Parser

_local = os.path.dirname(os.path.dirname(__file__))

STANDARD_LIBRARY_FILES = []


for r, dirs, files in os.walk(f"{_local}/pycompiler/templates/standard_library"):
    STANDARD_LIBRARY_FILES.extend(
        os.path.join(r, file).replace("\\", "/")
        for file in files
        if file.endswith(".c")
    )


class Project:
    def __init__(
        self,
        build_folder: str = None,
        compiler="gcc",
        compile_only=False,
        compiler_output=None,
    ):
        self.path: typing.List[str] = []
        self.entry_points = []
        self.build_folder = build_folder
        self.compiler = compiler
        self.compile_only = compile_only
        self.compiler_output = (
            compiler_output
            or f"{build_folder}/result." + (".o" if compile_only else ".exe")
            if build_folder
            else None
        )

    def add_folder(self, path: str):
        if not os.path.isdir(path):
            raise ValueError(path)
        self.path.append(path)

    def add_file(self, path: str, is_entry=False):
        if not os.path.isfile(path):
            raise ValueError(path)
        self.path.append(path)
        if is_entry:
            self.add_entry_point(path)

    def add_entry_point(self, path_or_module: str):
        self.entry_points.append(path_or_module)

    def build(self):
        build = self.build_folder or f"{_local}/build"

        if os.path.exists(build):
            shutil.rmtree(build)

        os.makedirs(build)

        include_files = []

        for entry_point in self.entry_points:
            if entry_point.endswith(".c"):
                include_files.append(entry_point)
                continue

            if not entry_point.endswith(".py"):
                raise NotImplementedError

            py = pathlib.Path(entry_point).read_text()
            parser = Parser(py)
            ast_nodes = parser.parse()
            c_compare = parser.emit_c_code(expr=ast_nodes)

            out_file = (
                entry_point.split("/")[-1].split("\\")[-1].removesuffix(".py") + ".c"
            )
            with open(f"{build}/{out_file}", mode="w") as f:
                f.write(c_compare)

            include_files.append(f"{build}/{out_file}")

        command = (
            [
                self.compiler,
                "-g",
            ]
            + include_files
            + [
                f"-I{_local}/pycompiler/templates",
                f"-I{build}",
            ]
            + (
                ["-c"]
                if self.compile_only
                else STANDARD_LIBRARY_FILES
                + [
                    f"{_local}/pycompiler/templates/pyinclude.c",
                ]
            )
            + (
                [
                    "-o",
                    self.compiler_output,
                ]
                if self.compiler_output
                else []
            )
        )

        print(command)

        exit_code = subprocess.call(command)

        if exit_code != 0:
            raise RuntimeError(
                f"exit code {exit_code} of compiler {self.compiler} != 0"
            )
