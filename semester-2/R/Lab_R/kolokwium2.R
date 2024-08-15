# zad 1

czas = c(11.5, 27.4, 17.9, 5.2, 13.6, 14.2, 14.2, 22.0, 14.9, 19.3, 13.3, 13.3, 10.5, 14.3, 15.2, 24.8, 19.4, 19.5, 24.6, 5.8, 29.4, 29.2, 15.2, 12.4, 22.6)

pora = c('R', 'R', 'R', 'W', 'W', 'W', 'R', 'R', 'W', 'R', 'W', 'W', 'R', 'R', 'W', 'R', 'W', 'R', 'W', 'W', 'R', 'W', 'R', 'R', 'W')

# 1.1

# a)
quantile(czas, 0.75)

# b)
sd(czas)


# c)
IQR(czas)

# 1.2

shapiro.test(czas)

# 1.3

t.test(czas, conf.level=0.95)

# 1.4

t.test(czas, mu = 17.5, alternative = 'l')

# 1.5

by(czas, pora, shapiro.test)

var.test(czas~pora)

# 1.6

t.test(czas~pora, var.equal=T)

# zad 2 

ocena = c(35, 35, 37, 35, 46, 41, 43, 35, 31, 34, 36, 45, 33, 44)

ocena = c(0.35, 0.35, 0.37, 0.35, 0.46, 0.41, 0.43, 0.35, 0.31, 0.34, 0.36, 0.45, 0.33, 0.44)

grupa = c(rep('A', 4), rep('B', 4), rep('C', 6))

# 2.1

bartlett.test(ocena~grupa)

# 2.2

kruskal.test(ocena~grupa)

# zad 3




table(matrix(c(131, 91, 185, 47), nrow=2, ncol=2))

matrix(c(131, 91, 185, 47), 2, 2, byrow=TRUE, dimnames = list(c("w gorach", "nad woda"), c("kobieta", "mezczyzna")))


matrix(c(131,185,91,47), 2)

chisq.test(matrix(c(131,185,91,47), 2))

t.test(c(185/(185+131), 47/(91+47)), conf.level = 0.93)
# zad 4

temperatura = c(18, 17, 15, 25, 23, 20, 19, 21)

ilosc1 = c(2, 1.8, 1.5, 2.5, 2.2, 1.9, 1.8, 2.5)

ilosc2 = c(2.4, 2, 2.5, 2.3, 2.5, 1.8, 2.1, 2.8)

ilosc = c(2, 1.8, 1.5, 2.5, 2.2, 1.9, 1.8, 2.5, 2.4, 2, 2.5, 2.3, 2.5, 1.8, 2.1, 2.8)

miesac = c(rep('CZ', 8), rep('L', 8))

table(ilosc, miesac)

chisq.test(matrix(c(2, 1.8, 1.5, 2.5, 2.2, 1.9, 1.8, 2.5, 2.4, 2, 2.5, 2.3, 2.5, 1.8, 2.1, 2.8), 8, 2)
)
matrix(c(2, 1.8, 1.5, 2.5, 2.2, 1.9, 1.8, 2.5, 2.4, 2, 2.5, 2.3, 2.5, 1.8, 2.1, 2.8), 8, 2)

roznica = ilosc2 - ilosc1

cor.test(ilosc1, temperatura, conf.level = 0.94)

cor.test(ilosc1, temperatura, alternative = 'g')


lm(ilosc~temperatura)

shapiro.test(roznica)

