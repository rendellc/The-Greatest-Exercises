setwd("C:/Users/rende_000/Dropbox/Skole/Kybernetikk og Robotikk 4/Statistikk/Anbefalt 3")

df <- read.table("data30.txt", 
                 header = FALSE)
hist(df$V1, main = "Histogram of data",
     xlab = "data")

func <- function(x, n){
  if (0<=x && x<1){
      n*x^(n-1)
  } else {
      0
  }
}
par(neq=TRUE)
x <- seq(0, 1, 0.1)
plot(x, func(x, 2), add=TRUE)
