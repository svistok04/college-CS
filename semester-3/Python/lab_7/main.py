import math
import random
from Matrix import matrix_operations

# Zadanie 1
print('Zadanie 1')
help(math)

# Zadanie 2.1

print('Zadanie 2.1')
help(math.cos)  # kat w radianach

# Zadanie 2.2

print('Zadanie 2.2')
help(math.log)  # logarytm naturalny (e)

# Zadanie 3
print('Zadanie 3')

# Zadanie 4
print('Zadanie 4')
print('Addition')
a1 = [[random.randint(0, 20) for _ in range(3)] for _ in range(4)]
b1 = [[random.randint(0, 20) for _ in range(3)] for _ in range(4)]
res1 = matrix_operations.addition(a1, b1)
print(res1)
print('Adding a const')
a3 = [[random.randint(0, 20) for _ in range(3)] for _ in range(3)]
b3 = 5
res3 = matrix_operations.addition_by_const(a3, b3)
print('Before: ', a3, '\nAfter: ', res3)
print('Multiplication')
a3 = [[random.randint(0, 10) for _ in range(3)] for _ in range(3)]
b3 = [[random.randint(0, 10) for _ in range(4)] for _ in range(3)]
res3 = matrix_operations.multiplication(a3, b3)
print(res3)
print('Multiplication by const')
a4 = [[random.randint(0, 20) for _ in range(3)] for _ in range(3)]
b4 = 3
res4 = matrix_operations.multiplication_by_const(a4, b4)
print('Before: ', a4, '\nAfter: ', res4)
print('Hadamard product')
a5 = [[random.randint(0, 10) for _ in range(3)] for _ in range(5)]
b5 = [[random.randint(0, 10) for _ in range(3)] for _ in range(5)]
res5 = matrix_operations.hadamard_product(a5, b5)
print('Before: ', a5, ' and ', b5, '\nAfter: ', res5)
print('Kronecker product')
a6 = [[random.randint(1, 10) for _ in range(2)] for _ in range(2)]
b6 = [[random.randint(1, 10) for _ in range(2)] for _ in range(2)]
res6 = matrix_operations.kronecker_product(a6, b6)
print('Before: ', a6, ' and ', b6, '\nAfter: ', res6)


# Zadanie 5
print('Zadanie 5')

# Zadanie 6
print('Zadanie 6')


