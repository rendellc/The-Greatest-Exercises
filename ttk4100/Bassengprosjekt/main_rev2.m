%Konstanter

%Konstant for å konvertere Celsius til Kelvin
Kelvin_reg = 273.15;
%Volum
V = 500 * 200 * 200; %lengde * bredde * dybde (i cm^3)
%Overflateareal
A = 5 * 2; % lengde * bredde (i m^2)
%Varmeoverføringskonstant
h = 2; % W/(m^2 * K)
%Varmekapasitetskonstant
C_pv = 4.1796; %J/(cm^2 * K)
%Temperaturen til omgivelsene
T_om = 15; % Degrees
%Starttemperatur til bassenget
T_0 = T_om;
%Ønsket temperatur
T_onsket = 30;
%Simuleringstid
t_sim = 15*10^6;
%Tidsforsinkelse
time_delay = 60;
%Saturation
max_effect = 5800;
%Reguleringsparametere
K_p = 1000; 
K_i = 0.0002;

sim('bassengmodell_rev2_2014.slx', t_sim);

plot(T);
grid on;
xlabel('Tid [s]');
ylabel('Temperatur [C]');
title('Oppvarming av basseng');
legend('Tilpasset konstanter med saturation');


