_from = {'a':[0,1], 'b':[2,3], 'c':[4,5]}

_to =[] #_to = [{'a': 0, 'b': 2, 'c': 4}, {'a': 1, 'b': 3, 'c': 5}] 

_to = [dict(zip(_from,t)) for t in zip(*_from.values())]
print(_to)
