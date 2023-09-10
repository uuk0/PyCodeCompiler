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

    gen = generator_4()
    assert next(gen) == 5
    assert next(gen) == 10

    gen = generator_5()
    assert next(gen) == 1
    assert next(gen) == 2
    assert next(gen) == 4

    gen = generator_6()
    assert next(gen) == 1
    assert next(gen) == 2
    assert next(gen) == 4


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
    yield 5


def generator_4():
    a = 10
    yield 5
    yield a


def generator_5():
    yield from generator_2()


def generator_6():
    yield from [1, 2, 4]
