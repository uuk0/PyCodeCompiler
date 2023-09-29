def test():
    test_simple(simple_target)
    test_simple_keyword(simple_target_keyword)


def simple_target(a):
    return a


def test_simple(f):
    assert f(*[10]) == 10


def simple_target_keyword(a=10):
    return a


def test_simple_keyword(f):
    assert f() == 10
    assert f(a=20) == 20
    assert f(20) == 20
