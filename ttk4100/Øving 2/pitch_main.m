J = 15;
m = 200;

%innstillinger
u = 1000;
delta = pi/16;
theta_0 = pi/8;
theta_dot0 = 0;
v_0 = 0;
t_sim = 30;

%proporsjonalitetskonstanter
k = 100;
k_2 = 5;
k_3 = 1;
k_4 = 1;

sim('pitch_hastighet', t_sim);

figure(1); clf(1);
plot(x_pos.data, z_pos.data);
xlabel('x-planet'); ylabel('z-planet')
title('Bevegelse til AUV');
grid on;