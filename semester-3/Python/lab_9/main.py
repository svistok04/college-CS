# from math import gcd
import math
from copy import copy, deepcopy
from abc import ABC, abstractmethod

# class Ulamek:
#     def __init__(self, m, l):
#         self.__mianownik = m
#         self.__licznik = l
#
#     def __add__(self, other):
#         mianownik1 = 0
#         mianownik2 = 0
#         lcm = 0
#         if self.__licznik != other.__licznik:
#             lcm = abs(self.__licznik * other.__licznik) / gcd(self.__licznik, other.__licznik)
#             mianownik1 = self.__mianownik * lcm / self.__licznik
#             mianownik2 = other.__mianownik * lcm / other.__licznik
#         return mianownik1 + mianownik2, lcm
#
#     def __sub__(self, other):
#         mianownik1 = 0
#         mianownik2 = 0
#         lcm = 0
#         if self.__licznik != other.__licznik:
#             lcm = abs(self.__licznik * other.__licznik) / gcd(self.__licznik, other.__licznik)
#             mianownik1 = self.__mianownik * lcm / self.__licznik
#             mianownik2 = other.__mianownik * lcm / other.__licznik
#         return mianownik1 - mianownik2, lcm
#
#     def __truediv__(self, other):
#         return self.__mianownik * other.__licznik, self.__licznik * other.__mianownik
#
#     def __mul__(self, other):
#         return self.__mianownik * other.__mianownik, self.__licznik * self.__licznik
#
#
# ulamek1 = Ulamek(3, 5)
# ulamek2 = Ulamek(2, 3)
#
# ulamek3 = ulamek1 + ulamek2
# print(ulamek3)
# ulamek3 = ulamek1 - ulamek2
# print(ulamek3)
# ulamek3 = ulamek1 * ulamek2
# print(ulamek3)
# ulamek3 = ulamek1 / ulamek2
# print(ulamek3)


class Osoba:
    _counter = 0

    def __init__(self, pesel: str, name: str, surname: str, height: int = 0, weight: float = 0.0):
        Osoba._counter += 1
        self.__pesel = pesel
        self.__name = name
        self.__surname = surname
        self.__height = height / 100
        self.__weight = weight
        match pesel[2]:
            case '8':
                self.__year = 1800
            case '0':
                self.__year = 1900
            case '2':
                self.__year = 2000
            case '4':
                self.__year = 2100
            case '6':
                self.__year = 2200
        self.__year += int(pesel[0]) * 10 + int(pesel[1])
        self.__age = 2023 - self.__year

    def __init__(self, pesel: str, name: str, surname: str, height: float = 0.0, weight: float = 0.0):
        Osoba._counter += 1
        self.__pesel = pesel
        self.__name = name
        self.__surname = surname
        self.__height = height
        self.__weight = weight
        match pesel[2]:
            case '8':
                self.__year = 1800
            case '0':
                self.__year = 1900
            case '2':
                self.__year = 2000
            case '4':
                self.__year = 2100
            case '6':
                self.__year = 2200
        self.__year += int(pesel[0]) * 10 + int(pesel[1])
        self.__age = 2023 - self.__year

    def __del__(self):
        Osoba._counter -= 1

    def __str__(self):
        return (str(self.__pesel) + ", "
                + str(self.__name) + " "
                + str(self.__surname) + " "
                + str(self.__age))

    def __repr__(self):
        return repr(str(self.__pesel) + " "
                    + str(self.__name) + " "
                    + str(self.__surname) + " "
                    + str(self.__height) + " "
                    + str(self.__weight) + " "
                    + str(self.__year) + " "
                    + str(self.__age))

    def __hash__(self):
        return int(self.__pesel)

    @property
    def weight(self):
        return self.__weight

    @weight.setter
    def weight(self, weight):
        self.__weight = weight

    @property
    def height(self):
        return self.__height

    @height.setter
    def height(self, height):
        self.__height = height

    @property
    def age(self):
        return self.__age

    @property
    def name(self):
        return self.__name

    @property
    def surname(self):
        return self.__surname

    @property
    def pesel(self):
        return self.__pesel

    @staticmethod
    def counter():
        print(Osoba._counter)

class Pracownik(Osoba):
    def __init__(self, pesel: str, name: str, surname: str, occupation: str, height: float = 0.0, weight: float = 0.0, salary: int = 0):
        super().__init__(pesel, name, surname, height, weight)
        self.__pesel = pesel
        self.__name = name
        self.__surname = surname
        self.__height = height / 100
        self.__weight = weight
        match pesel[2]:
            case '8':
                self.__year = 1800
            case '0':
                self.__year = 1900
            case '2':
                self.__year = 2000
            case '4':
                self.__year = 2100
            case '6':
                self.__year = 2200
        self.__year += int(pesel[0]) * 10 + int(pesel[1])
        self.__age = 2023 - self.__year
        self.__occupation = occupation
        self.__salary = salary

    def __str__(self):
        return (str(self.__pesel) + ", "
                + str(self.__name) + " "
                + str(self.__surname) + " "
                + str(self.__age) + " "
                + str(self.__occupation))

    def __repr__(self):
        return repr(str(self.__pesel) + " "
                    + str(self.__name) + " "
                    + str(self.__surname) + " "
                    + str(self.__height) + " "
                    + str(self.__weight) + " "
                    + str(self.__year) + " "
                    + str(self.__age) + " "
                    + str(self.__occupation) + " "
                    + str(self.__salary))


pracownik1 = Pracownik('23821532512', 'John', "Smith", 'Designer', 1.6, 55, 100000)
pracownik2 = pracownik1
print(repr(pracownik2))
# baza = {
#         Osoba('21821532124', 'Alex', 'Nowak'),
#         Osoba('21821532124', 'Alex', 'Nowak', 180, 50),
#         Osoba('21821532124', 'Alex', 'Nowak', 1.8, 50),
#         Pracownik('23821532512', 'John', "Smith", 'Designer', 1.6, 55, 100000),
#         Pracownik('25618274231', 'Vadim', 'Vadim', 'Clerk', 1.5, 100, 30000)
#         }
# # for person in baza:
# #     print(repr(person))
#
# pracownik1.counter()
#
# class Figura(ABC):
#     @abstractmethod
#     def oblicz_pole(self):
#         pass
#
#     @abstractmethod
#     def typ_figury(self):
#         pass
#
#     def print(self):
#         print('Figura:', self.typ_figury(), 'Pole:', self.oblicz_pole())
#
# class Kwadrat(Figura):
#     def __init__(self, a):
#         self.a = a
#
#     def oblicz_pole(self):
#         return self.a**2
#
#     def typ_figury(self):
#         return 'Kwadrat'
#
# class Kolo(Figura):
#     def __init__(self, r):
#         self.r = r
#
#     def oblicz_pole(self):
#         return 4*math.pi*pow(self.r, 2)
#
#     def typ_figury(self):
#         return 'Kolo'
#
# class Trojkat(Figura):
#     def __init__(self, a, b, c):
#         self.a = a
#         self.b = b
#         self.c = c
#
#     def oblicz_pole(self):
#         p = (self.a + self.b + self.c) / 2
#         return math.sqrt(p * (p - self.a) * (p - self.b) * (p - self.c))
#
#     def typ_figury(self):
#         return 'Trojkat'
#
# a = 5
# if isinstance(a, (int, float)):
#     kw = Kwadrat(a)
#     kw.print()
# else:
#     raise TypeError('Wrong type')
# a = 3
# if isinstance(a, (int, float)):
#     ko = Kolo(a)
#     ko.print()
# else:
#     raise TypeError('Wrong type')
#
# a = 'TROJKAT'
# b = 4
# c = 5
# if isinstance(a, (int, float)) and isinstance(b, (int, float)) and isinstance(c, (int, float)):
#     tr = Trojkat(a, b, c)
#     tr.print()
# else:
#     raise TypeError('Wrong type')
#
#
# try :
#     raise Exception('wystapil wyjatek') # zgloszenie ogolnego wyjatku
# except Exception as inst: # przypisanie instancja wyjatku
#     print(inst)

class complexClass:
    def __init__(self):
        self.a = [a]

    def __str__(self):
        return "a:" + str(self.a) + "id:" + str(id(self.a))

    def __copy__(self):
        cls = self.__class__
        result = cls.__new__(cls)
        result.__dict__.update(self.__dict__)
        return result

    def __deepcopy__(self, memo):
        cls = self.__class__
        result = cls.__new__(cls)
        memo[id(self)] = result
        for k, v in self.__dict__.items():
            setattr(result, k, deepcopy(v, memo))
        return result


a = complexClass(3)
b = copy(a)
c = deepcopy(a)
print(a)
print(b)
print(c)