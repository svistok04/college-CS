# KOLOKWIUM 2

x =c(18.6, 17.9, 17, 17.3, 18.1, 17.8, 17.3, 17, 17.6, 16.3, 18.7, 17.8, 17.9, 17.1, 17.5, 17.6, 17, 17, 18.3, 17.1)


# ZAD 1.1


  p.opisowe(x)

# a) kwartyl gorny:

# Srednia wydajnosc pracy (w szt/h) 75% osob w badanej grupie nie
# przekroczyla 17.9.


# b) wspolczynnik zmiennosci: 

# Udzial odchylenia standardowego wydajnosci pracy w wartosci
# sredniej wynosi 0.0345, co swiadczy o tym, ze
# pracownicy sa slabo zroznicowani pod wzgledem wydajnosci.
  


# c) kurtoza:

# Rozklad wydajnosci pracy badanych osob charakteryzuje sie
# nizszym skupieniem wokol sredniej wydajnosci niz
# rozklad normalny.
  


# ZAD 1.2


# H0: rozklad wydajnosci pracy jest normalny
# H1: ~H0

shapiro.test(x)

# stat. testowa W = 0.96382
# p-value = 0.6227
# alfa = 0.05

# Wniosek: alfa < p-value
# Alfa mniejsze od p-value, wiec nie ma podstaw do
# odrzucenia hipotezy H0, ze roklad wydajnosci pracy w populacji
# robotnikow jest zgodny z rozkladem normalnym


# ZAD 1.3


przedzial.odchylenie(x, 0.96)
# 0.4548486    0.9019564

# przedzial liczbowy o koncach 0.4548486  i 0.9019564 szt/h z
# prawdopodobienstwem 0.95 obejmuje rzeczywista wartosc
# odchylenia standardowego w populacji robotnikow


# ZAD 1.4


# H0: m = 17.2
# H1: m > 17.2
t.test(x, mu = 17.2, alternative = 'g')

# stat.testowa t = 2.5475
# p-value = 0.009832
# alfa = 0.05

# Wniosek: alfa > p-value,
# Alfa wieksze niz p, wiec odrzucamy hipoteze H0, zatem srednia
# wydajnosc w populacji pracownikow jest wieksza niz 17.2 szt/h


# ZAD 1.5


wydajnosc = c(18.6, 17.9, 17, 17.3, 18.1, 17.8, 17.3, 17, 17.6, 16.3, 18.7, 17.8, 17.9, 17.1, 17.5, 17.6, 17, 17, 18.3, 17.1)

szkolenie = c('T', 'T', 'T', 'N', 'T', 'N', 'N', 'T', 'T', 'N', 'T', 'N', 'T' , 'N', 'T', 'N', 'N', 'T', 'T', 'N' )


# zalozenie 1: normalnosc rozkladow
# H0: rozklad wydajnosci pracy w populacji robotnikow po szkoleniu jest normalny,
# H1: ~H0
# H0': rozklad wydajnosci pracy w populacji robotnikow bez szkolenia jest normalny,
# H1': ~H0'

by(wydajnosc, szkolenie, shapiro.test)
# T: W = 0.91959, p-value = 0.3153
# N: W = 0.91201, p-value = 0.3302

# alfa = 0.03
# Wniosek: Na poziomie instotnosci 0.03 nie ma podstaw do 
# odrzucenia hipotez H0, H0' o normalnosci rozkladow
# wydajnosci pracy w populacji robotnikow po szkoleniu i bez szkolenia


# zalozenie 2: jednorodnosc wariancji
# H0: (sig.T)^2 = (sig.N)^2
# H1: ~H0

var.test(wydajnosc~szkolenie)

# Stat.testowa F = 0.56472
# p-value = 0.4298
# alfa = 0.03
# Wniosek: Brak podstaw do odrzucenia hipotezy o
# jednorosci wariacji wydajnosci pracy w populacji robotnikow
# po szkoleniu i bez szkolenia


# ZAD 1.6


# test studenta dla 2 srednich
# H0: m.N = m.T
# H1: m.N < m.T

t.test(wydajnosc~szkolenie, var.equal=T, alternative = 'l')
# stat.testowa t = -2.0994
# p-value = 0.02507

# alfa = 0.03
# Wniosek : Odrzucamy H0 i przyjmujemy H1, zatem wyniki
# proby potwierdzaja przypuszczenie, ze na poziomie
# istotnosci 0.03 srednia wydajnosc pracy robotnikow po szkoleniu
# jest wyzsza niz nieprzeszkolonych.


# ZAD 2.1


# zmienna mierzalna
bialko = c(5, 12, 17, 19, 14, 17, 11, 22, 19, 11, 16, 16, 17, 18)

# zmienna grupujaca
gatunek = c(rep('dorsz', 5), rep('sledz', 5), rep('sandacz', 4))


# H0: sig1^2 = sig2^2 = sig3^2
# H1: ~H0

bartlett.test(bialko~gatunek)

# Stat. testowa chi^2 = 6.0398
# p-value = 0.04881
# alfa = 0.05

# Wniosek: Na poziomie istotnosci 0.05 odrzucamy hipoteze H0, na rzecz H1.
# Wariancje roznych gatunkow ryb nie sa jednorodne.


# ZAD 2.2


# H0: me1=me2=me3
# H1: ~H0

kruskal.test(bialko~gatunek)

# stat. testowa: chi^2 = 0.6529, p-value = 0.7215
# alfa = 0.05
# Wniosek: Brak podstaw do odrzucenia H0. Zawartosc bialka nie zalezy
# od gatunku.


# ZAD 3


# H0: p = 65%
# H1: p < 65%

prop.test(1600,2500, p = 0.65, alternative = 'l')
# Stat.testowa chi^2 = 1.0554
# p-value 0.1521
# alfa = 0.05

# Wniosek: Brak podstaw do odrzucenia H0. Na poziomie
# istotnosci 0.05, 65% ogolu osob, lub wiecej zamierza wziac
# udzial w wyborach do samorzadu.


# ZAD 4.1


x = c(220, 180, 270, 290, 200, 300, 250, 190)
y = c(190, 170, 220, 260, 220, 200, 260, 150)

# H0: rozklad roznicy zmiennych jest normalny,
# H1: ~H0

shapiro.test(x-y)
# Stat. testowa W = 0.94844
# p-value = 0.6955
# alfa = 0.01

# Wniosek: Brak podstaw do odrzucenia H0.
# Wyniki sa rozkladu normalnego


# ZAD 4.2


# H0: m1 - m2 = 0
# H1: m1 - m2 > 0

t.test(x,y,paired = T, alternative = 'g')
# Stat.testowa t = 2.1637
# p-value = 0.03362
# alfa = 0.05

# Wniosek: Odrzucamy H0 i przyjmujemy H1. Lek powoduje
# spadek cisnienia u pacjentow na poziomie istotnosci 0.05.


# ZAD 5.1


# wiek w latach
x = c(1, 2, 3, 4, 5)
# waga w kg
y = c(0.3, 1.2, 2.0, 2.7, 3.8)

cor.test(x, y, conf.level = 0.97)

# Przedzial o koncach 0.9493195 i 0.9998877 z prawdopodobienstwem 0.97 obejmuje wspolczynnik korelacji w populacji miedzy wiekiem, a waga.


# ZAD 5.2

lm(y~x)

# oszacowana liniowa funkcja regresji ma postac:
# y = -0.55 + 0.85x

# Interpetacja wspolczynnika regresji:
# Wspolczynnik regresji rowny 0.85 oznacza, ze ze wzrostem wieku o rok,
# waga zwieksza sie srednio o 0.85 kg.


# ZAD 5.3


# H0: beta1 = 0 (nieistotny)
# H1: ~H0 (istotny)

summary(lm(y~x))

# t value i Pr(>|t|) dla x na summary
# stat. testowa t = 24.885
# p-value = 0.000142

# alfa = 0.01
# Odrzucamy hipoteze H0 o przyjmujemy H1. Na poziomie istotnosci 0.01 mozna stwierdzic,
# ze wspolczynnik regresji miedzy wiekiem, a waga karpia jest istotny.