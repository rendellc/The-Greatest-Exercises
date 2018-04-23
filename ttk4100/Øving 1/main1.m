%definerer variablene
u = 500;
v_0 = 0;
m = 200;
k = 100;
t_sim = 15;

sim('simulation1', t_sim)

%lager figur og plotter data
figure(1); clf(1);
grid on;
plot(v);
title('Fart over tid');
xlabel('Tid (s)'); ylabel('Fart (m/s)');