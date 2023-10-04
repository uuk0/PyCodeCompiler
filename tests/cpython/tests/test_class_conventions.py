import unittest


class TestClassCallable(unittest.TestCase):
    def test_basic(self):
        class Test:
            def __call__(self):
                return 10

        a = Test()
        self.assertEqual(a(), 10)

    def test_attribute(self):
        class Test:
            def __init__(self, value):
                self.value = value

            def __call__(self):
                return self.value

        a = Test(20)
        self.assertEqual(a(), 20)


if __name__ == "__main__":
    unittest.main()
