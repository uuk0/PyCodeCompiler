def test():
    test_simple(simple_target)


def simple_target(a):
    return a


def test_simple(f):
    assert f(*[10]) == 10
