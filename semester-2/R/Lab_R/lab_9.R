#zad 1
# Estymację stosujemy, gdy w zadaniu występuje poziom ufności
# Testy stosujemy, gdy w zadaniu występuje poziom istotności
# Struktura testu w skrypcie:
# H0: m = 179 (zawsze równość !!!!)
# H1: m > 179
# instrukcja w R (bez #) t.test(Ankieta.M$Wzrost, mu = 179, alternative = "greater")
# Statystyka testowa: = 2.4676
# p-value = 0.007696
# Wniosek: alfa > p-value, odrzucamy H0 (to znaczy m > 179)
#na poziomie istotnosci 0.05 srednia wzrostu meczyzn w populacji generalnej jest istotnie wieksza niz 179
# Prawdziwą nieznaną średnią w populacji generalnej oznaczamy literą m
# Test dla średniej
t.test(Ankieta.M$Wzrost, mu = 179, alternative = "greater")


# zad2
# a)
# Test zgodności Shapiro-Wilka
shapiro.test(Ankieta.M$Waga)
# Hipoteza zerowa H0: rozkład wagi mężczyzn w pop.gen jest normalny
# Hipoteza alternatywna H1: ~H0
# Statystyka testowa: W = 0.97607
# Poziom istotności (alfa) to prawdopodobieństwo popełnienia błędu w teście,
# polegającego na odrzuceniu hipotezy H0, gdy jest ona prawdziwa
# alfa = 0.01
# p-value to najmniejszy poziom istotności pozwalający odrzucić hipotezę H0,
# wyznaczany na podstawie statystyki testowej
# p-value = 0.07602
# Wniosek: alfa = 0.01 < p, więc brak podstaw do odrzucenia hipotezy H0
# tzn. na poziomie istotności 0.01 różnice między rozkładem normalnym
# a rozkładem empirycznym nie są statystycznie istotne
# Można wyznaczać przedziały ufności i weryfikować hipotezy parametryczne
# dla wzrostu mężczyzn w pop.gen
ggplot(Ankieta.M, aes(x = Waga)) + geom_histogram(aes(y = after_stat(density)), fill = "blue", col = "yellow", binwidth = 10) + 
  stat_function(fun = dnorm, args=list(mean(Ankieta.M$Wzrost), sd(Ankieta.M$Wzrost)), col = "red", linewidth = 1.25) + ylab("Częstość")
#b)
t.test(Ankieta.M$Waga, conf.level = 0.96)
#przedzial liczbowy (71.39718, 76.62991) z prawdopodobieństwem 0.96
# obejmuje prawdziwą nieznaną średnią wzrostu mężczyzn w pop.gen
# Im większy poziom ufności tym szerszy przedział ufności
#c)
przedzial.odchylenie(Ankieta.M$Waga, 0.99)
# Przedział liczbowy (10.35606, 15.08749) na poziomie ufności 0.99
# obejmuje prawdziwe nieznane odchylenie standardowe wagi mężczyzn w pop.gen
#d)
t.test(Ankieta.M$Waga, mu = 77)
# Estymację stosujemy, gdy w zadaniu występuje poziom ufności
# Testy stosujemy, gdy w zadaniu występuje poziom istotności
# Struktura testu w skrypcie:
# H0: m = 77
# H1: m !=77
# instrukcja w R (bez #) t.test(Ankieta.M$Waga, mu = 77) # alternative = "two.sided" jest default
# Statystyka testowa: = -2.3769
# p-value = 0.01946
# alfa = 0.05
# Wniosek: alfa > p-value, odrzucamy H0 (to znaczy m != 77)
#na poziomie istotnosci 0.05 srednia wzrostu meczyzn w populacji generalnej jest różni sie istotnie od 77kg

#zad 3
Przed = c(158, 160, 155, 170, 166, 173, 167, 180, 168, 173)
Po = c(140, 155, 150, 167, 170, 162, 157, 163, 158, 175)
Roznica = Przed - Po
# Będziemy badać wektor różnic między próbami zależnymi
# Test zgodności Shapiro-Wilka (wersja skrócona)
shapiro.test(Przed - Po)
# Hipoteza zerowa H0: rozkład różnic ciśnienia skurczowego w pop.gen jest normalny
# Hipoteza alternatywna H1: ~H0
#alfa = 0.05
#p-value = 0.7159
#alfa < p-value, więc nie ma podstaw po odrzucenia hipotezy H0
# Rozkład różnic ciśnienia nie różni się istotnie od rozkładu normalnego

# Test dla dwóch średnich w próbach zależnych
#H0: m.Przed-m.Po = 0
#H1: m.Przed-m.Po > 0
t.test(Przed-Po, alternative = "greater") # mu = 0 - default
#alfa = 0.05
#p-value = 0.005769
#alfa > p-value, więc odrzucamy hipotezę H0 (tzn. uzycie leku jest skuteczne)
# tzn. na poziomie istotności 0.05 w pop.gen średnia ciśnienia tętniczego przed podaniem 
# leku jest istotnie większa niż po podaniu leku (leczenie jest skuteczne)


#zad 4
table(Ankieta$M.zamieszkania)
# a) 
# Estymacja wskaźnika struktury (odsetka)
prop.test(x = 21, n = 120, conf.level = 0.96)
#przedzial liczbowy (0.1117629, 0.2615617) z prawdopodobieństwem 0.96
# obejmuje prawdziwy nieznany odsetek studentów mieszkających na stacji w pop.gen
# Im większy poziom ufności tym szerszy przedział ufności

#b)
# Prawdziwy nieznany odsetek w pop.gen oznaczamy literą p
# Test dla wskaźnika struktury
# Struktura testu w skrypcie:
# H0: p = 0.4
# H1: ~H0
# instrukcja w R (bez #) t.test(Ankieta.M$Waga, mu = 77) # alternative = "two.sided" jest default
# Statystyka testowa: = 0.70312 (chi^2)
# p-value = 0.4017
# alfa = 0.05
# Wniosek: alfa < p-value, nie ma podstaw do odrzucenia H0 (to znaczy p = 0.4)
#na poziomie istotnosci 0.05 odsetek osób mieszkających w akademiku w populacji generalnej nie różni się istotnie od 0.4
prop.test(x = 43, n = 120, p = 0.4) # alternative = "two.sided" - default

#zad 5
table(Ankieta$Sz.średnia)

prop.test(x = 51, n = 120, conf.level = 0.96)
#przedzial liczbowy (0.3325089, 0.5228095) z prawdopodobieństwem 0.97
# obejmuje prawdziwy nieznany odsetek absolwe na stacji w pop.gen
# Im większy poziom ufności tym szerszy przedział ufności

#b)
prop.test(x = 35, n = 120, p = 0.35, alternative = "less")
# H0: p = 0.35
# H1: p < 0.35
# instrukcja w R (bez #) prop.test(x = 35, n = 120, p = 0.35, alternative = "greater")
# Statystyka testowa: = 1.5476 (chi^2)
# p-value = 0.1067
# alfa = 0.01
# Wniosek: alfa < p-value, nie ma podstaw do odrzucenia H0 (to znaczy p = 0.35)
#na poziomie istotnosci 0.05 odsetek absolwentów technikum informatycznego w populacji generalnej nie jest istotnie mniejszy od 35%