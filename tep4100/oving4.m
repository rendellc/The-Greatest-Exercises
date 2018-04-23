% konstanter
a = 0.6;
b = 0.5;
c = 0.2;

% domene
[x,y] = meshgrid(-2:0.4:7, -2:0.4:2);

% hastighet
u = a^2 - (b - c.*x).^2;
v = -2*b*c.*y + 2*c^2.*x.*y;

figure;
quiver(x,y,u,v);
title('Hastighetsfelt');
xlabel('u'); ylabel('v');