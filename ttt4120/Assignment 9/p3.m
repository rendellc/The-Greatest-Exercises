Bs = [1];
As = [1 sqrt(2) 1];

freqs(Bs,As);
title('Response of Butterworth filter with N=2 and \Omega_c = 1');


n = 0:10;
h1 = 2*sin(0.59*n);
h2 = 2*sin(3.97*n);


B1 = sqrt(2) * [1 -0.83];
A1 = [1 -1.66 1];

B2 = sqrt(2) * [1 0.68];
A2 = [1 1.35 1];


freqz(B1,A1);
title('Response of Discretized filter with \omega_1 = 0.25');
figure();

freqz(B2, A2);
title('Response of Discretized filter with \omega_2 = 1.4');


