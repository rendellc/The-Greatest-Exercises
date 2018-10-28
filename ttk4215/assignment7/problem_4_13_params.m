%% Params
% model parameters
beta = 0.1;
k = 5;

% adaptive law parameters
Gamma = diag([30, 5]);
gamma = 0.01;
alpha = 0.001;
lambda1 = -2;
lambda2 = -2;

%% simulation
sim('problem_4_13', 100);

%% plotting
t = data.Time;
m_est = data.Data(:,1);
beta_est = data.Data(:,2);
k_est = data.Data(:,3);
m = data.Data(:,4);
beta = data.Data(:,5);
k = data.Data(:,6);

subplot(3,1,1);
plot(t,m, t,m_est);
title('m');
subplot(3,1,2);
plot(t,beta, t,beta_est);
title('beta');
subplot(3,1,3);
plot(t,k, t,k_est);
title('k');