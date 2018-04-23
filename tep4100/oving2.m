dybder = [0 50 100 80 110 50 30 0];
avstand = [1 100 500 550 900 1100 1200 1300];

% konstanter
P_atm = 101*10^3;
rho = 1000;
SG = 1.3;
rho_hav = rho*SG;
g = 9.81;

% beregning og plotting
trykk = P_atm + rho_hav*g*dybder;

plot(avstand, trykk .*0.001);
xlabel('avstand');
ylabel('trykk (kPa)');
title('Trykkvariasjon på ubåttur');



