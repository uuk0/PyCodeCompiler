

def test():
    obj = list()
    obj.append(10)
    obj.append(20)
    obj.index(10)
    obj.remove(10)
    obj.append(30)
    obj[0] = 25
    obj[1] = obj[1]
    obj.clear()

