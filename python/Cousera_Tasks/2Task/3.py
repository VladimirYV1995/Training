import numpy as np
import pandas
from sklearn.tree import DecisionTreeClassifier

#Шаг 1 Загрузите выборку из файла titanic.csv с помощью пакета Pandas.
data = pandas.read_csv('titanic.csv', index_col='PassengerId')

#Требуемая выборка + флаг выживших
Sel=data[['Pclass','Fare','Age','Sex','Survived']]

#Шаг 5 В данных есть пропущенные значения — например, для некоторых пассажиров неизвестен их возраст.
#Такие записи при чтении их в pandas принимают значение nan.
#Найдите все объекты, у которых есть пропущенные признаки, и удалите их из выборки.
SelwN=Sel[~np.isnan(Sel['Age'])]

#Шаг 4 Выделите целевую переменную — она записана в столбце Survived.
#Выбираем выживших из пассажиров с известным возростом
Y=np.array(SelwN['Survived'])

#Шаг 2 Оставьте в выборке четыре признака: класс пассажира (Pclass), цену билета (Fare), возраст пассажира (Age) и его пол (Sex).

del SelwN['Survived']

#Превращение выборки SelwN в numpy.ndarray X
X=np.array(SelwN)

#Шаг 3 Обратите внимание, что признак Sex имеет строковые значения.
#Преобразование пола в числа ('male'=1,остальные, в нашем случае 'famale'=0)

for Obj in X:
    Obj[3]=int(np.where(Obj[3]=='male',1,0))

#Шаг 6 Обучите решающее дерево с параметром random_state=241 и остальными параметрами по умолчанию
#(речь идет о параметрах конструктора DecisionTreeСlassifier).

clf = DecisionTreeClassifier(random_state=241)
clf.fit(X,Y)

#Шаг 7 Вычислите важности признаков и найдите два признака с наибольшей важностью.
#Их названия будут ответами для данной задачи (в качестве ответа укажите названия признаков через запятую или пробел, порядок не важен).

importances = clf.feature_importances_

Names=[]
[Names.append(Name) for Name in SelwN]

print(Names)
print(importances)



