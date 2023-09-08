import os
import pathlib
import shutil
import subprocess
import typing

from pycompiler.Parser import Parser, AbstractASTNode
from pycompiler.TypeResolver import GetModuleImports, GetHeaderRelatedInfo

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

        pending_compilation_files: typing.List[typing.Tuple[str, str]] = []
        compiled_files = set()
        prepared_module_files: typing.List[
            typing.Tuple[str, typing.List[AbstractASTNode], Parser, str]
        ] = []

        for entry_point in self.entry_points:
            if entry_point.endswith(".c"):
                include_files.append(entry_point)
                continue

            if not entry_point.endswith(".py"):
                raise NotImplementedError

            pending_compilation_files.append(
                (
                    entry_point,
                    entry_point.split("/")[-1].split("\\")[-1].removesuffix(".py"),
                )
            )

        while pending_compilation_files:
            file, module = pending_compilation_files.pop()

            if file in compiled_files:
                continue

            compiled_files.add(file)

            py = pathlib.Path(file).read_text()
            parser = Parser(py)
            ast_nodes = parser.parse()

            prepared_module_files.append((file, ast_nodes, parser, module))

            resolver = GetModuleImports()
            resolver.visit_any_list(ast_nodes)

            for module in resolver.modules:
                for f in self.path:
                    p = pathlib.Path(f)

                    if (
                        p.is_file()
                        and "." not in module
                        and p.name.removesuffix(".py") == module
                    ):
                        pending_compilation_files.append((str(p.absolute()), module))
                    elif p.is_dir():
                        for file in p.glob("**/*.py"):
                            if (
                                file.is_file()
                                and "." not in module
                                and file.name.removesuffix(".py") == module
                            ):
                                pending_compilation_files.append(
                                    (str(file.absolute()), module)
                                )

        for file, ast_nodes, parser, module in prepared_module_files:
            c_source = parser.emit_c_code(expr=ast_nodes, module_name=module)

            out_file = file.split("/")[-1].split("\\")[-1].removesuffix(".py") + ".c"
            with open(f"{build}/{out_file}", mode="w") as f:
                f.write(c_source)

            include_files.append(f"{build}/{out_file}")

            header_info = GetHeaderRelatedInfo()
            header_info.visit_any_list(ast_nodes)

            header = f"""#include "pyinclude.h"
            
// Header for the module {module}

// Functions
void PY_MODULE_{module.replace('.', '___')}_init(void);
"""

            for signature in header_info.function_signatures:
                header += f"{signature};\n"

            header += "\n// Variables\n"

            for variable in header_info.global_variables:
                header += f"extern {variable};\n"

            with open(f"{build}/{out_file.removesuffix('.c')}.h", mode="w") as f:
                f.write(header)

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
