#zad 1
#0, 1, 2, 3, 4, 5  osob nie zrobily zadania
rozklad2=rbind(c(0:5), c(dbinom(0:5, 5, 3/7)))

sum(dbinom(0:5,5,3/7))

pi=dbinom(0:5,5,3/7)
rozklad=rbind(xi=0:5,pi)
#zad 2
dbinom(2, 3, 1/7) # P(X=2) = 0.05247813


#zad 3
dgeom(5, 0.003) #P(X=5)=0.002955269


#zad 4
#a)
dbinom(3, 300, 0.002) #(P=3) = 0.0.0196661
dpois(3, 300*0.002) # 0.01975722
#b)
pbinom(3, 300, 0.002) # F(3) F - dystrybuanta
sum(dbinom(0:3, 300, 0.002)) # P(X<=3) = 0.9966893

sum(dpois(0:3, 300*0.002)) # 0.9966419
ppois(3, 300*0.002) # 0.9966419
#zad 5
1-(sum(dbinom(0:3, 600, 0.004))) # 0.2210252
sum(dbinom(4:600, 600, 0.004)) #0.2210252
1-pbinom(3,  600, 0.004) # 0.2210252
pbinom(3, 600, 0.004, 0) # 0.2210252

#zad 6
pgeom(4, 1/8, 0) # 0.5129089


#zad 7
pbinom(1, 650, 0.003, 0) # 0.5806874 P(X>1)
1-pbinom(1, 650, 0.003) # 0.5806874 1-F(1) = 1-P(X<=1)
1-(sum(dbinom(0:1, 650, 0.003))) # 0.5806874
sum(dbinom(2:650,650,0.003)) # P(X>=2) = 0.5806874
#zad 8
#a)
dgeom(2, 1/9) # P(X=2) = 0.0877915
#b) P(1=<X=<6) = F(6) - F(0)
pgeom(6, 1/9) - pgeom(0, 1/9) # F(6)-F(0) = P(X<=6)-P(X<=0)


sum(dgeom(1:6, 1/9)) # P(1<=X<=6) = 0.4504265
#zad 9 (85; 115), 0.12
sum(dbinom(86:114, 1000, 0.12)) # P(85<X<115) = 0.2990923

pbinom(114,1000,0.12) - pbinom(85,1000,0.12) # F(114)-F(85) = P(X<=114)-P(X<=85)