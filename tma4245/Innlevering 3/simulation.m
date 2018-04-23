%constants 
mu = 498.25;
sigma = 2.67;
nr_days = 300;
nr_tests = 12;
alpha = 0.1;

counter = 0;
for i = 1:nr_days
    x = normrnd(mu, sigma, [1,nr_tests]);
    [mu_L, mu_U] = konfint(x, alpha);
    if (mu_L <= mu && mu <= mu_U)
        counter = counter + 1;
    end
end

counter
counter = counter/nr_days