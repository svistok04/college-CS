#Zad1
# Poprawne porównanie średnich w dwóch populacjach wymaga sprawdzenia założeń:
# zgodności z rozkładem normalnym w obu populacjach oraz jednorodności wariancji
# (założenia obejmują trzy testy istotności)

# a)
# Testy zgodności Shapiro-Wilka
by(Ankieta$Waga,Ankieta$Płeć,shapiro.test)
# H0: waga w pop.gen kobiet ma rozkład normalny
# H1: ~H0
# Statystyka testowa: = 0.95917
# p-value = 0.4221
# Wniosek: alfa = 0.01 < p, więc nie ma podstaw do odrzucenia hipotezy H0,
# tzn. na poziomie istotności 0.01 różnice między rozkładem normalnym a rozkładem empirycznym
# nie są statystycznie istotne, założenie można uznać za spełnione

#b)
# Prawdziwe odchylenie standardowe w pop.gen oznaczamy σ
# Test Fishera jednorodności wariancji
# H0: σ^2.K = σ^2.M
# H1: ~H0
var.test(Ankieta$Waga~Ankieta$Płeć)
var.test(Waga~Płeć,Ankieta)   # alternatywa
var.test(data=Ankieta,Waga~Płeć)   # alternatywa
# Statystyka testowa: F = 0.57434
# p-value = 0.1294
#alfa < p-value, nie ma podstaw do odrzucenia H0, tzn. na poziomie istotności 0.05 w pop.gen wariancje wag dla obu płci
#nie różnią się istotnie (wariancje są jednorodne)

#c)
# Test dla dwóch średnich
# H0: m.K = m.M
# H1: m.K < m.M
t.test(Waga~Płeć, Ankieta, alternative = "less", var.equal = TRUE)
# Statystyka testowa: t = -5.5803
# p-value = 7.77e-08
# alfa > p-value, więc odrzucamy hipotezę H0, tzn. na poziomie istostności 0.05 w pop.gen. średnia wagi w grupie kobiet
# jest istotnie mniejsza niż średnia wagi w grupie mężczyzn

#zad2
#H0: m.K = m.M
#H1: ~H0
#założenia
# 1) Testy zgodności Shapiro-Wilka
by(Ankieta$Średnia,Ankieta$Płeć,shapiro.test)
# Hipoteza zerowa H0: rozkład średniej oceny mężczyzn w pop.gen jest normalny
# Hipoteza alternatywna H1: ~H0
# Statystyka testowa: W = 0.98637
# Poziom istotności (alfa) to prawdopodobieństwo popełnienia błędu w teście,
# polegającego na odrzuceniu hipotezy H0, gdy jest ona prawdziwa
# alfa = 0.05
# p-value to najmniejszy poziom istotności pozwalający odrzucić hipotezę H0,
# wyznaczany na podstawie statystyki testowej
# p-value = 0.4261
# Wniosek: alfa = 0.05 < p, więc brak podstaw do odrzucenia hipotezy H0
# tzn. na poziomie istotności 0.01 różnice między rozkładem normalnym
# a rozkładem empirycznym nie są statystycznie istotne
# Można wyznaczać przedziały ufności i weryfikować hipotezy parametryczne
# dla wzrostu mężczyzn w pop.gen
# 2)
# Test Fishera jednorodności wariancji
var.test(Średnia~Płeć,Ankieta)
# H0: σ^2.K = σ^2.M
# H1: ~H0
# Statystyka testowa: F = 1.3253
# p-value = 0.3453
#alfa < p-value, nie ma podstaw do odrzucenia H0, tzn. na poziomie istotności 0.05 w pop.gen wariancje średniej oceny dla obu płci
#nie różnią się istotnie (wariancje są jednorodne)

#3)
## Założenia są spełnione, można zrobić test t bez poprawki Welcha
# Test dla dwóch średnich
t.test(Średnia~Płeć, Ankieta, var.equal = TRUE)
# Statystyka testowa: t = 0.37918
# p-value = 0.7052
# H0: m.K = m.M
# H1: ~H0
# alfa < p-value, więc nie ma podstaw do odrzucenia hipotezy H0, tzn. na poziomie istostności 0.05 w pop.gen 
#średnia ocen nie różni się istotnie i nie jest zależna od płci

#zad3
#1)
by(Ankieta.M$L.godzin, Ankieta.M$System, shapiro.test)
# Hipoteza zerowa H0: rozkład liczby godzin spędzonych przed komputerem w pop.gen mężczyzn preferujących system 
#Windows jest normalny
# Hipoteza alternatywna H1: ~H0
# Statystyka testowa: W = 0.968
# alfa = 0.03
# p-value = 0.0.3462
# alfa = 0.03 < p, więc brak podstaw do odrzucenia hipotezy H0
# tzn. na poziomie istotności 0.03 różnice między rozkładem normalnym a rozkładem empirycznym
# nie są statystycznie istotne, założenie można uznać za spełnione
# (wariancje nie są jednorodne)
#2)
# Test Fishera jednorodności wariancji
var.test(L.godzin~System,Ankieta.M)
# H0: σ^2.K = σ^2.M
# H1: ~H0
# Statystyka testowa: F = 2.3554
# p-value = 0.02785
# alfa = 0.03
#alfa > p-value, więc odrzucamy hipotezę H0, tzn. na poziomie istotności 0.03 w pop.gen męzczyzn wariancje liczby godzin 
#spędzonych przed komputerem zgodnie z preferowanym systemem różnią się istotnie
#3)## Założenia są spełnione, można zrobić test t z poprawką Welcha
# Test dla dwóch średnich
t.test(L.godzin~System, Ankieta.M, alternative = "greater")
# H0: m.K = m.M
# H1: m.Inny > m.Windows
# Statystyka testowa: t = 1.5506
# p-value = 0.0731
# alfa = 0.03
# alfa < p-value, więc nie ma podstaw do odrzucenia hipotezy H0, tzn. na poziomie istostności 0.03 w pop.gen męzczyzn
# liczba godzin spędzonych przed komputerem nie różni się istotnie w zależności od systemu preferowanego

#zad4
# Test dla dwóch wskaźników struktury (nie wymaga żadnych założeń)
table(Ankieta$M.zamieszkania, Ankieta$Sz.średnia)
# H0: p.MZR = p.Poz
# H1: p.MZR > p.Poz
prop.test(x = c(29, 22), n = c(56, 64), alternative = "greater", conf.level = 0.95)
# chi^2=3.0266
# p-value = 0.04096
# Wniosek: alfa = 0.05 >= p, więc odrzucamy hipotezę H0 na korzyść hipotezy alternatywnej,
# tzn. na poziomie istotności 0.05 w pop.gen odsetek absolwentów LO (RM) 
# w grupie mieszkających z rodziną jest istotnie większy od 
# odsetka absolwentów LO (RM) w grupie mieszkających w akademiku lub na stancji

#zad5
table(Ankieta$M.zamieszkania, Ankieta$Płeć)
prop.test(x = c(7, 36), n = c(24, 96), alternative = "less")
# H0: p.K.akademi = p.M.akademik
# H1: p.K.akademik < pk.M.akademik
# chi^2=0.27409
# p-value = 0.3003
# alfa = 0.02
# Wniosek: alfa < p-value, więc brak podstaw do odrzucenia hipotezy H0,
# tzn. na poziomie istotności 0.02 w pop.gen odsetek kobiet mieskających 
# w akademiku nie rożni się istotnie od odsetku męzczyzn mieskających w akademiku