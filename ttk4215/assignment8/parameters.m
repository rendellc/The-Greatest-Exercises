gamma1 = 1;
gamma2 = 1;
gamma3 = 1;

%% plot
t = data.Time;
V = data.Data(:,1);
Vm = data.Data(:,2);

plot(t,V, t,Vm);
legend('V', 'V_m');
title('V vs V_m');
xlabel('t');

