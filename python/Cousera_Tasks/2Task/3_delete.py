
#Шаг 5 В данных есть пропущенные значения — например, для некоторых пассажиров неизвестен их возраст.
#Такие записи при чтении их в pandas принимают значение nan.
#Найдите все объекты, у которых есть пропущенные признаки, и удалите их из выборки.

i=0
indexes=[i for i in range(len(X)) if np.isnan(X[i][2])]
XwNO=np.delete(X,indexes,axis=0)    
YwNO=np.delete(Y,indexes)            
