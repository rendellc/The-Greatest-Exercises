close all;
N = 1e5;
theta = 8;

f_T = @(t) theta./((t + theta).^2);

lambda = exprnd(repmat(theta, 1, N)); 
T = exprnd(lambda);

histogram(T, 'Normalization', 'probability');
hold on
title('T variable distribution');
xlabel('t');

dt = 0.01;
t = 0:dt:max(T);
plot(t, f_T(t));

