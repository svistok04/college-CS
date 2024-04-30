import math

# 1
print('Zadanie 1')


def time_format(seconds):
    hours = int(seconds / 3600)
    minutes = int((seconds - 3600 * hours) / 60)
    seconds = seconds - hours * 3600 - minutes * 60
    return hours, minutes, seconds


seconds_input = int(input('Ile sekund potrwalo? '))
x, y, z = time_format(seconds_input)
print('{} godzin, {} minut, {} sekund'.format(x, y, z))

# 2
print('Zadanie 2')


def kelvin_to_celsius(k):
    return k - 273.15


temperatureK = int(input('Jaka jest temperatura w K? '))
print('To {} w Celsjuszach'.format(round(kelvin_to_celsius(temperatureK), 3)))

# 3
print('Zadanie 3')


def some_function(x, n=10, k=2):
    return math.log(pow(x, 2) + 5, n) * (k + 1) * x


print('Wynik dla x = 2 i k = 7:', some_function(2, k=7))

# 4
print('Zadanie 4')

some_function_2 = lambda x: math.sin(x + 1) + math.cos(pow(x, 4))

for x in range(-5, 3):
    print("x =", x, ", wynik =", round(some_function_2(x), 3))

# generator_expr = (x for x in range(-5, 3))
#
# result = [some_function_2(x) for x in generator_expr]
# print(*result)

# 5
print('Zadanie 5')


def my_sum(*args: int):
    _sum = 0
    for i in args:
        _sum += i

    return _sum


print(my_sum(4, 2, 5, 3, 41, 2, 5, 9, 10))

# 6
print('Zadanie 6')


def find_volume(type, **kwargs):
    if type == 'kula':
        return 4 / 3 * math.pi * pow(kwargs['r'], 3)
    elif type == 'prostopadloscian':
        return kwargs['a'] * kwargs['b'] * kwargs['c']
    elif type == 'walec':
        return math.pi * pow(kwargs['r'], 2) * kwargs['h']
    elif type == 'stozek':
        return 1 / 3 * math.pi * pow(kwargs['r'], 2) * kwargs['h']


print('Kula:', round(find_volume('kula', r=3), 3))
print('Prostopadloscian', find_volume('prostopadloscian', a=2, b=3, c=4))
print('walec', round(find_volume('walec', r=3, h=4), 3))
print('stozek', round(find_volume('stozek', r=4, h=5), 3))

# 7
print('Zadanie 7')


def rozpakuj(a, b, c, d):
    return a, b, c, d


# some_list = [3, 5, 2, 6]
# a, b, c, d = rozpakuj(*some_list)
a, b, c, d = [4, 5, 9, 2]

print(a, b, c, d)

# 8
print('Zadanie 8')


def factorial_recursive(n):
    if n == 1:
        return 1

    return n * factorial_recursive(n - 1)


def factorial_iterative(n):
    result = 1
    for i in range(1, n + 1):
        result *= i

    return result


print('Silnia dla 5:', factorial_recursive(5))
print('Silnia dla 5:', factorial_iterative(5))

# 9
print('Zadanie 9')


def tribonacci(n):
    if n == 0 or n == 1:
        return 0

    if n == 2:
        return 1

    return tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3)


print('Wynik ciagu \'Tribonacciego\' dla 10:', tribonacci(10))
