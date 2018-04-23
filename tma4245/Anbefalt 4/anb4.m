dx = 0.01;
mrtl = 6.29; % hl mørtel han kjøper inn

x_s = 4:dx:mrtl;
x_b = mrtl:dx:7;
figure(1);
plot(x_s, losses(x_s, mrtl));
hold on;
plot(x_b, losses(x_b, mrtl));
expectedLoss = dx.*(dot(losses(x_s, mrtl),x_s) + dot(losses(x_b, mrtl),x_b))

mrtl = 6.28; % hl mørtel han kjøper inn
x_s = 4:dx:mrtl;
x_b = mrtl:dx:7;
plot(x_s, losses(x_s, mrtl));
plot(x_b, losses(x_b, mrtl));

expectedLoss = dx.*(dot(losses(x_s, mrtl),x_s) + dot(losses(x_b, mrtl),x_b))
