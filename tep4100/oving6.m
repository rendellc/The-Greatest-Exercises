% konstanter
R = 1;
dr = 0.1;
dPdx = -50;
MU = [0.5 1 2];

u = @(r, mu) 1/(4*mu)*dPdx.*(r.^2 - R^2);

r = 0:dr:R;
figure;
hold on;
for i=1:length(MU)
    D(i) = string(strcat('\mu = ', num2str(MU(i))));
    plot(r,u(r,MU(i)));
end
title('Velocity profile');
xlabel('r (m)');
ylabel('u (m/s)');
legend(D);
    