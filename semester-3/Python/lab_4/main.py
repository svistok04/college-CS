# Zadanie 1
import collections
import random

print('Zadanie 1\n')


def analizujProsokat(A, B):
    side_a = (A[0] - B[0])
    side_b = abs(A[1] - B[1])

    return 2 * (side_a + side_b), side_a * side_b


input_1 = input("Wpisz wspolrzedna pierwszego naroznika ")

A = eval(input_1)

# A = tuple(int(num) for num in input_1.replace(',', '').
#           replace('(', '').
#           replace(')', '').
#           replace(' ', '').
#           split(', '))

input_2 = input("Wpisz wspolrzedna drugiego naroznika ")

B = eval(input_2)

# B = tuple(int(num) for num in input_2.replace(',', '').
#           replace('(', '').
#           replace(')', '').
#           replace(' ', '').
#           split(', '))

l, S = analizujProsokat(A, B)

print(f"Obwod prostokata rownia sie {l} \t Pole prostokata rownia sie {S}")

# Zadanie 2

prostokat = collections.namedtuple('prostokat', ['x1', 'x2', 'y1', 'y2'])


def analizujProstokat(prosokat):
    side_a = abs(prosokat.x1 - prosokat.x2)
    side_b = abs(prostokat.y1 - prostokat.y2)

    return 2 * (side_a + side_b), side_a * side_b


some_prosokat = prostokat(1, 2, 2, 5)

l, S = analizujProsokat(A, B)

print(f"Obwod prostokata rownia sie {l} \t Pole prostokata rownia sie {S}")


# Zadanie 3

lista = list(range(1, 1002, 2))

print(lista)


# Zadanie 4

lista = list(range(1, 11))

lista_2 = lista.copy()

lista_2[3] = 5

print(lista, lista_2)

# Zadanie 5

lista_1 = list(random.randint(0, 9) for _ in range(100))

lista_2 = list(round(random.uniform(0, 9), 3) for _ in range(100))

print(*lista_1)
print(*lista_2)

lista_3 = lista_1 + lista_2

print(*lista_3)

lista_4 = random.sample(lista_3, 3)

print(lista_4)

# Zadanie 6

str1 = "kot"
str2 = "kociol"

counter = 0

if len(str1) > len(str2):
    for char in str2:
        if char in str1:
            counter += 1
    print(len(str1) - counter)
else:
    for char in str1:
        if char in str2:
            counter += 1
    print(len(str2) - counter)

