_from = {'a':[0,1], 'b':[2,3], 'c':[4,5]}

_to =[] #_to = [{'a': 0}, {'a': 1}, {'b': 2}, {'b': 3}, {'c': 4}, {'c': 5}] 

for key, val in _from.items():
    for v in val:
        buf={}
        buf[key]=v
        _to.append(buf)
        
print(_to)
