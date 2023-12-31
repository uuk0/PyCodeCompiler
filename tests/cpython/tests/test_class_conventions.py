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


class TestClassInClass(unittest.TestCase):
    def test_basic(self):
        class A:
            class B:
                def get(self):
                    return 10

        x = A.B()
        self.assertEqual(x.get(), 10)

        a = A()
        b = a.B()
        self.assertEqual(b.get(), 10)


class TestClassInFunction(unittest.TestCase):
    def test_basic(self):
        def target():
            class X:
                def get(self):
                    return 20

            return X

        obj = target()()
        self.assertEqual(obj.get(), 20)


if __name__ == "__main__":
    unittest.main()
