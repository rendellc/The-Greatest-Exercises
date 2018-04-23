N_DSETS = 1000;
N_OUTCOMES = 100;

mu = 5;
sigma = 2; 


avg = zeros(1, N_DSETS);
for i = 1:N_DSETS
    %Xs = normrnd(mu, sigma, 1, N_OUTCOMES);
    Xs = binornd(mu, 0.2, 1, N_OUTCOMES);
    avg(i) = sum(Xs)/length(Xs);
end

normplot(avg);
%hist(avg);