import unittest
import itertools


class TestItertoolsChain(unittest.TestCase):
    def test_chain_empty(self):
        self.assertEqual(list(itertools.chain([], [])), [])


if __name__ == "__main__":
    unittest.main()
