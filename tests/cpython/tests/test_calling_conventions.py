import unittest


def simple_target(a):
    return a


def simple_target_keyword(a=10):
    return a


class TestCallStar(unittest.TestCase):
    def test_simple(self):
        f = simple_target
        self.assertEqual(f(*[10]), 10)


class TestKeyword(unittest.TestCase):
    def test_simple(self):
        f = simple_target_keyword
        self.assertEqual(f(), 10)
        self.assertEqual(f(a=20), 20)
        self.assertEqual(f(20), 20)


class TestStarStar(unittest.TestCase):
    def test_simple(self):
        f = simple_target_keyword
        self.assertEqual(f(**{}), 10)
        self.assertEqual(f(**{"a": 20}), 20)


class TestLambdaDeclaration(unittest.TestCase):
    def test_basic(self):
        x = lambda: 10
        self.assertEqual(x(), 10)

    def test_with_param(self):
        x = lambda a: a + 2
        self.assertEqual(x(2), 4)

    def test_lambda_ception(self):
        x = lambda: lambda: 10
        self.assertEqual(x()(), 10)


if __name__ == "__main__":
    unittest.main()
