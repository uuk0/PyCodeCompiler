def test():
    test_simple()


def simple_target(a):
    return a


def test_simple():
    assert simple_target(*[10]) == 10
