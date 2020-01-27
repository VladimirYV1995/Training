def collatz(number):
    if number%2==0:
        n_l=number//2
    else:
        n_l=3*number+1
    return n_l

n_g='Введите целое число '

try:
    n_g=int(input(n_g))
    while n_g>1:
        n_g=collatz(n_g)
        print(n_g)
except ValueError:
    print("Ошибка числового ввода: ", n_g)



