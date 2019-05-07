_from = {'a':[0,1], 'b':[2,3], 'c':[4,5]}

_to = [{'a':0,'b':2, 'c':4},{'a':1,'b':3, 'c':5}]

for key, val in _from.items():
    print(key,':',val)

print('keys:',_from.keys())
print('values:',_from.values())
