import unittest


def simple_target(a):
    return a


def basic_test(self, f):
    self.assertEqual(f(*[10]), 10)


def simple_target_keyword(a=10):
    return a


def test_simple_keyword(self, f):
    self.assertEqual(f(), 10)
    self.assertEqual(f(a=20), 20)
    self.assertEqual(f(20), 20)


def test_star_star(self, f):
    self.assertEqual(f(**{}), 10)
    self.assertEqual(f(**{"a": 20}), 20)


class TestCallStar(unittest.TestCase):
    def test_simple(self):
        basic_test(self, simple_target)


class TestKeyword(unittest.TestCase):
    def test_simple(self):
        test_simple_keyword(self, simple_target_keyword)


class TestStarStar(unittest.TestCase):
    def test_simple(self):
        test_star_star(self, simple_target_keyword)


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
