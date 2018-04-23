close all;

N = 31;
fc = 0.2;

f = linspace(-0.5, 0.5, N);
n = 0:(N-1);

filt_rect = filtercoeffs(fc, rectwin(N)');
filt_hamm = filtercoeffs(fc, hamming(N)');


subplot(1,2,1);
stem(n, filt_rect);
title('Rectangular window');
xlabel('n'); ylabel('h[n]');

subplot(1,2,2);
stem(n, filt_hamm);
title('Hamming window');
xlabel('n'); ylabel('h[n]');

figure();
subplot(1,2,1);
plot(f, mag2db(abs(fft(filt_rect))));
title('Rectangular window');
xlabel('f'); ylabel('magnitude [dB]');

subplot(1,2,2);
plot(f, mag2db(abs(fft(filt_hamm))));
title('Hamming window');
xlabel('f'); ylabel('magnitude [dB]');


%% filter using fir1
fn = 2*fc;

fir1_rect = fir1(N-1, fn, rectwin(N));
fir1_hamm = fir1(N-1, fn, hamming(N));

figure()
subplot(1,2,1);
plot(f, mag2db(abs(fftshift(fft(fir1_rect)))));
title('Rectangular window');
xlabel('f'); ylabel('magnitude [dB]');

subplot(1,2,2);
plot(f, mag2db(abs(fftshift(fft(fir1_hamm)))));
title('Hamming window');
xlabel('f'); ylabel('magnitude [dB]');

