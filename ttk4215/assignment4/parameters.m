clear;
% Parameters
m0 = 20;
beta0 = 0.1;
k0 = 5;

% Initial conditions
y0 = 0;
y_dot0 = 0;
y_dotdot0 = 0;

% filter
root1 = -1;
root2 = -2;
lambda1 = -(root1 + root2);
lambda2 = root1*root2;

% task
taskE = 0;
theta0 = [0 0 0];

%% Gradient Instantaneous
alphaInstant = 1;
GammaInstant = diag([300.0 50.0 10.0]);

%% Gradient Integral
alphaIntegral = 1;
betaIntegral = 0.1;
GammaIntegral = diag([300.0 50.0 10.0]);






