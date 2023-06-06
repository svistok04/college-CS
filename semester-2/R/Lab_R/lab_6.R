#zad 2 
#a)
summary(Ankieta)

Ankieta$Płeć=factor(Ankieta$Płeć)
Ankieta$M.zamieszkania=factor(Ankieta$M.zamieszkania)
Ankieta$Sz.średnia=factor(Ankieta$Sz.średnia)
Ankieta$System=factor(Ankieta$System)
summary(Ankieta)

#Ankieta=Ankieta[-32,] #usuwanie wiersza nr 32

summary(Ankieta)


#b)
Ankieta$Średnia = (Ankieta$Algebra  + Ankieta$MSzS1 + Ankieta$Narz.inż + Ankieta$Prog1 + Ankieta$WdI) / 5


#c)
Ankieta.kursy = subset(Ankieta, select = Algebra:WdI)

#Ankieta = Ankieta[,-(7:11)]

#d)
zakres3sigm = function(zmienna) {
  lewy.kres = mean(zmienna) - 3*sd(zmienna)
  prawy.kres = mean(zmienna) + 3*sd(zmienna)
  data.frame (lewy.kres, prawy.kres)
}

#e)
zakres3sigm(Ankieta$Średnia)


#f)
Ankieta.M = filter(Ankieta, Płeć == "M")
Ankieta.K = filter(Ankieta, Płeć == "K")

zakres3sigm(Ankieta.K$Wzrost)
zakres3sigm(Ankieta.K$Waga)
zakres3sigm(Ankieta.M$Wzrost)
zakres3sigm(Ankieta.M$Waga)

round(zakres3sigm(Ankieta.K$Średnia), 1)
round(zakres3sigm(Ankieta.M$Średnia), 1)

#h)
Ankieta$L.g.kody = cut(Ankieta$L.godzin, c(0, 4, 8, 24))
