a = 0.45; % (ft s)^-1
b = 0.75; % (ft s)^-1

[xs,ys] = meshgrid(0:0.1:3, 0:0.1:4);

psi = @(x,y) a.*x.^2.*y - b/2.*x.*y.^2;

[C,h] = contour(xs,ys,psi(xs,ys));
clabel(C,h);
title('Contour plot (ft/s)');
xlabel('x (ft)');
ylabel('y (ft)');