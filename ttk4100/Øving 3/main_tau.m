%system
h_max = 1; %tankens høyde, brukes ikke
h_0 = 0; %startverdi
A = 1; %tverrsnittsareal
k = 1;
rho = 1000; %massetettheten til vann
w_f = 0; %forstyrrelse
%regulator
h_r = 0.5; %referanse
k_p = 100;
k_i = 4;
t_sim = 2000; %simuleringstid
figure(1); clf(1);
grid on; hold on;

legend_to_set = {};
tau_list = [10,11,12,0];
for i = 1:4
    tau = tau_list(i); %tidsforsinkelse
    sim('oppg1_system', t_sim);
    
    plot(h);
    legend_to_set{i}=['tau = ',num2str(tau)];
end

xlabel('Tid (s)'); ylabel('Tanknivå (m)');
title('Nivåregulering PI-regulator og transportforsinkelse');
legend(legend_to_set);