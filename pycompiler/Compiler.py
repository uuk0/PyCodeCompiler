import os
import pathlib
import shutil
import subprocess
import typing

from pycompiler.Parser import Parser, AbstractASTNode, Scope, ConstantAccessExpression
from pycompiler.TypeResolver import (
    GetModuleImports,
    GetHeaderRelatedInfo,
    ModuleReferencesResolver,
)
from pycompiler.TypeResolver import (
    ResolveParentAttribute,
    ScopeGeneratorVisitor,
    LocalNameValidator,
    ResolveKnownDataTypes,
    ResolveLocalVariableAccessTypes,
    ResolveClassFunctionNode,
    ResolveStaticNames,
    ResolveGlobalNames,
    NameNormalizer,
    BinaryOperatorPriorityRewriter,
)

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
            or f"{build_folder}/result" + (".o" if compile_only else ".exe")
            if build_folder
            else None
        )
        self.add_main_function_flag = False

    def add_folder(self, path: str):
        if not os.path.isdir(path):
            raise ValueError(path)
        self.path.append(path)

    def add_main_function(self):
        self.add_main_function_flag = True
        return self

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
            typing.Tuple[str, typing.List[AbstractASTNode], Parser, str, Scope]
        ] = []
        entry_module_names = set()

        if self.add_main_function_flag:
            content = """// Generated Entry File
#include <assert.h>
#include "pyinclude.h"
#include "standard_library/exceptions.h"
"""

            for entry_point in self.entry_points:
                if entry_point.endswith(".py"):
                    module_name = (
                        entry_point.split("/")[-1].split("\\")[-1].removesuffix(".py")
                    )
                    content += f'\n#include "{module_name}.h"'

            content += """
int main(int argc, char** args)
{"""
            for entry_point in self.entry_points:
                if entry_point.endswith(".py"):
                    module_name = (
                        entry_point.split("/")[-1].split("\\")[-1].removesuffix(".py")
                    )
                    content += f"\n    PY_CHECK_EXCEPTION_AND_EXIT(PY_MODULE_{module_name}_init());"

            content += "\n}\n"

            with open(f"{build}/entry.c", mode="w") as f:
                f.write(content)

            self.add_file(f"{build}/entry.c", is_entry=True)

        for entry_point in self.entry_points:
            if entry_point.endswith(".c"):
                include_files.append(entry_point)
                continue

            if not entry_point.endswith(".py"):
                raise NotImplementedError

            pending_compilation_files.append(
                (
                    entry_point,
                    module_name := entry_point.split("/")[-1]
                    .split("\\")[-1]
                    .removesuffix(".py"),
                )
            )
            entry_module_names.add(module_name)

        while pending_compilation_files:
            file, module = pending_compilation_files.pop()

            if file in compiled_files:
                continue

            compiled_files.add(file)

            py = pathlib.Path(file).read_text()
            parser = Parser(py)
            ast_nodes = parser.parse()

            prepared_module_files.append((file, ast_nodes, parser, module, Scope()))

            resolver = GetModuleImports()
            resolver.visit_any_list(ast_nodes)

            for module in resolver.modules:
                if module in Scope.STANDARD_LIBRARY_MODULES:
                    continue

                for f in self.path:
                    p = pathlib.Path(f)

                    if (
                        p.is_file()
                        and "." not in module
                        and p.name.removesuffix(".py") == module
                    ):
                        pending_compilation_files.append((str(p.absolute()), module))
                        break

                    elif p.is_dir():
                        for file in p.glob("**/*.py"):
                            if (
                                file.is_file()
                                and str(file).endswith(".py")
                                and (
                                    str(file.relative_to(p))
                                    .removesuffix(".py")
                                    .replace("/", ".")
                                    .replace("\\", ".")
                                    == module
                                )
                            ):
                                pending_compilation_files.append(
                                    (str(file.absolute()), module)
                                )
                                break
                        else:
                            continue
                        break

                else:
                    print(self.path)
                    raise ModuleNotFoundError(module)

        for file, ast_nodes, parser, module, scope in prepared_module_files:
            Scope.STANDARD_LIBRARY_VALUES["__name__"] = {
                "*": module if module not in entry_module_names else "__main__"
            }
            self.apply_prep_optimisation_on_module(scope, ast_nodes)

        module_table: typing.Dict[str, dict] = {
            module: parser.get_module_content(ast_nodes)
            for _, ast_nodes, parser, module, __ in prepared_module_files
        }

        for file, ast_nodes, parser, module, scope in prepared_module_files:
            Scope.STANDARD_LIBRARY_VALUES["__name__"] = {
                "*": module if module not in entry_module_names else "__main__"
            }
            ModuleReferencesResolver(module_table).visit_any_list(ast_nodes)

        for file, ast_nodes, parser, module, scope in prepared_module_files:
            Scope.STANDARD_LIBRARY_VALUES["__name__"] = {
                "*": module if module not in entry_module_names else "__main__"
            }
            self.apply_big_optimisation_on_module(ast_nodes)

        for file, ast_nodes, parser, module, scope in prepared_module_files:
            Scope.STANDARD_LIBRARY_VALUES["__name__"] = {
                "*": module if module not in entry_module_names else "__main__"
            }
            c_source = parser.emit_c_code(
                expr=ast_nodes, module_name=module, scope=scope
            )

            out_file = file.split("/")[-1].split("\\")[-1].removesuffix(".py") + ".c"
            with open(f"{build}/{out_file}", mode="w") as f:
                f.write(c_source)

            include_files.append(f"{build}/{out_file}")

            header_info = GetHeaderRelatedInfo()
            header_info.visit_any_list(ast_nodes)

            header = f"""#include "pyinclude.h"
#include "standard_library/generator.h"
            
// Header for the module {module}

// Functions
PyObjectContainer* PY_MODULE_{module.replace('.', '___')}_init(void);
"""

            for signature in header_info.function_signatures:
                header += f"{signature};\n"

            header += f"\n// Variables\nextern PyObjectContainer* PY_MODULE_INSTANCE_{module.replace('.', '___')};\n"

            for variable in header_info.global_variables:
                header += f"extern {variable};\n"

            with open(f"{build}/{out_file.removesuffix('.c')}.h", mode="w") as f:
                f.write(header)

        command = (
            [
                self.compiler,
                "-g",
                # "-Wall",
                # "-Wextra",
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

    def apply_big_optimisation_on_module(self, ast_nodes):
        ResolveLocalVariableAccessTypes.DIRTY = True
        while ResolveLocalVariableAccessTypes.DIRTY:
            ResolveKnownDataTypes().visit_any_list(ast_nodes)
            ResolveClassFunctionNode().visit_any_list(ast_nodes)

            ResolveLocalVariableAccessTypes.DIRTY = False
            ResolveLocalVariableAccessTypes().visit_any_list(ast_nodes)
        ResolveGlobalNames().visit_any_list(ast_nodes)

    def apply_prep_optimisation_on_module(self, scope, ast_nodes):
        assert scope is not None
        ResolveParentAttribute().visit_any_list(ast_nodes)
        BinaryOperatorPriorityRewriter().visit_any_list(ast_nodes)
        ScopeGeneratorVisitor(scope).visit_any_list(ast_nodes)
        NameNormalizer().visit_any_list(ast_nodes)
        LocalNameValidator().visit_any_list(ast_nodes)
        ResolveStaticNames().visit_any_list(ast_nodes)
