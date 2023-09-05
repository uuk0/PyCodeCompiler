import os
import pathlib
import shutil
import subprocess
import typing

from pycompiler.Parser import Parser

_local = os.path.dirname(os.path.dirname(__file__))

STANDARD_LIBRARY_FILES = [
    f"{_local}/pycompiler/templates/standard_library/{file}"
    for file in os.listdir(f"{_local}/pycompiler/templates/standard_library")
    if file.endswith(".c")
]


class Project:
    def __init__(self, build_folder: str = None, compiler="gcc", compile_only=False):
        self.path: typing.List[str] = []
        self.entry_points = []
        self.build_folder = build_folder
        self.compiler = compiler

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

    def _ensure_std_build(self):
        # args = [
        #     "cmake",
        #     ".",
        #     "-S",
        #     f"{_local}/pycompiler/templates",
        #     "-B",
        #     f"{_local}/pycompiler/templates/cmake-build-debug",
        # ]
        #
        # print(" ".join(args))
        #
        # subprocess.call(
        #     args,
        #     cwd=f"{_local}/pycompiler/templates",
        # )
        pass  # todo: can we make this work?

    def build(self):
        build = self.build_folder or f"{_local}/build"

        if os.path.exists(build):
            shutil.rmtree(build)

        os.makedirs(build)

        self._ensure_std_build()

        has_std_build = False

        if os.path.exists(
            f"{_local}/pycompiler/templates/cmake-build-debug/libtemplates.a"
        ):
            shutil.copy(
                f"{_local}/pycompiler/templates/cmake-build-debug/libtemplates.a",
                f"{build}/pylib.a",
            )
            has_std_build = True

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
                entry_point.split("/")[0].split("\\")[0].removesuffix(".py") + ".c"
            )
            with open(f"{build}/{out_file}", mode="w") as f:
                f.write(c_compare)

            include_files.append(out_file)

        if not has_std_build:
            command = (
                [
                    self.compiler,
                    "-g",
                ]
                + include_files
                + self.path
                + STANDARD_LIBRARY_FILES
                + [
                    f"{_local}/pycompiler/templates/pyinclude.c",
                    f"-I{_local}/pycompiler/templates",
                    "-o",
                    f"{build}/result.exe",
                ]
            )

        else:
            command = (
                [
                    self.compiler,
                    "-g",
                ]
                + include_files
                + self.path
                + [
                    f"{build}/pylib.a",
                    f"{_local}/pycompiler/templates/pyinclude.c",
                    f"-I{_local}/pycompiler/templates",
                    "-o",
                    f"{build}/result.exe",
                ]
            )

        exit_code = subprocess.call(command)

        if exit_code != 0:
            raise RuntimeError(
                f"exit code {exit_code} of compiler {self.compiler} != 0"
            )
