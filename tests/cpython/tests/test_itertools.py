import unittest
import itertools


class TestItertoolsChain(unittest.TestCase):
    def test_chain_empty(self):
        self.assertEqual(list(itertools.chain([], [])), [])

    # def test_chain_rhs_empty(self):
    #     self.assertEqual(list(itertools.chain(["test"], [])), ["test"])


if __name__ == "__main__":
    unittest.main()
