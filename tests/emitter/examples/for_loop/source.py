def test():
    l = [1, 2, 3]
    s = 0

    for x in l:
        s = s + x

    return s


def test_2():
    l = [(1, 3), (7, 9), (3, 2)]
    s = 0

    for x, y in l:
        s += x // y

    return s
