import unittest


def simple_target(a):
    return a


def simple_target_keyword(a=10):
    return a


class TestFunctionInception(unittest.TestCase):
    def test_basic(self):
        def target():
            return 10

        self.assertEqual(target(), 10)

    def test_local_capture(self):
        extern = 10

        def target():
            return extern

        self.assertEqual(target(), 10)

    def test_local_capture_two_vars(self):
        extern = 10
        add = 2

        def target():
            return extern + add

        self.assertEqual(target(), 12)

    def test_local_capture_with_arg(self):
        extern = 10

        def target(add):
            return extern + add

        self.assertEqual(target(2), 12)


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
