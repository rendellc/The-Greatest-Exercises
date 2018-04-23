%Input
T = [25 43 57 21 32 43 50];
 
%Konstanter
R_air = 287.0; %J/(kg K)
V = 0.025; %m^3
P(1) = 310*1000; %Pa

%Beregninger
T_kelvin = T + 273.15;
P = P(1)/T_kelvin(1) .*T_kelvin;
delta_m = (P(1)*V/R_air)...
    .*(1/T_kelvin(1) - 1./T_kelvin);

%Plotting
i = 1:size(T,2);
plot(i, delta_m);
xlabel('Temperaturer (Celsius)');
set(gca, 'XTickLabel', T);
ylabel('Masse som må slippes ut (kg)');
title('Luftutslipp for dekk');