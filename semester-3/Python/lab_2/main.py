# zadanie 1
"""a = [0, -2, 1, 7, 3, 4]
print(a[5], a[4], a[3], a[2], a[1], a[0])
"""
# zadanie 2

"""x, y, z = map(int, input("Wpisz wartości x, y i z \n").split())
c = int(input("Wybierz opcję: 1 - zwrocić sumę; 2 - zwrocić roznicę; 3 - zwrocić iloczyn; inna liczba - zwrocić "
              "iloraz \n"))

match c:
    case 1:
        print(x+y+z)
    case 2:
        print(x-y-z)
    case 3:
        print(x*y*z)
    case _:
        if y != 0 and z != 0:
            print(x/y/z)
        else:
            print("brak możliwości dzielenia przez 0")
"""
# zadanie 3

"""wzrost_cm = int(input("Podaj swój wzrost (w centymetrach): "))
waga_g = int(input("Podaj swoją wagę (w gramach): "))
wzrost_m = float(wzrost_cm)/100
waga_kg = float(waga_g)/1000
bmi = waga_kg / pow(wzrost_m, 2)
print("Twój wzrost w metrach: {:.2f}; \nTwoja waga w kilogramach: {:.2f}; \nTwój wskaźnik BMI: {:.2f}."
      .format(wzrost_m, waga_kg, bmi))

match bmi:
    case _ if bmi < 18.5:
        print("waga poniżej normy")
    case _ if 18.5 <= bmi < 25:
        print("norma")
    case _ if 25 <= bmi < 30:
        print("nadwaga")
    case _ if bmi >= 30:
        print("otyłość stopnia I, II lub III")
"""

# zadanie 4

"""wysokosc = int(input("Wpisz wysokość trojkąta \n"))

for i in range(wysokosc):
    for j in range(i+1):
        print("X", end="")
    print("\r")"""

# zadanie 5
"""
lista = [41, 2, 51, 841, 3241, 8412, 8888]
liczba = 41
lista_found = []

for li in lista:
    if str(liczba) in str(li):
        lista_found.append(li)

print(*lista_found, sep=", ", end="\n")
"""

# zadanie 6
"""
lista_catalana = []

liczba_catalana = 1
n = 1

while (liczba_catalana < 1000000):
    lista_catalana.append(liczba_catalana)
    liczba_catalana *= (4*n+2)/(n+2)
    n += 1

even_cnt = 0

for li in lista_catalana:
    if (li % 2 == 0):
        even_cnt += 1

print(even_cnt)
"""

# zadanie 7
"""
lista_2d = [[i for i in range(1, 8, 3)]]*3
print(lista_2d)
"""

# zadanie 8
"""
n = int(input("ile liczb pierwszych? \n"))

lista_liczb_pierwszych = []

liczba_pierwsza = 2

i = 0

while i < n:
    flag = True
    for j in range(2, int(liczba_pierwsza/2) + 1):
        if liczba_pierwsza % j == 0:
            flag = False
            break
    if flag:
        lista_liczb_pierwszych.append(liczba_pierwsza)
        i += 1
    liczba_pierwsza += 1

print(lista_liczb_pierwszych)
"""

# zadanie 9

n = int(input("wpisz liczbe wierszy \n"))

trojkat_pascal = []*n
trojkat_pascal.append([1])
for i in range(n - 1):
    line = [1]
    for j in range(len(trojkat_pascal[i]) - 1):
        line.append(trojkat_pascal[i][j] + trojkat_pascal[i][j+1])
    line.append(1)
    trojkat_pascal.append(line)

for line in trojkat_pascal:
    print(' '.join([str(item) for item in line]).center(int(pow(n, 1.675))))

