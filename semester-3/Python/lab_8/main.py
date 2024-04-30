from math import gcd

class Ulamek:
    def __init__(self, m, l):
        self.__mianownik = m
        self.__licznik = l

    def __add__(self, other):
        mianownik1 = 0
        mianownik2 = 0
        lcm = 0
        if self.__licznik != other.__licznik:
            lcm = abs(self.__licznik * other.__licznik) / gcd(self.__licznik, other.__licznik)
            mianownik1 = self.__mianownik * lcm / self.__licznik
            mianownik2 = other.__mianownik * lcm / other.__licznik
        return mianownik1 + mianownik2, lcm

    def __sub__(self, other):
        mianownik1 = 0
        mianownik2 = 0
        lcm = 0
        if self.__licznik != other.__licznik:
            lcm = abs(self.__licznik * other.__licznik) / gcd(self.__licznik, other.__licznik)
            mianownik1 = self.__mianownik * lcm / self.__licznik
            mianownik2 = other.__mianownik * lcm / other.__licznik
        return mianownik1 - mianownik2, lcm

    def __truediv__(self, other):
        return self.__mianownik * other.__licznik, self.__licznik * other.__mianownik

    def __mul__(self, other):
        return self.__mianownik * other.__mianownik, self.__licznik * self.__licznik


ulamek1 = Ulamek(3, 5)
ulamek2 = Ulamek(2, 3)

ulamek3 = ulamek1 + ulamek2
print(ulamek3)
ulamek3 = ulamek1 - ulamek2
print(ulamek3)
ulamek3 = ulamek1 * ulamek2
print(ulamek3)
ulamek3 = ulamek1 / ulamek2
print(ulamek3)


class Osoba:
    _counter = 0

    def __init__(self, pesel: str, name: str, surname: str, height: int, weight: int):
        Osoba._counter += 1
        self.__pesel = pesel
        self.__name = name
        self.__surname = surname
        self.__height = height / 100
        self.__weight = weight / 100
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
        return self.__pesel

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

    @staticmethod
    def counter():
        print(Osoba._counter)


osoba1 = Osoba('21821532124', 'Alex', 'Nowak')
osoba2 = Osoba('21821532124', 'Alex', 'Nowak', )
osoba3 = Osoba('21821532124', 'Alex', 'Nowak', )
osoba4 = Osoba('21821532124', 'Alex', 'Nowak', )
osoba5 = Osoba('21821532124', 'Alex', 'Nowak', )
osoba6 = Osoba('21821532124', 'Alex', 'Nowak', )
osoba7 = Osoba('21821532124', 'Alex', 'Nowak', )
osoba8 = Osoba('21821532124', 'Alex', 'Nowak', )
osoba9 = Osoba('21821532124', 'Alex', 'Nowak', )
print(osoba1)
eval(repr(osoba1))
osoba1.counter()
