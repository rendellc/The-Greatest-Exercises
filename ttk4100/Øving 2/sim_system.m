%definerer variablene
v_0 = 0;
u = 500;
m = 200;
k = 100;
t_sim = 15;

sim('simulering', t_sim);

%plotter simuleringsresulatet
figure(1); clf(1);
plot(v);
title('Simulering med ODE1');
xlabel('tid (s)'); ylabel('v (m/s)');
grid on;