def test():
    obj = dict()
    obj["test"] = 10
    assert obj["test"] == 10
    assert "test" in obj

    obj["test"] = 20
    assert obj["test"] == 20
    assert "test" in obj

    obj["other"] = 5
    assert obj["other"] == 5
