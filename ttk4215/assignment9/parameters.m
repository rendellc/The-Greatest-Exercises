%% Plant
M = 10;
f = 1;
k = 9;

%% Control law
Gamma = diag([1 1 1 1]);
lambda0 = 1;
p0 = 1;

%% Plotting
t = ys.Time;
yp = ys.Data(:,1);
ym = ys.Data(:,2);

plot(t,yp, t,ym);
title('y_p v. y_m');
xlabel('time [s]');
ylabel('position [m]');
legend('y_p', 'y_m');