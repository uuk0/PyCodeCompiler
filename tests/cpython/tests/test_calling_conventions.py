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


if __name__ == "__main__":
    unittest.main()
