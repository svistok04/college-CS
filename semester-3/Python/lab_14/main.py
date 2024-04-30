import random
import numpy

zad1 = numpy.array([numpy.arange(1, 17, 5), numpy.arange(2, 18, 5), numpy.arange(3, 19, 5), numpy.arange(4, 20, 5)], dtype=int)
print(zad1)

def zad2_cramer(a, b) -> numpy.array:
    W = numpy.linalg.det(a)
    Wi = []

    for i in range(len(a)):
        temp = numpy.copy(a)
        temp[:, i] = b
        Wi.append(numpy.linalg.det(temp))
    if W != 0:
        return numpy.array(Wi) / W
    else:
        raise ValueError("W = 0")



# a = [[8, 1, 2], [5, -3, -7], [0, -5, 7]]
# b = [16, -22, 11]
a = [[1, 2], [3, 4]]
b = [5, 6]
print(zad2_cramer(a, b))

zad3 = numpy.zeros([6, 6], dtype=int)
for i in range (1, 4):
    zad3[i][1] = 1
    zad3[i][4] = 1
zad3[4][2] = 1
zad3[4][3] = 1

print(zad3)
print(numpy.rot90(zad3, 1))
print(numpy.rot90(zad3, -1))
print(numpy.rot90(zad3, 2))

zad4_a = numpy.ones([2, 2], dtype=int)
zad4_b = numpy.zeros([2, 1], dtype=int)

print(
    numpy.hstack((
        numpy.vstack((
            numpy.hstack((zad4_b, zad4_a, zad4_b)), numpy.hstack((zad4_b.transpose(), zad4_b.transpose()))
        )),
        numpy.vstack((zad4_b.transpose(), zad4_a))
    ))
)

zad5_1 = numpy.array(numpy.arange(0, 20, 2), dtype=int)
zad5_2 = numpy.array(numpy.arange(3, 34, 3), dtype=int)
print(-numpy.sort(-numpy.concatenate((zad5_1, zad5_2))))


def zad6(n: int, m: int) -> numpy.array:
    arr = numpy.random.randint(2, high=23, size=(n, m))
    arr[arr % 2 == 0] = -100
    arr[arr % 2 == 1] = 100
    return arr


print(zad6(5, 5))

zad7 = numpy.random.rand(1, 20)
print(zad7)

for x in numpy.nditer(zad7, op_flags=['readwrite']):
    match x[...]:
        case _ if x[...] < 0.33:
            x[...] = random.randint(10, 100)
        case _ if x[...] > 0.67:
            x[...] = random.randint(5, 10)
        case _:
            x[...] = round(random.uniform(0, 1), 3)

print(zad7)
