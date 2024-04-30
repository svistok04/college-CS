import math

# zadanie 7
"""
imie = input("Jak masz na imie? ")
kierunek = input("Na jakim kierunku studiujesz? ")
rok = int(input("Na jakim roku jesteś? "))
srednia = float(input("Jaką srednią uzyskaleś w poprzednim semestrze? "))
print('Witaj', imie)
print("Twój kierunek: {} \nTwój rok studiów: {} \nTwoja średnia w poprzednim semestrze: {} ".format(kierunek, rok,
                                                                                                    srednia))
"""
# zadanie 8
"""
adres = input("Pod jakim adresem zamieszujesz? ")
kod = input("Jaki jest Twój kod pocztowy? ")
miasto = input("W jakim miescie zamieszkujesz? ")
print(adres, kod, miasto, sep=", ", end=". \n")
print(adres, ",", kod, ",", miasto, ".")
"""
# zadanie 9
"""
wzrost_cm = int(input("Podaj swój wzrost (w centymetrach): "))
waga_g = int(input("Podaj swoją wagę (w gramach): "))
wzrost_m = float(wzrost_cm)/100
waga_kg = float(waga_g)/1000
bmi = waga_kg / pow(wzrost_m, 2)
print("Twój wzrost w metrach: {:.2f}; \nTwoja waga w kilogramach: {:.2f}; \nTwój wskaźnik BMI: {:.2f}."
      .format(wzrost_m, waga_kg, bmi))
"""
# zadanie 10
"""
liczba1 = int(input("Podaj liczbę: "))
print("Podana liczba jest większa od 10 i jednocześnie mniejsza od 20:", 10 < liczba1 < 20)
liczba2 = int(input("Podaj liczbę: "))
print("Podana liczba jest mniejsza od 0 lub większa od 20:", 0 > liczba2 or liczba2 > 20)
"""
# zadanie 11

x = float(input("Podaj zmienną x: "))
y = float(input("Podaj zmienną y: "))

wynik = math.e + math.log(pow(x, 2) + 1, 10)*(x-1)/(math.cos(pow(y, 3) - 1) + 6)
print(wynik)  # dla x = 2, y = 4 wynosi 2.8183362733213935; dla x = -9.5, y = 6.4 wynosi -1.3367487551407415



