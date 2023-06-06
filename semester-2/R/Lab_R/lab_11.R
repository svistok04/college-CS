# Zad1
# Poprawne porównanie średnich w trzech populacjach wymaga sprawdzenia założeń:
# zgodności z rozkładem normalnym w trzech grupach oraz
# jednorodności wariancji

# a)
# Testy zgodności Shapiro-Wilka (wersja skrócona)
by(Ankieta$Średnia, Ankieta$M.zamieszkania, shapiro.test)
# Wniosek: na poziomie istotności 0.01 rozkład średnich ocen we wszystkich trzech 
# miejscach zamieszkania nie różni się istotnie od normalnego
# (założenie można uznać za spełnione)

# b)
# Test Bartletta jednorodności wariancji
# H0: σ^2.A = σ^2.M = σ^2.S
# H1: ~H0 (nie wszystkie równe)
bartlett.test(Ankieta$Średnia~Ankieta$M.zamieszkania)
# p = 0.7606
# alfa = 0.05
# Wniosek: alfa < p-value, więc nie ma podstaw do odrzucenia hipotezy H0, 
# tzn. na poziomie istotności 0.05 w pop.gen wariancje średnich ocen 
# dla wszystkich miejsc zamieszkania nie różnią się istotnie 
# (wariancje są jednorodne)

# c)
# Analiza wariancji ANOVA (porównanie trzech średnich)
# H0: m.A = m.M = m.S
# H1: ~H0
anova(aov(Ankieta$Średnia~Ankieta$M.zamieszkania))
# Statystyka testowa: F = 2.0318 (F value)
# p-value = 0.1357 (Pr(>F))
# alfa = 0.05
# Wniosek: alfa < p, więc nie ma podstaw do odrzucenia hipotezy H0,
# tzn. na poziomie istotności 0.05 w pop.gen średnie średnich ocen
# dla wszystkich miejsc zamieszkania nie różnią się istotnie (średnie są jednorodne),
# tzn. średnia ocen nie zależy od miejsca zamieszkania
TukeyHSD(aov(Ankieta$Średnia~Ankieta$M.zamieszkania))

plot(TukeyHSD(aov(Ankieta$Średnia~Ankieta$M.zamieszkania)))



#Zad2
#a)
Wyniki = c(23, 24, 26, 23, 20, 18, 22, 17, 20, 21, 19, 20, 24, 25, 19, 22, 27, 29)
Metoda = c(rep("A", 7), rep("B", 5), rep("C", 6))
Metoda=rep(c("A","B","C"),c(7,5,6))  # alternatywa
#b)
by(Wyniki, Metoda, shapiro.test)
# Wniosek: na poziomie istotności 0.05 rozkład wyników testu dla wszystkich trzech 
# metod nauczania nie różni się istotnie od normalnego


bartlett.test(Wyniki~Metoda)
# H0: σ^2.A = σ^2.B = σ^2.C
# H1: ~H0 (nie wszystkie równe)
# Statystyka testowa: chi^2=2.5625
# p-value = 0.2777
# Wniosek: alfa = 0.05 < p-value, więc nie ma podstaw do odrzucenia hipotezy H0,
# tzn. na poziomie istotności 0.05 w pop.gen wariancje wyników testu
# dla wszystkich grup metod nie różnią się istotnie
# (wariancje są jednorodne)


## Założenia są spełnione, można zrobić test ANOVA
# H0: m.A = m.B = m.C
# H1: ~H0
anova(aov(Wyniki~Metoda))
# Statystyka testowa: F = 4.379 (F value)
# p-value = 0.03178 (Pr(>F))
# alfa = 0.05
# Wniosek: alfa > p, więc odrzucamy hipotezę H0,
# tzn. na poziomie istotności 0.05 w pop.gen średnie wyników testu
# dla wszystkich metod różnią się istotnie (średnie nie są jednorodne),
# tzn. średnia wyników zależy od metody
plot(TukeyHSD(aov(Wyniki~Metoda)))  # Średnie wyników różnią się istotnie tylko dla metod B i C

# Testy nieparametryczne
# Gdy nie są spełnione wymagane założenia do testów parametrycznych dla średnich,
# należy wykorzystać ich słabsze odpowiedniki nieparametryczne
# Zad3
# Na poziomie istotności 0.01 test Shapiro-Wilka wyklucza zgodność z rozkładem normalnym
# patrz Lab_8 Zad3
# Test Wilcoxona dla mediany (me)
# H0: me = 5
# H1: me > 5
wilcox.test(Ankieta$L.godzin, alternative = "greater")
# Statystyka testowa: V = 5589.5
# p-value = 1.875e-15
# alfa = 0.01
# Wniosek: alfa > p-value, więc odrzucamy hipotezę H0,
# tzn. na poziomie istotności 0.01 w pop.


#Zad4
Poczatek = c(195, 210, 240, 213, 211, 202, 180, 190, 185, 199, 183, 215, 225, 250, 235, 206, 200, 246, 238, 215)
Koniec = c(205, 359, 256, 220, 410, 390, 400, 380, 397, 235, 320, 380, 428, 255, 295, 309, 378, 446, 397, 360)

# Hipoteza zerowa H0: rozkład różnic tempa czytania w pop.gen jest normalny
# Hipoteza alternatywna H1: ~H0
shapiro.test(Poczatek-Koniec)
# p-value = 0.006
# alfa = 0.05
# Wniosek: alfa > p-value, więc odrzucamy hipotezę H0,
# tzn. na poziomie istotności 0.05 rozkład różnic tempa czytania różni się
# istotnie od normalnego

# H0: me.P-me.K = 0
# H1: ~H0
wilcox.test(Poczatek-Koniec, alternative = "less")
# Statystyka testowa: V = 0
# p-value = 9.537e-7
# alfa = 0.05
# Wniosek: alfa > p-value, więc odrzucamy hipotezę H0,
# tzn. na poziomie istotności 0.05 w pop.gen mediana tempa czytania 
# na początku kursu jest istotnie mniejsza niż po jego zakończeniu 
# (uczestnictwo w kursie zwiększa tempo czytania)

#zad5
by(Ankieta$L.godzin,Ankieta$Płeć,shapiro.test)
# H0: liczba godzin w pop.gen kobiet ma rozkład normalny
# H1: ~H0
# Statystyka testowa: = 0.95917
# p-value = 0.005401
# Wniosek: alfa = 0.05 > p, więc odrzucamy hipotezę H0.

# H0: liczba godzin w pop.gen męzczyzn ma rozkład normalny
# H1: ~H0
# Statystyka testowa: = 0.95917
# p-value = 0.001447
# Wniosek: alfa = 0.01 < p, więc odrzucamy hipotezę H0.

#na poziomie istotności 0.05 test Shapiro-Wilka wyklucza zgodność 
# z rozkładem normalnym w obu grupach

# Test Wilcoxona dla dwóch median
# H0: me.K = me.M
# H1: me.K < me.M
wilcox.test(Ankieta$L.godzin~Ankieta$Płeć, alternative="less")
# Statystyka testowa: W = 908.5
# alfa = 0.05
# p-value = 0.0542
# Wniosek: alfa < p-value, więc nie ma podstaw do odrzucenia hipotezy H0,
# tzn. na poziomie istotności 0.05 w pop.gen mediana liczby godzin spędzonych przed komputerem przez kobiet 
# nie różni się istotnie liczby godzin spędzonych przez męzczyzn 
# (liczba godzin nie zależy od płci)

#zad6
# Zad6
# Testy zgodności Shapiro-Wilka (wersja skrócona)
by(Ankieta$L.godzin, Ankieta$M.zamieszkania,shapiro.test)
# akademik - p-value = 0.001246 - nie ma rozkładu norm.
# z rodziną - p-value 0.01126 - nie ma rozkładu norm.
# stancja - p-value = 0.6927 - rozkład norm.
# Wniosek: na poziomie istotności 0.05 test Shapiro-Wilka wyklucza zgodność
# z rozkładem normalnym w grupie studentów mieszkających z rodziną lub w akademiku

# H0: me.A = me.M = me.S
# H1: ~H0
kruskal.test(Ankieta$L.godzin~Ankieta$M.zamieszkania)
# Statystyka testowa: chi^2 = 1.7928
# p-value = 0.408
# alfa = 0.05
# Wniosek: alfa < p, więc nie ma podstaw do odrzucenia hipotezy H0,
# tzn. na poziomie istotności 0.05 w pop.gen mediane liczby godzin spędzonych przed komputerem
# dla wszystkich miejsc zamieszkania nie różnią się istotnie (mediane są jednorodne),
# tzn. liczba godzin nie zależy od miejsca zamieszkania