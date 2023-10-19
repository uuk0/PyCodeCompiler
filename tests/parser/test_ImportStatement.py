from unittest import TestCase

from pycompiler.parser.Parser import Parser
from pycompiler.parser.NameAccessNode import NameAccessNode
from pycompiler.parser.ImportStatementNode import ImportStatement


class TestAssignmentParsing(TestCase):
    def helper(self, code: str, expected: ImportStatement):
        parser = Parser(code)
        self.assertEqual(parser.try_parse_code_line_obj(), expected)
        parser = Parser(code)
        self.assertEqual(parser.parse_code_block(), [expected])

    def test_raw_import(self):
        self.helper("import test", ImportStatement("test"))

    def test_raw_import_with_dot(self):
        self.helper("import test.part", ImportStatement("test.part"))

    def test_from_import(self):
        self.helper("from source import test", ImportStatement("test", "source"))

    def test_from_import_lhs_dot(self):
        self.helper(
            "from source.part import test", ImportStatement("test", "source.part")
        )

    def test_from_import_rhs_dot(self):
        self.helper(
            "from source import test.part", ImportStatement("test.part", "source")
        )

    def test_from_import_lhs_rhs_dot(self):
        self.helper(
            "from source.part import test.portion",
            ImportStatement("test.portion", "source.part"),
        )

    def test_raw_import_with_as(self):
        self.helper("import test as x", ImportStatement("test", as_name="x"))

    def test_raw_import_with_dot_with_as(self):
        self.helper("import test.part as x", ImportStatement("test.part", as_name="x"))

    def test_from_import_with_as(self):
        self.helper(
            "from source import test as x",
            ImportStatement("test", "source", as_name="x"),
        )

    def test_from_import_lhs_dot_with_as(self):
        self.helper(
            "from source.part import test as x",
            ImportStatement("test", "source.part", as_name="x"),
        )

    def test_from_import_rhs_dot_with_as(self):
        self.helper(
            "from source import test.part as x",
            ImportStatement("test.part", "source", as_name="x"),
        )

    def test_from_import_lhs_rhs_dot_with_as(self):
        self.helper(
            "from source.part import test.portion as x",
            ImportStatement("test.portion", "source.part", as_name="x"),
        )
