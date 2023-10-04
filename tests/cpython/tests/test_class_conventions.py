import unittest


class TestClassCallable(unittest.TestCase):
    def test_basic(self):
        class Test:
            def __call__(self):
                return 10

        a = Test()
        self.assertEqual(a(), 10)


if __name__ == "__main__":
    unittest.main()
