%% Run
parameters;
taskE = 0;
sim('problem4_9.slx', 100);

%% Plot
t = results.Time;
m = model.Data(:,1);
beta = model.Data(:,2);
k = model.Data(:,3);
m_pred = results.Data(:,1);
beta_pred = results.Data(:,2);
k_pred = results.Data(:,3);

figure(1); clf(1);
subplot(3,1,1);
plot(t, m, '--');
hold on;
plot(t, m_pred);
legend('$m$', '$\hat{m}$', 'interpreter', 'latex');
title('mass');

subplot(3,1,2);
plot(t, beta, '--');
hold on;
plot(t, beta_pred);
legend('$\beta$', '$\hat{\beta}$', 'interpreter', 'latex');
title('damping');

subplot(3,1,3);
plot(t, k, '--');
hold on;
plot(t, k_pred);
legend('$k$', '$\hat{k}$', 'interpreter', 'latex');
title('spring');

%% Run
parameters;
taskE = 1;
sim('problem4_9.slx', 500);

%% Plot
t = results.Time;
m = model.Data(:,1);
beta = model.Data(:,2);
k = model.Data(:,3);
m_pred = results.Data(:,1);
beta_pred = results.Data(:,2);
k_pred = results.Data(:,3);

figure(1); clf(1);
subplot(3,1,1);
plot(t, m, '--');
hold on;
plot(t, m_pred);
legend('$m$', '$\hat{m}$', 'interpreter', 'latex');
title('mass');

subplot(3,1,2);
plot(t, beta, '--');
hold on;
plot(t, beta_pred);
legend('$\beta$', '$\hat{\beta}$', 'interpreter', 'latex');
title('damping');

subplot(3,1,3);
plot(t, k, '--');
hold on;
plot(t, k_pred);
legend('$k$', '$\hat{k}$', 'interpreter', 'latex');
title('spring');

