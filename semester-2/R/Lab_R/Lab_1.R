# Ctrl L czyści konsolę
# Ctrl Enter = Run
#zad1
#a)
4*(5^2)+log(30,3)
#b)
7^(1/5)
#c)
(6^(1/7))^(1/3)
#zad2
#macierz A
#matrix()
A=matrix(c(3, 4, 2, 1, -1, 0), 2, 3)
#cbind
cbind(c(3, 4), c(2, 1), c(-1, 0))
#rbind
rbind(c(3, 2, -1), c(4, 1, 0))
#macierz B
#matrix()
B=matrix(c(7, -11, 3, 2, -6, -2, 12, 1, 3), 3)
#a)
det(B)
#b)
solve(B)
#c)
t(A)
t(B)
det(t(B))
#d)
B %*% B
A %*% B
#e)
sum(A[1,]) * sum(B[,2])
sum(A[1,] * B[,2])
#zad3
C=matrix(c(2, 3, 1, 4, 4, -2, 3, -3, -3, 8, 2, -5, 1, -11, 5, -3), 4)
D=c(71, -20, 26, 49)
solve(C, D)

#zad4 kolokwium
E=(1:80)^2
factor(E %% 10)
summary(E %% 10)
summary(factor(E %% 10))

#zad5
stopni=seq(30, 60, by = 5)
rad <- function(stopien) {
  stopien * pi / 180
}


tablica.data <- data.frame(
  stopni,
  sin = sin(rad(stopni)),
  cos = cos(rad(stopni)),
  tan = tan(rad(stopni)),
  cot = 1/tan(rad(stopni))
)

#zad6
litery = rep(c("X", "Y", "Z"), 13)
liczby = 1:40
noquote(paste(litery, liczby, sep = "."))
