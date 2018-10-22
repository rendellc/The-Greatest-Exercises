% System parameters
params_30 = [0.81 19.75 0.31 0.064 14.0 0.365]';
params_60 = [0.77 19.0 0.27 0.09 13.5 0.505]';

% Least square with forgetting factor parameters
theta0 = ones(6,1); %[1 10 0.5 110 0.5]';
P0 = diag([1 1 1 1 1 1]);
R0 = 5;
Gamma = eye(6);
beta = 0.000001;
alpha = 3;
% Lambda = s^2 + lambda1*s + lambda2
lambda1 = 1;
lambda2 = 1;


%% Run
sim('simulation', 50);


%% Plot
t = parameters.Time;
k0 = parameters_star.Data(:,1);
k0_est = parameters.Data(:,1);
omega0 = parameters_star.Data(:,2);
omega0_est = parameters.Data(:,2);
xi0 = parameters_star.Data(:,3);
xi0_est = parameters.Data(:,3);
k1 = parameters_star.Data(:,4);
k1_est = parameters.Data(:,4);
omega1 = parameters_star.Data(:,5);
omega1_est = parameters.Data(:,5);
xi1 = parameters_star.Data(:,6);
xi1_est = parameters.Data(:,6);




figure(1); clf(1);
subplot(3,1,1); hold on
plot(t,k0, '--b');
plot(t,k0_est, 'b');
plot(t,k1, '--g');
plot(t,k1_est, 'g');
title('Estimates for k_0 and k_1');
legend('$k_0$', '$\hat{k_0}$', '$k_1$', '$\hat{k_1}$', 'Interpreter', 'latex');
axis([0 max(t) 0 6]);

subplot(3,1,2); hold on
plot(t,omega0, '--b');
plot(t,omega0_est, 'b');
plot(t,omega1, '--g');
plot(t,omega1_est, 'g');
title('Estimates for \omega_0 and \omega_1');
legend('$\omega_0$', '$\hat{\omega_0}$', '$\omega_1$', '$\hat{\omega_1}$', 'Interpreter', 'latex');
axis([0 max(t) 0 25]);

subplot(3,1,3); hold on
plot(t,xi0, '--b');
plot(t,xi0_est, 'b');
plot(t,xi1, '--g');
plot(t,xi1_est, 'g');
title('Estimates for \xi_0 and \xi_1');
legend('$\xi_0$', '$\hat{\xi_0}$', '$\xi_1$', '$\hat{\xi_1}$', 'Interpreter', 'latex');
axis([0 max(t) 0 1]);



