# zad 2

stezenie = c(0.4, 0.41, 0.56, 0.48, 0.57, 0.55, 0.51, 0.53, 0.54, 0.52, 0.51, 0.6, 0.53)

dzielnice = c(rep('A', 6), rep('B', 4), rep('C', 3))


# 1.1

by(stezenie, dzielnice, shapiro.test)

# H0: sig.A^2 = sig.B^2 = sig.C^2
# H1: ~H0
bartlett.test(stezenie~dzielnice)
# alfa = 0.05 
# p-value = 0.04342
# alfa > p-value, odrzucamy H0, więc wariancje nie są jednorodne

# 1.2

# H0: me.A = me.B = me.C 
# H1: ~H0
kruskal.test(stezenie~dzielnice)
# chi^2 = 0.46961
# p-value = 0.7907
# alfa < p-value, więc nie odrzucamy hipotezę H0, więc na poziomie istotności 0.05 
