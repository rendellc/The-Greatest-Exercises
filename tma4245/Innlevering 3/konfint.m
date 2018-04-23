function [mu_L, mu_U] = konfint(x, alpha)
    n = length(x);
    xbar = mean(x);
    s = std(x);
    tq = icdf('t', 1-alpha/2, n-1);
    mu_L = xbar - tq*s/sqrt(n);
    mu_U = xbar + tq*s/sqrt(n);
end