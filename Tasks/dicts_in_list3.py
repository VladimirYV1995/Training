'''C использованием Zip и Map'''

_from = {'a':[0,1], 'b':[2,3], 'c':[4,5]}

_to =[] #_to = [{'a': 0, 'b': 2, 'c': 4}, {'a': 1, 'b': 3, 'c': 5}] 

keys=_from.keys()
vals=_from.values() 



zip_val= zip(*vals)

for zv in zip_val:
     buf=dict(map(lambda *arg: arg, keys,zv))
     _to.append(buf)

print(_to)


'''
Better

_to = [dict(zip(_from,t)) for t in zip(*_from.values())]
print(_to)

and Dict to  list

v = {k: [dic[k] for dic in LD] for k in LD[0]}
print(v)

'''
