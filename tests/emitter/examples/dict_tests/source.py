def test():
    obj = dict()
    obj["test"] = 10
    assert obj["test"] == 10

    obj["test"] = 20
    assert obj["test"] == 20

    obj["other"] = 5
    assert obj["other"] == 5
