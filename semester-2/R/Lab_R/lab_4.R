# zad 1
#a)
pnorm(8, 7, 2)-pnorm(5, 7 ,2)
#b) sigma = sqrt(5), Y = (X - m1)/sigma1, gdzie Y = kwantyl od 0.4, a X - 10
sigma1 = sqrt(5)
m1 = 10 - qnorm(0.4)*sigma1
pnorm(8, m1, sigma1) - pnorm(5, m1, sigma1)

# zad 2 qnorm(0.2) = (10 - 15)/sigma2
m2 = 15
sigma2 = round((10-m2)/qnorm(0.2))
qnorm(0.75, m2, sigma2)

# zad 3 m3 = -1, qnorm(1-0.05) = (4 - (-1))/sigma3
m3 = -1
sigma3 = (4 - m3/qnorm(1-0.05))
pnorm(0, m3, sigma3, 0)

# zad 4 m4 - 0.35, qnorm(0.25) = (0.45 - m4)/sigma4
# # 45 - kwantyl rzędu 1-0.25
# m4 = 35
# Y = (X-m4)/sigma4
# qnorm(1-0.25) = (45-m4)/sigma4

m4 = 35
sigma4 = (45 - m4)/qnorm(1-0.25)

#a) # P(X>60) = 1-F(60) = 0.0458763
pnorm(60, m4, sigma4, 0) 

#b)
qnorm(1-0.15, m4, sigma4)
qnorm(0.15, m4, sigma4, 0)

# zad 5 m4 = 165, sigma4 = (155 - m4)/qnorm((1-0.93/2))
m5 = 165
sigma5 = (155 - m5)/qnorm((1-0.93)/2) # since 165 is an average and 175 is upper bound and 155 is lower bound, 
#that is the difference between bounds and the average is the same, so 'kwantyl' of one side (lower than the lower bound 
# or bigger than the upper bound) is (1-0.93)/2
# sigma5 = (175 - m5) / qnorm(0.5 + (0.93/2))
pnorm(175, 165, sigma5) - pnorm(155, 165, sigma5)
round(500*pnorm(170, m5, sigma5, 0)) # 500*P(X>170) = 91

# zad 6 m6 = 4700, qnorm(0.3) = (3000 - 4700)/sigma6
m6 = 4700
sigma6 = (3000-m6)/qnorm(0.3)
qnorm(0.75, m6, sigma6)
