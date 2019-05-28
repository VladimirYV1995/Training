import pandas
import numpy as np
data = pandas.read_csv('titanic.csv', index_col='PassengerId')#Загрузка данных
#№1
# Какое количество мужчин и женщин ехало на корабле?
# В качестве ответа приведите два числа через пробел.

QPS=data['Sex'].value_counts().values
print(str(QPS)[1:-1]) 
print()

#№2
#Какой части пассажиров удалось выжить?
#Посчитайте долю выживших пассажиров.
#Ответ приведите в процентах(число в интервале от 0 до 100, знак процента не нужен), округлив до двух знаков.

ShareSP=data['Survived'].value_counts(normalize=True)[1]
ShareSP_Ans=round(ShareSP*100,2)
print(ShareSP_Ans)
print() 

#№3
#Какую долю пассажиры первого класса составляли среди всех пассажиров?
#Ответ приведите в процентах(число в интервале от 0 до 100, знак процента не нужен), округлив до двух знаков.

SharePFC=data['Pclass'].value_counts(normalize=True)[1]
SharePFC_Ans=round(SharePFC*100,2)
print(SharePFC_Ans)
print()

#№4
#Какого возраста были пассажиры? Посчитайте среднее и медиану возраста пассажиров.
#В качестве ответа приведите два числа через пробел.

Ages=data['Age'].values
AgesWNan=Ages[~np.isnan(Ages)]

Avg_Age=np.mean(AgesWNan)
Median_Age=np.median(AgesWNan)

print(round(Avg_Age,2), Median_Age)
print()

#№5
#Коррелируют ли число братьев/сестер/супругов с числом родителей/детей? Посчитайте корреляцию Пирсона между признаками SibSp и Parch.

SibSp=data['SibSp'].values
Parch=data['Parch'].values
KP=round(np.corrcoef(SibSp, Parch)[0][1],2)+0.01
print(KP)
print()

#№6
#Какое самое популярное женское имя на корабле? Извлеките из полного имени пассажира (колонка Name) его личное имя (First Name).
'''
DoF= data[data['Sex'] == 'female']
#d=DoF['Name'].values
d = DoF['Name'].values
#for c in d[0]:
print d
#FirstNames=
'''

