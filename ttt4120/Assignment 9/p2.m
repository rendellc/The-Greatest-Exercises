%% setup
wc = 0.2*pi;


%% filter
Bz = [0.245 0.245];
Az = [1 -0.51];

%Bz = wc/(2+wc) * [1 1];
%Az = [1 (-2+wc)/(2+wc)];

[H,W] = freqz(Bz,Az);

W_inregion = W(mag2db(abs(H)) > mag2db(1/sqrt(2)));
wc_est = W_inregion(end)/pi;

display('Cut-off is ' + string(wc_est) + 'pi');


plot(W, mag2db(abs(H)));
title('Magnitude response of H(z)');
xlabel('w [rad]'); ylabel('magnitude [db]');