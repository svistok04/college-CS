# zad 1 n = 35; m = 4700; sigma = 1500; X = X1 + X2 + ... + X35
m1 = 35 * 4700;
sigma1 = sqrt(35)*1500
pnorm(167000, m1, sigma1, 0)

# zad 2 n = 40; m = 44.9; sigma = 0.4;  1800/45 # n = 40 m = 44.9 kg sigma = 0.4 kg
# X = X1+X2+...+X40
m2 = 40 * 44.9;
sigma2 = sqrt(40)*0.4;

pnorm(1800, m2, sigma2) # CTG P(X<1800) = 0.9430769

# zad 3 n = 1000; p = 1-0.515; q = 0.515
#a
sum(dbinom(480:1000, 1000, 1-0.515)) # P(X>=480) = 0.6359685
pbinom(479, 1000, 1-0.515, 0)
#b
1-ppois(480, 1000*0.485) #rozkład Poissona nie, gdyż p=1-0.515 p>0.1
#c CTG 
m3 = 1000 * 0.485 # n*p
sigma3 = sqrt(1000 * 0.485 * 0.515) # sqrt(n*p*q) 
pnorm(479.5, m3, sigma3, 0) # P(X>=480) = (poprawka) P(X>=479.5) = 0.6360826

# zad 4 n = 5000; p = 0.002; 
#a
pbinom(20, 5000, 0.002) - pbinom(5, 5000, 0.002) # F(20) - F(5) 0.9315336
sum(dbinom(6:20, 5000, 0.002))

#b
ppois(20, 5000*0.002) - ppois(5, 5000*0.002) # 0.9313258
sum(dpois(6:20, 5000*0.002))

#c CTG
m4 = 5000*0.002
sigma4 = sqrt(5000*0.002*(1-0.002))

pnorm(20.5, m4, sigma4) - pnorm(5.5, m4, sigma4)
# zad 5

