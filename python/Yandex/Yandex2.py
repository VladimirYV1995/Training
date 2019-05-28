f = open('1.txt')
Data=f.read()
DataWS=list(Data.split())
Quan=int(DataWS.pop(0))
Vote=Quan
for i in range(Quan):
    Vote+=int(DataWS[i*3+2])
print(Vote)


