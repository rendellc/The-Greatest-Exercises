df = load('data30.txt');

fx = @(x, n) n*x.^(n-1);

hist(df);
hold on;

xs = 0:0.1:1;
plot(xs, fx(xs, 2));

figure;
F_hat = ecdf(df);
plot(xs, F_hat);
