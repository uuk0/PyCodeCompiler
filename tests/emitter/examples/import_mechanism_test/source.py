import typing
import test_module


def test():
    assert typing.TYPE_CHECKING == False
    assert test_module.test_target() == 10
