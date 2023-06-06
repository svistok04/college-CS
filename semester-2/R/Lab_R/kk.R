#zad 1
A = matrix(c(9, -17, 12, 4, 9, -2, -8, 12, 4, 15, 1, 13, 8, -12, 10, 2), 4)
B = c(973, -1056, 408, 708)
C = solve(A, B)
det(A)


#zad 2
C = c((12:1188)*3)^3
summary(factor(C %% 18))
summary(factor(C %% 17))
summary(factor(C %% 18 && C %% 17))

#zad 3
dgeom(0, 1/8)
pgeom(7, 1/8)

#zad4
#a
dbinom(8, 5440, 0.001)
dpois(8, 5440*0.001)
dpois(8, 5.44)

#b
pbinom(4, 5440, 0.001, 0)
sum(dbinom(5:5440, 5440, 0.001))
ppois(4, 5.44, 0)
#b CTG
m1 = 5440*0.001
sigma1 = sqrt(5440*0.001*0.999)
pnorm(4.5, m1, sigma1, 0)
pnorm(4, m1, sigma1, 0)


#zad5
#4x>=191 4x<=-145
pnorm(-145/4, 77, 16)+pnorm(191/4, 77, 16, 0)
#|x+36|<144 x < 108 & x > -180
pnorm(108, 77, 16)-pnorm(-180, 77, 16)

#zad 6
#a
qnorm(0.78)
#b
qt(0.7, 93)
#c
qchisq(0.35,9)
#d
qf(0.95, 55, 10)

#zad 7 m2 = 10.1, sigma2 = 1.4
#a n=113 

113*pnorm(10.4, 10.1, 1.4, 0)
qnorm(0.73, 10.1, 1.4)
#zad 8
#m3 = 35 sigma3 = (31.9 - 35)/qnorm((1-0.92)/2)
m3 = 35
sigma3 = (31.9 - 35)/qnorm((1-0.92)/2)
pnorm(38.1, 35, sigma3) - pnorm(31.9, 35, sigma3)
106*pnorm(37.9, 35, sigma3)


