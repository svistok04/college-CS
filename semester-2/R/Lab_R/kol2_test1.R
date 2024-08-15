# zad 1

# 1.1

x =c(18.6, 17.9, 17, 17.3, 18.1, 17.8, 17.3, 17, 17.6, 16.3, 18.7, 17.8, 17.9, 17.1, 17.5, 17.6, 17, 17, 18.3, 17.1)

# a) kwantyl gorny
quantile(x, 0.75)
# Srednia wydajnosc pracy (w szt/h) 75% osob w badanej grupie nie
# przekroczyla 17.9.

# b) wspolczynnik zmienosci
sd(x)/mean(x)
# Udzial odchylenia standardowego wydajnosci pracy w wartosci
# sredniej wynosi 0.0345, co swiadczy o tym, ze
# pracownicy sa slabo zroznicowani pod wzgledem wydajnosci.

# # odchylenie standardowe wzrostu mężczyzn stanowi 3.39 % średniej

# c)

kurtosis(x)

# Rozklad wydajnosci pracy badanych osob charakteryzuje sie
# nizszym skupieniem wokol sredniej wydajnosci niz
# rozklad normalny (k=3).

# d)

skewness(x)

#rozkład wydajnosci pracy jest prawostronnie asymetryczny, gdyż wsp. as. jest dodatni (lewostronnie - negatywny)


# 1.2

# H0: rozklad wydajnosci pracy jest normalny
# H1: ~H1

shapiro.test(x)
# statystyka testowa: W = 0.96382
# p-value = 0.622
# alfa = 0.05
# alfa < p-value, więc brak podstaw do odrzucenia hipotezy H0, tzn.
# na poziomie istotnosci rozkład wydajności pracy w pop.gen. jest normalny


# 1.3

przedzial.odchylenie(x, 0.96)
# przedzial liczbowy o koncach 0.4548486  i 0.9019564 szt/h z
# prawdopodobienstwem 0.96 obejmuje rzeczywista wartosc
# odchylenia standardowego w populacji robotnikow

# 1.4

# H0: m.wydajność = 17.2
# H1: m.wydajność > 17.2

t.test(x, mu = 17.2, alternative='g')
# statystyka testowa: t = 2.5475
# alfa = 0.05
# p-value = 0.009832
# alfa > p-value, więc odrzucamy hipotezę H0 na korzyść H1, tzn.
# średnia wydajność pracy w pop.gen. jest istotniej większa niż 17.2

# 1.5

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

# zalozenie 2: 

# H0: sig^2.T = sig^2.N 
# H1: ~H0
var.test(wydajnosc~szkolenie)
# statystyka testowa: F = 0.56472
# alfa = 0.03
# p-value = 0.4298
# alfa < p-value, więc brak podstaw do odrzucenia hipotezy H0, tzn.
# na poziomie istotnosci 0.05 w pop.gen wariancje wydajności pracy dla robotników po szkoleniu 
# i bez szkolenia nie rożnią się istotnie

# H0: m.T = m.N
# H1: m.T > m.N
t.test(wydajnosc~szkolenie, var.equal = T, alternative='l')
# statystyka testowa: t = -2.0994
# alfa = 0.03
# p-value = 0.02507
# alfa > p-value, więc odrzucamy hipotezę H0, tzn.
# na poziomie istotnści 0.03 w pop.gen. średnia wydajnośći pracy pracowników po szkoleniu jest
# istotnie większa niż osób nieprzeszkolonych

# zad 2

# 2.1

bialko = c(5, 12, 17, 19, 14, 17, 11, 22, 19, 11, 16, 16, 17, 18)

gatunek = c(rep('dorsz', 5), rep('sledz', 5), rep('sandacz', 4))

by(bialko, gatunek, shapiro.test)


# H0: sig.d^2 = sig.sa^2 = sig.sl^2
# H1: ~H0
bartlett.test(bialko~gatunek)
# statystyka testowa: W = 0.94281
# alfa = 0.05
# p-value = 0.04881
# alfa > p-value, odrzucamy na korzyść hipotezy H1, tzn. 
# na poziomie istotności 0.05 w pop.gen. dla wszystkich ganutków wariacje zawartości bialka
# nie są jednorodne

# 2.2

# H0: m.d = m.sa = m.sl
# H1: ~H0
kruskal.test(bialko~gatunek)
# statystyka testowa: chi^2 = 0.6529
# alfa = 0.05
# p-value = 0.7215
# alfa < p-value, nie odrzucamy, więc mediany nie roznią się istotnie i zawartość
# bialka nie zależy od gatunku.

# zad 3 

prop.test(1600, 2500, p=0.65, alternative='l')
# statystyka testowa: chi^2 = 1.0554
# alfa = 0.05
# p-value = 0.1521
# alfa < p-value, więc nie odrzucamy H0, tzn. że na poziomie istotnosci 0.05
# procent udziału w głosowaniu nie różni się istotnie od 65% (0.65)

# zad 4

przed = c(220, 180, 270, 290, 200, 300, 250, 190)

po = c(190, 170, 220, 260, 220, 200, 260, 150)

# 4.1

# H0: rozkład normalny
# H1: ~H0
shapiro.test(przed-po)
# statystyka testowa: W = 0.94844
# alfa = 0.01
# p-value = 0.6955
# alfa < p-value, więc nie odrzucamy, tzn. rozkład jest normalny

# 4.2
# H0: m.przed-m.po = 0
# H1: m.przed-m.po > 0

t.test(przed, po, paired=T, alternative='g')
# t = 2.1637
# alfa = 0.05
# p-value = 0.03362
# alfa > p-value, więc odrzucamy, więc średnia ciśnienia krwi przed podaniem leku jest istotnie
# większa od średnią ciśnienia przed, więc lek działa

# zad 5

wiek = 1:5

waga = c(0.3, 1.2, 2.0, 2.7, 3.8)

# 5.1

cor.test(wiek, waga, conf.level = 0.97)
# Przedział liczbowy (0.9493195, 0.9998877) z prawdopodobieństwem 0.97
# obejmuje prawdziwą nieznany współczynnik korelacji między wiekiem karpia, a go wagą

# 5.2 

lm(waga~wiek)
# y = -0.55+0.85x, gdzie x jest wiekiem
# ze wzrostem wieku o jeden, waga zwiększa się o 0.85

# 5.3

# H0: beta 1 = 0
# H1: ~H0
summary(lm(waga~wiek))
# alfa = 0.01
# statystyka testowa: t = 24.855
# p-value = 0.00142
# alfa > p-value, więc odrzucamy hipotezę H0, tzn. współczynnik regresji w pop.gen. jest istotny (β1 jest różny się 0)

