import os.path
import pathlib
import sys
import argparse

sys.path.append(os.path.dirname(os.path.dirname(__file__)))

import pycompiler.Compiler


parser = argparse.ArgumentParser(
    prog="PyCodeCompiler", description="Compile python files to .c"
)
parser.add_argument(
    "-o",
    "--output",
)
parser.add_argument("-e", "--entry")
parser.add_argument("--build-folder")
parser.add_argument("--compiler", default="gcc")
parser.add_argument("files", nargs="*")

arg = parser.parse_args()

project = pycompiler.Compiler.Project(
    build_folder=arg.build_folder
    or f"{os.path.dirname(arg.entry or arg.files[0])}/build",
    compiler=arg.compiler,
)
project.add_entry_point(arg.entry or arg.files[0])

for file in arg.files:
    project.add_file(file)


project.build()
