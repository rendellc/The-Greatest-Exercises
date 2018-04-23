%system
h_max = 1; %tankens høyde, brukes ikke
h_0 = 0; %startverdi
A = 1; %tverrsnittsareal
k = 1;
rho = 1000; %massetettheten til vann
w_f = 10; %forstyrrelse
tau = 0; %tidsforsinkelse

%regulator
h_r = 0.5; %referanse
k_p = 100;
k_i = 0.1;

t_sim = 200; %simuleringstid

sim('oppg1_system', t_sim);

%plotter resultatene
figure(1); clf(1);
plot(h);
grid on; hold on;
xlabel('Tid (s)'); ylabel('Tanknivå (m)');
title('Nivåregulering PI-regulator');
%legend('transportforsinkelse = 3');

