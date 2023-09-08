def test():
    gen = generator_1()
    assert next(gen) == 1

    gen = generator_2()
    assert next(gen) == 1
    assert next(gen) == 2
    assert next(gen) == 4

    gen = generator_3()
    assert next(gen) == 1
    assert next(gen) == 2
    assert next(gen, None) == None


def generator_1():
    yield 1


def generator_2():
    yield 1
    yield 2
    yield 4


def generator_3():
    yield 1
    yield 2
    return
