alphas= [0.5 0.7 0.9];
K=3;
wavfile='Audio Sample.wav';

[x,fs]=audioread (wavfile);

for alpha = alphas
    B(1)= (K/2)*(1-alpha)+(1/2)*(1+alpha);
    B(2)= (K/2)*(1-alpha)-(1/2)*(1+alpha);
    A = [1, -alpha];
    y = filter(B,A,x);
    figure
    [H,W]=freqz(B,A,1024);
    normFreq = [0:1/(length(H)-1):1];
    plot(normFreq,20*log10(abs(real(H))));
    title(['Frequency response, alpha=',num2str(alpha), ' K=',num2str(K)]);
    xlabel('Normalized frequency');
    ylabel('Magnitude [dB]');
end

alpha = 0.7;
Ks = [0.5 1 4];
for K = Ks
    B(1)= (K/2)*(1-alpha)+(1/2)*(1+alpha);
    B(2)= (K/2)*(1-alpha)-(1/2)*(1+alpha);
    A = [1, -alpha];
    y = filter(B,A,x);
    figure
    [H,W]=freqz(B,A,1024);
    normFreq = [0:1/(length(H)-1):1];
    plot(normFreq,20*log10(abs(real(H))));
    title(['Frequency response, alpha=',num2str(alpha), ' K=',num2str(K)]);
    xlabel('Normalized frequency');
    ylabel('Magnitude [dB]');
end

