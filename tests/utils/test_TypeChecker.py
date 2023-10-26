from __future__ import annotations

import typing
import types
import unittest
import inspect

from pycompiler.TypeChecking import check_signature_compatible, check_type_matching


class TestTypeMatching(unittest.TestCase):
    def test_simple(self):
        self.assertTrue(check_type_matching(list, list))
        self.assertTrue(check_type_matching(tuple, tuple))
        self.assertFalse(check_type_matching(str, list))

    def test_rhs_generic_ignore(self):
        self.assertTrue(check_type_matching(list, list[int]))
        self.assertTrue(check_type_matching(tuple, tuple[str]))
        self.assertFalse(check_type_matching(str, list[int]))

    def test_lhs_generic_and_rhs_not(self):
        self.assertFalse(check_type_matching(list[str], list))
        self.assertFalse(check_type_matching(list[str], str))

    def test_both_generics_match(self):
        self.assertTrue(check_type_matching(list[int], list[int]))
        self.assertTrue(check_type_matching(tuple[str], tuple[str]))
        self.assertFalse(check_type_matching(list[int], list[str]))
        self.assertFalse(check_type_matching(list[int], tuple[int]))

    def test_union_subset(self):
        self.assertTrue(check_type_matching(int | str, int))
        self.assertTrue(check_type_matching(str | int, str | int))
        self.assertTrue(check_type_matching(str | int, int | str))
        self.assertFalse(check_type_matching(str, str | int))


class TestSignatureMatching(unittest.TestCase):
    def test_simple(self):
        self.assertTrue(
            check_signature_compatible(inspect.Signature(), inspect.Signature())
        )
        self.assertTrue(
            check_signature_compatible(
                inspect.Signature(
                    [inspect.Parameter("a", inspect.Parameter.POSITIONAL_OR_KEYWORD)]
                ),
                inspect.Signature(
                    [inspect.Parameter("a", inspect.Parameter.POSITIONAL_OR_KEYWORD)]
                ),
            )
        )
        self.assertTrue(
            check_signature_compatible(
                inspect.Signature(
                    [
                        inspect.Parameter(
                            "a",
                            inspect.Parameter.POSITIONAL_OR_KEYWORD,
                            annotation=list,
                        )
                    ]
                ),
                inspect.Signature(
                    [
                        inspect.Parameter(
                            "a",
                            inspect.Parameter.POSITIONAL_OR_KEYWORD,
                            annotation=list,
                        )
                    ]
                ),
            )
        )
