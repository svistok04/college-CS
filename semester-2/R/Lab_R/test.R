homicideRate = c(15.8, 11.8, 10.6, 10.6, 10.5, 9.6, 9.6, 9.1, 9.1, 8.8, 8.0, 7.9, 7.8, 7.6, 7.5, 7.4, 7.4, 7.2, 7.0, 6.9, 6.7, 6.6, 6.6, 6.1, 5.9, 5.7, 5.6, 5.3, 5.1, 5.0, 4.5, 4.2, 4.2, 3.9, 3.9, 3.7, 3.6, 3.5, 3.4, 3.4, 3.1, 3.1, 3.0, 2.9, 2.9, 2.3, 2.2, 2.2, 1.6, 0.9)
gunOwnership = c(53, 49, 55, 57, 50, 55, 52, 28, 30, 49, 46, 40, 46, 40, 44, 34, 55, 55, 40, 46, 64.5, 58.5, 46, 44, 35, 47, 28, 45, 45, 66, 55, 20, 55, 24, 42, 15, 45, 44, 57, 43, 47, 66, 15, 15, 51, 50 ,15, 60, 47, 40)

cov(homicideRate, gunOwnership, use = "everything",
    method = c("pearson", "kendall", "spearman"))

cor(homicideRate, gunOwnership)

plot(homicideRate, gunOwnership)


cor.test(homicideRate, gunOwnership)