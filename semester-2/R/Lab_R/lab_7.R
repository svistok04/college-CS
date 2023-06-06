#zad 1  

parametry.opisowe=function(x) {
  rbind(
    srednie = mean(x),
    kwartyl1.1 = quantile(x, 0.25),
    mediana = median(x),
    kwartyl1.3 = quantile(x, 0.75),
    min = min(x),
    max = max(x),
    rozstep.empiryczny = max(x) - min(x), 
    rozstep.miedzykwartylowy = IQR(x),
    wariancja = var(x),
    odchylenie.standardowe = sd(x),
    wspolczynnik.zmienosci = sd(x)/mean(x),
    wspolczynnik.asymetrii = skewness(x),
    wspolczynnik.skupienia = kurtosis(x)
  )
}


# zad 2
#Waga
#a
parametry.opisowe(Ankieta.M$Waga)
# srednia - średnia waga zbadanych mężczyzn wynosi 74.01 kg
# kwartyl.1 - waga 25% mężczyzn nie przekracza 64.75 kg
# mediana - waga 50% mężczyzn nie przekracza 73.5 kg
# kwartyl.3 - waga 75% mężczyzn nie przekracza 81 kg
# min, max - waga minimalna wynosi 45 kg, a maksymalna 104 kg
# rozstep.empiryczny - waga mężczyzn zmienia się w zakresie 59 kg
# rozstep.miedzykwartylowy - 50% środkowych wartości wagi zmienia się w zakresie 16.25 kg
# wariancja - przeciętne kwadratowe odchylenie wagi mężczyzn od średniej wynosi 151.55 kg^2
# odchylenie.standardowe - przeciętne odchylenie wagi mężczyzn od średniej wynosi 12.31 kg
# wspolczynnik.zmiennosci - odchylenie standardowe wagi mężczyzn stanowi 16.63 % średniej
# wspolczynnik.asymetrii - rozkład wagi mężczyzn jest prawostronnie asymetryczny, gdyż wsp. as. jest dodatni
# wspolczynnik.skupienia - rozkład wagi mężczyzn jest słabiej skupiony wokół średniej niż w rozkładzie normalnym,
# gdyż kurtoza jest mniejsza niż 3

#b
ggplot(Ankieta.M, aes(Waga)) + geom_histogram(fill="black", col="red", binwidth=10) + ylab("histogram")

#c
stem(Ankieta.M$Waga)

#d
ggplot(Ankieta, aes(Płeć, Waga)) + geom_boxplot(fill="blue", color="red")

#Wzrost
#a
parametry.opisowe(Ankieta.M$Wzrost)
# srednia - średni wzrost zbadanych mężczyzn wynosi 180.54 cm
# kwartyl.1 - wzrost 25% mężczyzn nie przekracza 177 cm
# mediana - wzrost 50% mężczyzn nie przekracza 180 cm
# kwartyl.3 - wzrost 75% mężczyzn nie przekracza 185 cm
# min, max - wzrost minimalny wynosi 163 cm, a maksymaly 195 cm
# rozstep.empiryczny - wzrost mężczyzn zmienia się w zakresie 32 cm
# rozstep.miedzykwartylowy - 50% środkowych wartości wzrostu zmienia się w zakresie 8 cm
# wariancja - przeciętne kwadratowe odchylenie wzrostu mężczyzn od średniej wynosi 37.47 cm^2
# odchylenie.standardowe - przeciętne odchylenie wzrostu mężczyzn od średniej wynosi 6.12 cm
# wspolczynnik.zmiennosci - odchylenie standardowe wzrostu mężczyzn stanowi 3.39 % średniej
# wspolczynnik.asymetrii - rozkład wzrostu mężczyzn jest lewostronnie asymetryczny, gdyż wsp. as. jest negatyny
# wspolczynnik.skupienia - rozkład wzrostu mężczyzn jest silnej skupiony wokół średniej niż w rozkładzie normalnym,
# gdyż kurtoza jest większa niż 3

#b
ggplot(Ankieta.M, aes(Wzrost)) + geom_histogram(fill="black", col="red", binwidth=5) + ylab("histogram")

#c
stem(Ankieta.M$Wzrost)

#d
ggplot(Ankieta, aes(Płeć, Wzrost)) + geom_boxplot(fill="blue", color="red")

#zad 3
# (160,170] (170,180] (180,190] (190,200]
#        8         42        42         4
table(cut(Ankieta.M$Wzrost, c(160, 170, 180, 190, 200)))

Wzrost.środki = c(165, 175, 185, 195)
Wzrost.wagi = c(8, 42, 42, 4)

Wzrost.szereg = rep(Wzrost.środki, Wzrost.wagi)
# srednia  179.37500000
# odchylenie.standardowe  7.08036574
mean(Wzrost.szereg)
sd(Wzrost.szereg)
# Parametry nie są takie same

  
# zad 4
#a
parametry.opisowe(Ankieta$Średnia)
# srednia - średnia średnich ocen zbadanych studentow wynosi 3.99 pt
# kwartyl.1 - średnia ocen 25% studentow nie przekracza 3.6 pt
# mediana - średnia ocen 50% studentow nie przekracza 4 pt
# kwartyl.3 - średnia ocen 75% studentow nie przekracza 4.33 pt
# min, max - średnia ocen minimalna wynosi 2.7, a maksymala 5 pt
# rozstep.empiryczny - średnia ocen studentow zmienia się w zakresie 2.3 pt
# rozstep.miedzykwartylowy - 50% środkowych wartości średniej ocen zmienia się w zakresie 0.73 pt
# wariancja - przeciętne kwadratowe odchylenie średniej ocen studentów od średniej wynosi 0.27 puntków^2
# odchylenie.standardowe - przeciętne odchylenie średniej ocen od średniej wynosi 0.52 pt
# wspolczynnik.zmiennosci - odchylenie standardowe średniej ocen stanowi 12.9 % średniej
# wspolczynnik.asymetrii - rozkład średniej ocen jest lewostronnie asymetryczny, gdyż wsp. as. jest ujemny
# wspolczynnik.skupienia - rozkład średniej ocen jest słabiej skupiony wokół średniej niż w rozkładzie normalnym,
# gdyż kurtoza jest mniejsza niż 3

#b
ggplot(Ankieta, aes(Płeć, Średnia)) + geom_boxplot(fill="blue", color="red")
ggplot(Ankieta, aes(M.zamieszkania, Średnia)) + geom_boxplot(fill="blue", color="red")
ggplot(Ankieta, aes(Sz.średnia, Średnia)) + geom_boxplot(fill="blue", color="red")
