# zad 1
# a)
cor(Ankieta$L.godzin, Ankieta$Wiek) # r = -0.1072855  (współczynnik korelacji z próbki)
# Liczba godzin spędzanych przed komputerem w ciągu doby jest bardzo słabo 
# skorelowana z wiekiem samodzielnego zetknięcia z komputerem

# b)
# Estymacja współczynnika korelacji
cor.test(Ankieta$L.godzin, Ankieta$Wiek, conf.level=0.98)
# Przedział liczbowy (-0.3120102, 0.1069603) z prawdopodobieństwem 0.98
# obejmuje prawdziwą nieznany współczynnik korelacji między liczbą godzin
# przed komputerem w ciągu doby, a wiekiem zetknięcia się z komputerem

# c)
# Prawdziwy współczynnik korelacji liniowej Pearsona w pop.gen oznaczamy ρ (ro)
# Test dla współczynnika korelacji
# H0: ρ = 0  
# H1: ρ < 0
cor.test(Ankieta$L.godzin, Ankieta$Wiek, alternative = 'l')
# statystyka testowa t = -1.1722
# alfa = 0.05
# p-value = 0.1217
# alfa < p-value, wiec brak podstaw do odrzucenia hipotezy H0, tzn.
# wspolczynnik korelacji ρ w pop.gen. nie rozni sie istotnie od 0 (nie jest istotny)

# zad 2
Bez.snu = c(19, 21, 23, 25, 27, 29)
Reakcja = c(0.3, 0.4, 0.5, 0.7, 1.2, 1.5)
#a)
cor(Bez.snu, Reakcja)
# Czas reakcji jest bardzo silnie skorelowany z czasem aktywności bez snu
# b)
cor.test(Bez.snu, Reakcja, conf.level = 0.97)
# Przedział liczbowy (0.5768022 0.9964313) z prawdopodobieństwem 0.97
# obejmuje prawdziwy nieznany współczynnik korelacji między czasem aktywności 
# bez snu a reakcją
# c)
ggplot(data.frame(x = Bez.snu, y = Reakcja), aes (x = Bez.snu, y = Reakcja)) + geom_point (size = 3, col = "red") + geom_smooth (method = "lm", formula = y~x, col = "steelblue")

 #d)
lm(Reakcja~Bez.snu)
# y = -2.1819 + 0.1229x
# jesli czas aktywnosci bez snu zwiekszy sie o 1 godzine, to czas reakcji zwiekszy sie o 0.1229 sekund

# e)
ggplot ( data.frame (x = Bez.snu, y = Reakcja),
         aes (x = Bez.snu, y = Reakcja)) + geom_point (size = 3, col = "deeppink")+ geom_smooth (method = "lm", formula = y~x, col = "steelblue")

# f)
# H0: β1 = 0
# H1: ~H0
summary(lm(Reakcja~Bez.snu))
# statystyka testowa t = 6.609
# p-value = 0.00272
# alfa = 0.03
# alfa > p-value, więc odrzucamy hipotezę H0, tzn. współczynnik regresji w pop.gen. jest istotny (β1 jest różny się 0)

# zad 3
table(Ankieta$M.zamieszkania, Ankieta$Płeć)
# Test niezależności chi^2
# H0: miejsce zamieszkania studentów w pop.gen nie zależy od płci
# H1: ~H0
chisq.test(x = c(7, 12, 5), y = c(36, 44, 16))
chisq.test(Ankieta$M.zamieszkania, Ankieta$Płeć)
# chi^2 = 0.634
# alfa = 0.05
# p-value 0.7283
# alfa < p-value, więc nie ma podstaw do odrzucenia hipotezy H0, 
# tzn. na poziomie istotności 0.05 miejsce zamieszkania studentów w pop.gen
# nie zależy od płci
# Nie ma zależności, więc nie badamy jej siły

# zad 4
chisq.test(matrix(c(45,35,30,25,25,40), 3, 2))
# H0: zadowolenie z wykonywanej pracy w pop.gen nie zależy od wykształcenia
# H1: ~H0
# chi^2 = 6.8783
# alfa = 0.05
# p-value = 0.03209
# alfa > p-value, więc odrzucamy hipotezę H0, tzn. na
# poziomie istotności 0.05 zadowolenie z wykonywanej pracy zależy od wykształcenia

V = sqrt(6.8783/(200)) # współczynnik Cramera 0.1854495 - zależność jest dość słaba
