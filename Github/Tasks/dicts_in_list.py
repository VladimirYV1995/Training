_from = {'a':[0,1], 'b':[2,3], 'c':[4,5]}

_to=[] #_to = [{'a':0,'b':2, 'c':4},{'a':1,'b':3, 'c':5}]

for i in range(len(list(_from.values())[0])):
    buf={}
    for key, val in _from.items():
        buf[key]=val[i]
    _to.append(buf)

print(_to)








#print('keys:',_from.keys())
#print('values:',_from.values())


#print(key,':',val)






