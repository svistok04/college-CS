#zad1
#a)
#ggplot(data.frame(x = c(-4, 4)), aes(x)) + stat_function(fun = dt, args = 1, col = "red", size = 1) + ylab("Gęstość rozkładu dt") +
#ggplot(data.frame(x = c(-4, 4)), aes(x)) + stat_function(fun = dt, args = 2, col = "red", size = 1) + ylab("Gęstość rozkładu dt") +
#ggplot(data.frame(x = c(-4, 4)), aes(x)) + stat_function(fun = dt, args = 10, col = "red", size = 1) + ylab("Gęstość rozkładu dt") +
#ggplot(data.frame(x = c(-4, 4)), aes(x)) + stat_function(fun = dt, args = 50, col = "red", size = 1) + ylab("Gęstość rozkładu dt")

ggplot (data.frame (x = c(-4, 4)), aes (x)) +
  stat_function (fun = dt, args = 1, col = "yellow", size = 1.25) +
  stat_function (fun = dt, args = 2, col = "red", size = 1.25) +
  stat_function (fun = dt, args = 10, col = "brown", size = 1.25) +
  stat_function (fun = dt, args = 50, col = "blue", size = 1.25) +
  stat_function(fun=dnorm,col="black", size=1.25) +
  ylab ("Gęstość rozkładu t Studenta")
# Rozkład t Studenta jest zbieżny do rozkładu normalnego standaryzowanego,
# więc rozkład t Studenta można zastąpić rozkładem normalnym dla dużej próby



#b)
ggplot(data.frame(x = c(- 1, 100)), aes(x)) + 
  stat_function(fun = dchisq, args = 2, col = "red", size = 1.25) + 
  stat_function(fun = dchisq, args = 10, col = "green", size = 1.25) + 
  stat_function(fun = dchisq, args = 20, col = "yellow", size = 1.25) + 
  stat_function(fun = dchisq, args = 50, col = "violet", size = 1.25) + 
  stat_function(fun=dnorm, args=list(50,sqrt(2*50)),col="black",size=1.25) +
  ylab("Gęstość rozkładu chi^2")
# Rozkład chi kwadrat jest zbieżny do rozkładu normalnego,
# więc rozkład chi kwadrat można zastąpić rozkładem normalnym dla dużej próby

#zad2
# Przy uogólnianiu wyników badania próbnego na pop.gen, 
# estymacja i testowanie parametrów wymaga zgodności z rozkładem normalnym

#a)
ggplot(Ankieta.M, aes(x = Wzrost)) + geom_histogram(aes(y = ..density..), fill = "blue", col = "yellow", binwidth = 5) + 
  stat_function(fun = dnorm, args=list(mean(Ankieta.M$Wzrost), sd(Ankieta.M$Wzrost)), col = "red", size = 1.25) + ylab("Częstość")

#b)
#Test zgodności Shapiro-Wilka
# Hipoteza zerowa H0: rozkład wzrostu mężczyzn w pop.gen jest normalny
# Hipoteza alternatywna H1: ~H0
shapiro.test(Ankieta.M$Wzrost) # Statystyka testowa: W = 0.98665 
# Poziom istotności (alfa) to prawdopodobieństwo popełnienia błędu w teście,
# polegającego na odrzuceniu hipotezy H0, gdy jest ona prawdziwa
# alfa = 0.05
# p-value to najmniejszy poziom istotności pozwalający odrzucić hipotezę H0,
# wyznaczany na podstawie statystyki testowej
# p-value = 0.4442
# jeśli alfa >= p, to odrzucamy hipotezę H0 na korzyść hipotezy alternatywnej,
# jeśli alfa < p, to nie ma podstaw do odrzucenia hipotezy H0
# Wniosek: alfa = 0.05 < p, więc nie ma podstaw do odrzucenia hipotezy H0
# tzn. na poziomie istotności 0.05 różnice między rozkładem normalnym
# a rozkładem empirycznym nie są statystycznie istotne
# Można wyznaczać przedziały ufności i weryfikować hipotezy parametryczne
# dla wzrostu mężczyzn w pop.gen

#c)
t.test(Ankieta.M$Wzrost, conf.level = 0.95)
t.test(Ankieta.M$Wzrost, conf.level = 0.98)
t.test(Ankieta.M$Wzrost, conf.level = 0.999999999999999)
# Przedział liczbowy (179.3013, 181.7820) z prawdopodobieństwem 0.95
# obejmuje prawdziwą nieznaną średnią wzrostu mężczyzn w pop.gen
# Im większy poziom ufności tym szerszy przedział ufności

#d)
przedzial.odchylenie=function(zmienna, ufnpoziom) {
  n = length(zmienna)
  alfa = 1 - ufnpoziom
  kwantyl.1 = qchisq(1-alfa/2, n-1)
  kwantyl.2 = qchisq(alfa/2, n-1)
  licznik = (n-1)*var(zmienna)
  data.frame(
    ocena.dolna = sqrt(licznik/kwantyl.1),
    ocena.gorna = sqrt(licznik/kwantyl.2)
    )
}

#e)
przedzial.odchylenie(Ankieta.M$Wzrost, 0.97)
# Przedział liczbowy (5.287252, 7.256975) na poziomie ufności 0.97
# obejmuje prawdziwe nieznane odchylenie standardowe wzrostu mężczyzn w pop.gen

#zad3
shapiro.test(Ankieta$L.godzin)
# Zad3
# Estymację stosujemy, gdy w zadaniu występuje poziom ufności
# Testy stosujemy, gdy w zadaniu występuje poziom istotności


# Struktura testu w skrypcie:
# H0: rozkład liczby godzin spędzanych przed komputerem w pop.gen jest normalny
# H1: ~H0
# instrukcja w R (bez #) shapiro.test(Ankieta$L.godzin)
# Statystyka testowa:=0.94768
# p-value = 0.0001467
# Wniosek: alfa > p-value, więc odrzucamy hipotezę H0
# tzn. na poziomie istotności 0.01 różnice między rozkładem normalnym 
# a rozkładem empirycznym są statystycznie istotne
# Nie można szacować średniej i odchylenia standardowego