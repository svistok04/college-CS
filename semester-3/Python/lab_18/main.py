import math
import unittest

class DList:
    class Element:
        def __init__(self, value):
            self.__value = value
            self.next = None
            self.prev = None

        @property
        def value(self):
            return self.__value

    def __init__(self, args):
        self.__root = None
        self.__end = None
        for i in args:
            self.insert(i)

    def insert(self, value):
        new_node = self.Element(value)
        if self.__root is None:
            self.__root = new_node
            self.__end = self.__root
            return

        if value < self.__root.value:
            if self.__root.next is not None:
                self.__root.next.prev = new_node
            self.__root.prev = new_node
            new_node.next = self.__root
            self.__root = new_node
            return

        curr = self.__root
        while curr.next is not None:
            if value < curr.next.value:
                new_node.prev = curr
                new_node.next = curr.next
                curr.next.prev = new_node
                curr.next = new_node
                return
            curr = curr.next

        new_node.prev = curr
        curr.next = new_node
        self.__end = new_node

    def __iter__(self):
        curr = self.__root
        while curr is not None:
            yield curr.value
            curr = curr.next

    def __reversed__(self):
        curr = self.__end
        while curr is not None:
            yield curr.value
            curr = curr.prev

    def __contains__(self, value):
        curr = self.__root
        while curr is not None:
            if curr.value == value:
                return True
            if curr.value > value or curr == self.__end:
                return False
            curr = curr.next

    @property
    def root(self):
        return self.__root

    @property
    def end(self):
        return self.__end

class TestZad1(unittest.TestCase):
    d_linked_list = DList([])

    def test_init(self):
        self.assertIsNone(self.d_linked_list.root)
        self.assertIsNone(self.d_linked_list.end)

    def test_insert(self):
        self.d_linked_list.insert(1)
        self.assertEqual(self.d_linked_list.root.value, 1)
        self.assertEqual(self.d_linked_list.end.value, 1)
        self.d_linked_list.insert(2)
        self.assertEqual(self.d_linked_list.root.value, 1)
        self.assertEqual(self.d_linked_list.end.value, 2)
        self.d_linked_list.insert(0)
        self.assertEqual(self.d_linked_list.root.value, 0)
        self.assertEqual(self.d_linked_list.end.value, 2)
        self.d_linked_list.insert(1.5)
        self.assertEqual(self.d_linked_list.root.value, 0)
        self.assertEqual(self.d_linked_list.end.value, 2)
        self.d_linked_list.insert(1.2)
        self.assertEqual(self.d_linked_list.root.value, 0)
        self.assertEqual(self.d_linked_list.end.value, 2)

# Zadanie 2

class TestZad2(unittest.TestCase):
    def test_log(self):
        self.assertEqual(math.log10(100), 2)
        with self.assertRaises(ValueError):
            math.log10(-100)

    def test_sqrt(self):
        self.assertEqual(math.sqrt(4), 2)
        self.assertGreaterEqual(math.sqrt(4), 0)
        with self.assertRaises(ValueError):
            math.sqrt(-4)

    def test_isfinite(self):
        self.assertTrue(math.isfinite(1))
        self.assertFalse(math.isfinite(math.inf))
        self.assertFalse(math.isfinite(math.nan))

    def test_pi(self):
        self.assertGreater(math.pi, 3.14)
        self.assertAlmostEqual(math.pi, 3.14159265359, 7)

# Zadanie 3

class TestZad3(unittest.TestCase):
    def test_nan_in_list(self):
        test_list = [1, 2, 3, float('nan'), 4, 5]

        # Check if NaN is in list
        contains_nan = any(math.isnan(x) if isinstance(x, float) else False for x in test_list)

        self.assertTrue(contains_nan)


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

class TestZad4Osoba(unittest.TestCase):
    def test_init(self):
        osoba = Osoba("01234567890", "Jan", "Kowalski")
        self.assertEqual(osoba.pesel, "01234567890")
        self.assertEqual(osoba.name, "Jan")
        self.assertEqual(osoba.surname, "Kowalski")
        self.assertEqual(osoba.height, 0)
        self.assertEqual(osoba.weight, 0)
        self.assertEqual(osoba.age, 33)

class TestZad4Pracownik(unittest.TestCase):
    def test_init(self):
        pracownik = Pracownik("01234567890", "Jan", "Kowalski", "Programista")
        self.assertEqual(pracownik.pesel, "01234567890")
        self.assertEqual(pracownik.name, "Jan")
        self.assertEqual(pracownik.surname, "Kowalski")
        self.assertEqual(pracownik.height, 0)
        self.assertEqual(pracownik.weight, 0)
        self.assertEqual(pracownik.age, 33)
        # self.assertEqual(pracownik.occupation, "Programista")
        # self.assertEqual(pracownik.salary, 0)

unittest.main()
