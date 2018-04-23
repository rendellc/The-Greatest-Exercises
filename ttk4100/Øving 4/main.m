% definerer konstantene
L_a = 1;
R_a = 10;
K_E = 1;
K_M = 1;
J_m = 0.01;
M_L = 0;

% regulator
theta_r = pi/2;
theta_0 = 0;
i_a0 = 0;
w_m0 = 0;

t_sim = 3;

% *****************

figure(1); clf(1);
% ZN-tuning
P = 6;
I = 3.3;
D = 0.075;
N = 100;

sim('simulink_pidcontroller.slx', t_sim);
hold on; grid on;
plot(theta.time, theta.data, 'LineWidth', 3);

% Simulink Autotuning
P = 5.3286;
I = 0.72939;
D = 0.1143;
N = 899.2487;

sim('simulink_pidcontroller.slx', t_sim);
plot(theta.time, theta.data, 'LineWidth', 3);

xlabel('Tid (s)'); ylabel('Motorvinkel');
title('Likestrømsmotor - tuningssammenligning');
legend('ZN-tuning', 'Simulink Tunings');



