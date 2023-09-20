def test():
    obj = list()
    obj.append(10)
    obj.append(20)

    assert obj.index(10) == 0

    obj.remove(10)
    obj.append(30)
    obj.insert(0, 20)
    obj[0] = 25
    obj[1] = obj[1]
    obj.clear()

    [10, 20, [50, 423]]

    assert len(obj) == 0
    obj.append(10)
    assert len(obj) == 1

    obj.extend([10])
    assert len(obj) == 2

    obj = obj + [20]
    assert len(obj) == 3

    obj = [x + 2 for x in obj]
    assert obj == [12, 12, 22]

    t = 2
    obj = [x + t for x in obj]
    assert obj == [14, 14, 24]
