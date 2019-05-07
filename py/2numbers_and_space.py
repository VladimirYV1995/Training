string=input('Введите числа через пробел: ')
numbers = string.split()
buf=0
for i in numbers:
    try:
        buf+=int(i)
    except ValueError:
        print("Ошибка числового ввода: ",i)

print(buf)    
