# 1

dawka=1:10/10
przyrost=c(15, 5, 15, 35, 25, 30, 55, 65, 65, 55)
# H0: ro = 0
# H: ro > 0
cor.test(dawka, przyrost, alternative = "greater")
# p-value = 0.0001373
# alfa > p-value, wiec odrzucamy H0, tzn.
# w populacji generalnej wspolczynnik korelacji ... jest istotnie wiekszy od 0



# 2
nawoz = 1:7
przyrost2 = c(8, 13, 14, 17, 18, 20, 22)

plot(nawoz, przyrost2)
cor(nawoz, przyrost2)
# a)
lm(przyrost2~nawoz) # oszacowanie liniowej fukcji regresji
# interpretacja wspolczynnika y = 7.429 + 2.143x
abline(lm(przyrost2~nawoz))
# b)
# H0: zaleznosc jest liniowa
# H1: ~H0
x1 = nawoz
y1 = 7.429 + 2.143*x1
przyrost2 - y1

# c) # zweryfikowac ze wspolczynnik regresji jest istotny
# H0: B1 = 0
# H1: ~H0
summary(lm(przyrost2~nawoz))
# p-value = 0.000114
# alfa > p-value, wiec odrzucamy hipoteze H0, wiec wspolczynnik regresji w pop jest istotny (nie = 0)

# 4)

# dwoe cecju moe,oerza;me = test moza;ezmpsco chi^2
# HO: zadowolenie z pracy nie zalezy od wyksztalczenia

chisq.test(matrix(c(45,35,30,25,25,40), 3, 2))
# chi^2 = 6.8783
# p-value = 0.03209
# alfa 