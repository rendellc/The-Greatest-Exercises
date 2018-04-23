rho = 1.25; % kg/m^3
eta_turb = 0.3; % efficiency

e_mek = @(V) 0.5.*V.^2;
Wdot_inn = @(D, V) rho*pi()/4*D.^2.*V.*e_mek(V);
Wdot_el = @(D, V) Wdot_inn(D, V) .* eta_turb;

[Ds, Vs] = meshgrid(20:20:80, 5:5:20);

surf(Ds, Vs, Wdot_el(Ds, Vs));
title('Power out v. vind velocity and diameter');
xlabel('Diameter (m)');
ylabel('Vind velocity (m/s)');
zlabel('Electric power out (W)');