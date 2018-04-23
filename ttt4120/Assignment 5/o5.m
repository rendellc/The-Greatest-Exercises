%% Problem 1
close all
clear
clc

n = 0:50;
N_FFT = power(2, 2*ceil(log2(size(n,2)))); %2 times smallest power of 2 greater than size(n,2)
l = -n(end):n(end);
as = [0.5 0.9 -0.9]';


%computation
%x(n)
M = size(as,1);
ns = repmat(n,M,1);
xs = as.^n;

%rxx(l)
%rxxs = abs(ifft(fft(xs, N_FFT,2).*fft(fliplr(xs), N_FFT,2)));
%rxxs = conv2(fliplr(xs),xs,'same'); 
rxxs = zeros(M,size(l,2));
for i=1:M
    rxxs(i,:) = conv(xs(i,:), fliplr(xs(i,:)));
end

%Sxx(w)
L = size(l,2)-1;
Sxxs = abs(fftshift(fft(rxxs, N_FFT, 2))/L);

%plotting
as_legend = "a = " + string(as');
f = linspace(-0.5, 0.5, size(Sxxs,2));

figure();
plot(n, xs);
title("x[n]"); xlabel("n"); ylabel("x[n]"); legend(as_legend);

figure();
plot(l, rxxs);
title("r_{xx}[l]"); xlabel("l"); ylabel("r_{xx}[l]"); legend(as_legend);

figure();
plot(f, Sxxs);
title("S_{xx}(f)"); xlabel("f"); ylabel("S_{xx}"); legend(as_legend);

%% Problem 2
clear; close all; clc;
load("Signals.mat");

n = 1:size(x,2);


figure();
subplot(2,1,1); 
plot(n,x); title("x[n]"); ylabel("x"); xlabel("n");
subplot(2,1,2); 
plot(n,y); title("y[n]"); ylabel("y"); xlabel("n");

l = (-size(x,2)+1):(size(x,2)-1);
rxy = xcorr(x,y);
rxy_conv = conv(x,fliplr(y));

figure();
subplot(2,1,1); 
stem(l,rxy); title("r_{xy}[l] from xcorr"); ylabel("r_{xy}"); xlabel("l");
subplot(2,1,2); 
stem(l, rxy_conv); title("r_{xy}[l] from conv"); ylabel("r_{xy}"); xlabel("l");

[m, i] = max(rxy);
D = -l(i) % index of maximum


%% Problem 3
clear; close all; clc;
filename = "piano.wav";
[x, Fs] = audioread(filename{1});

Rs = [11025, 22050, 33075];
alphas = [0.1 0.5 1];

for R=Rs
   for alpha=alphas
       figure();
       B = zeros(1,R+1);
       B(1) = 1; B(end) = alpha;
       A = 1;
       
       [H,T] = impz(B,A, 2*R);
       subplot(2,1,1);
       stem(T,H);
       title("Imp \alpha = " + string(alpha) + " and R = " + string(R));
       xlabel("n"); ylabel("h[n]");
       
       [H,W] = freqz(B, A);
       subplot(2,1,2);
       log_H = 10*log10(abs(H));
       plot(W,log_H);
       title("Freq \alpha = " + string(alpha) + " and R = " + string(R));
       xticks([0 pi/4 pi/2 3*pi/4 pi 5*pi/4 3*pi/2 7*pi/4 2*pi]);
       xticklabels({'0' '\pi/4' '\pi/2' '3\pi/4' '\pi' '5\pi/4' '3\pi/2' '7\pi/4' '2\pi'});
       xlim([0 pi]);    xlabel("\omega");
       ylim([floor(min(log_H))-1, ceil(max(log_H))+1]);   ylabel("H[\omega] (dB)");
       
       %disp("Filtered sound: alpha=" + string(alpha) + "R=" + string(R));
       %y = filter(B,A,x);
       %soundsc(y,Fs);
       %input('---press enter to continue---', 's');
   end
end

%% Problem 3 - new filter
clear; close all; clc;
filename = "piano.wav";
[x, Fs] = audioread(filename{1});

R=5000; alpha = 0.4; N=5;

figure();
B = zeros(1,N*R); A = zeros(1,R);

B(1) = 1; B(end) = -alpha^N;
A(1) = 1; A(end) = -alpha;

[H,T] = impz(B,A);
subplot(2,1,1);
plot(T,H); 
title("Imp \alpha = " + string(alpha) + ", R = " + string(R)+ " and N = " + string(N));
xlabel("n"); ylabel("h[n]");

[H,W] = freqz(B, A);
subplot(2,1,2);
log_H = 10*log10(abs(H));
plot(W,log_H);
title("Freq \alpha = " + string(alpha) + ", R = " + string(R) + " and N = " + string(N));
xticks([0 pi/4 pi/2 3*pi/4 pi 5*pi/4 3*pi/2 7*pi/4 2*pi]);
xticklabels({'0' '\pi/4' '\pi/2' '3\pi/4' '\pi' '5\pi/4' '3\pi/2' '7\pi/4' '2\pi'});
xlim([0 pi]);    xlabel("\omega");
ylim([floor(min(log_H))-1, ceil(max(log_H))+1]);   ylabel("H[\omega] (dB)");

%y = filter(B,A,x);
