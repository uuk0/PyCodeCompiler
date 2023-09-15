import unittest


class TestSimple(unittest.TestCase):
    def test_basic(self):
        self.assertTrue(True)
        self.assertFalse(False)
        self.assertEqual(10, 10)
        self.assertNotEqual(10, 20)


if __name__ == "__main__":
    unittest.main()
