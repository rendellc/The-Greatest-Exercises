%% Problem 1 -a
N = 100;

t = 1:N;
% Binary noise
n_bin = randi([0 1], size(t));
n_bin(n_bin==0) = -1;

% Gaussian noise
n_gauss = random('norm', 0,1,1, N);

% White uniform noise
n_unif = random('unif', -1,1,1,N);

subplot(3,1,1);
stem(t,n_bin);
title('Binary');

subplot(3,1,2);
stem(t,n_gauss);
title('Gaussian');

subplot(3,1,3);
stem(t,n_unif);
title('Uniform');

%% Problem 1 - d
N = 2000;

t = 1:N;
% Binary noise
n_bin = randi([0 1], size(t));
n_bin(n_bin==0) = -1;

% Gaussian noise
n_gauss = random('norm', 0,1,1, N);

% White uniform noise
n_unif = random('unif', -1,1,1,N);


disp("Mean binary: " + string(mean(n_bin)))
disp("Mean gaussian: " + string(mean(n_gauss)))
disp("Mean uniform: " + string(mean(n_unif)))

ac_bin = xcorr(n_bin);
ac_gauss = xcorr(n_gauss);
ac_unif = xcorr(n_unif);

l = -10:10;

subplot(3,1,1);
%stem(ac_bin);
stem(l,ac_bin(l + N));
title('Auto-corr binary');

subplot(3,1,2);
%stem(ac_gauss);
stem(l,ac_gauss(l + N));
title('Auto-corr Gaussian');

subplot(3,1,3);
%stem(ac_unif);
stem(l, ac_unif(l + N));
title('Auto-corr uniform');

%% Problem 2 - c


N = 20000;
t = 1:N;
l = -10:10;
f = linspace(-0.5, 5, 2*N-1);

w = random('norm', 0, 1, 1, N);

B = [1]; A = [1 1/2];
x = filter(B,A,w);

mean_theory = 0;
autocorr_theory = 2 - (0.5).^l;
psd_theory = 4./(5+4*cos(2*pi*f));
power_theory = 4/3;

mean_est = sum(x)/N;
autocorr_est = xcorr(x)./(2*N);
pds_est = fftshift(abs(fft(autocorr_est)));
power_est = sum(pds_est);

sprintf('Theory');
sprintf('\tMean: ' + string(mean_theory));
sprintf('\tPower: ' + string(power_theory));
sprintf('Estimates');
sprintf('\tMean: ' + string(mean_est));
sprintf('\tPower: ' + string(power_est));

subplot(2,1,1);
stem(l,autocorr_est(l + N));
hold on;
plot(l,autocorr_theory);
title('Autocorrelation');
hold off;

subplot(2,1,2);
stem(f, pds_est);
hold on;
plot(f, psd_theory);
title('Power density spectrum');
hold off;


%% Problem 3 - a


N = 20000;
w = random('norm', 0, 1, 1, N);
B = [1]; A = [1 1/2];
x = filter(B,A,w);
Ks = [20 40 100];

figure();
j = 1;
for K=Ks
    N_means = N/K;
    means = zeros(1,N_means);
    for i=1:(N_means-1)
       mean_est = mean(x(i:(i+K-1)));
       means(i) = mean_est;
    end
    subplot(1, size(Ks,2),j);
    hist(means, 20);
    title('Mean histogram with K = ' + string(K));
    
    j = j + 1;
end

mean_total = mean(x);
var_total = var(x);
sprint('Total estimates');
fprintf('\tMean estimate: ' + string(mean_total) + '\n');
fprintf('\tVariance estimate: ' + string(var_total) + '\n');
    






































