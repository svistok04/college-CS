#Zad1
# xp - kwantyl rzędu p wtedy i tylko wtedy gdy F(xp)=p
#a) rozkład normalny N(0,1)
ggplot(data.frame(x=c(-5,5)), aes(x))+
  stat_function(fun=dnorm,col="blue",size=1.25)+
  ylab("Gęstość rozkładu normalnego N(0,1)")
#u~N(0,1)

#a)
qnorm(0.98)

#b)
qt(0.95,18)

#b)
ggplot(data.frame(x=c(-5,5)), aes(x))+
stat_function(fun=dt,args=list(df=18),col="green",size=1.25)+
ylab("Gęstość rozkładu t Studenta")

#c)
ggplot(data.frame(x=c(-2,75)), aes(x))+
  stat_function(fun=dchisq,args=list(df=23),col="red",size=1.25)+
  ylab("Gęstość rozkładu chi kwadrat")
#lub c)
qchisq(0.975, 23)

#d)
ggplot(data.frame(x=c(-2,7)), aes(x))+
  stat_function(fun=df,args=list(df1=5,df2=24),col="brown",size=1.25)+
  ylab("Gęstość rozkładu Fishera")

#lub d)
qf(0.99, 5, 24)


#zad 2 kolowkium 2 przyklady z wartoscia bezwzlgl
# N(3,6)
ggplot(data.frame(x=c(-25,25)), aes(x))+
  stat_function(fun=dnorm,args=list(mean=3,sd=6),col="blue",size=1.25)+
  ylab("Gęstość rozkładu normalnego N(3,6)")

#a)
pnorm(5, 3, 6)

#b)
pnorm(4, 3, 6, 0)
1-pnorm(4, 3, 6)

#c)
pnorm(1, 3, 6)-pnorm(-1, 3, 6)
1-pnorm(1, 3, 6, 0)-pnorm(-1, 3, 6)

#d) |x-4|=<0.5 <--> 3.5=<x=<4.5
pnorm(4.5, 3, 6)-pnorm(3.5, 3, 6)

#e) |3x-8|<1 <--> 7/3<x<3
pnorm(3, 3, 6)-pnorm(7/3, 3, 6)

#f) |x+1|>=7 <--> x<=-8 i x>=6 
pnorm(-8, 3, 6)+pnorm(6, 3, 6, 0)

#g) |2x-3|>4 <--> x<=-1/2 i x>=7/2
pnorm(-0.5, 3, 6)+pnorm(3.5, 3, 6, 0)

#zad 3 N(200, 10), P(x<175), 10000 zarowek
round(10000*pnorm(175, 200, 10))

#zad 4 N(2.25, 0.2) 

#a) P(x>2.3), 40 zawodnikow
40*pnorm(2.3, 2.25, 0.2, 0)

#b) wynik ponizej ktorego jest 20% najgor qnorm(prawdopodobienstwo, m, n)
qnorm(0.2, 2.25, 0.2)

#zad 5 N(13, 18)
#a) P(15<x<20)
pnorm(20, 13, 18)-pnorm(15, 13, 18)
1-pnorm(20, 13, 18)-pnorm(15, 13, 18, 0)

#b) P(x>25)
pnorm(25, 13, 18, 0)
#zad 6
ggplot(data.frame(x=c(-25,75)), aes(x))+
  stat_function(fun=dnorm,args=list(mean=25,sd=8),col="blue",size=1.25)+
  ylab("Gęstość rozkładu normalnego N(25,8)")
 
#N(25, 8)
# P(X<k1) = 0.5987   k1-kwantyl rzędu 0.5987
qnorm(0.5987, 25, 8)

# P(X>k2) = 0.734   k2-kwantyl rzędu 0.734
qnorm(0.734, 25, 8, 0)
qnorm(1-0.734, 25, 8)

#c) P(|x|<k3)=0.468
(qnorm(0.5+0.468/2, 25, 8)+qnorm(0.5-0.468/2, 25, 8, 0))/2-qnorm(0.5+0.468, 25, 8, 0)-qnorm(0.5-0.468, 25, 8)

#c)
# P(25-k3<X<25+k3) = 0.468
# P(X<25-k3) = (1-0.468)/2  25-k3 - kwantyl rzędu (1-0.468)/2
qnorm((1-0.468)/2,25,8)   # = 20.00035 = 20
25-qnorm((1-0.468)/2,25,8) # = k3 = 5


#d) P(|x|>k4)=0.617

25-qnorm((0.617)/2, 25, 8)

