%% Problem 3

figure('name', 'Problem 3c 1'); hold on
freqz([1,2,1], 1); % y(n) = x(n) + 2*x(n-1) + x(n-2)
title('Problem 3c 1');
saveas(gcf, 'Problem 3c 1.png');

hold off
figure('name', 'Problem 3c 2'); hold on
freqz(1, [1, -0.9]); % y(n) = -0.9 y(n-1) x(n)
title('Problem 3c 2');
saveas(gcf, 'Problem 3c 2.png');

%% Problem 4 b

time = 2;   % seconds
Fs = [4000 1500];  % Hz

N_samples = Fs.*time; 
n1 = 0:1:(N_samples(1) - 1);
n2 = 0:1:(N_samples(2) - 1);

x1 = cos(2000*pi()./Fs(1)*n1);
x2 = cos(2000*pi()./Fs(2)*n2); 

soundsc(x1, Fs(1));
soundsc(x2, Fs(2));

