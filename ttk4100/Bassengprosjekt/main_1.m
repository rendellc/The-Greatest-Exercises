V = 30000*3785.41178; %gallons * cm^3/gallon
A = V/300; %areal = volum/300 cm
vind = 5; %tipping på gjennomsnittlig vindhastighet
h = 5.7 + 3.8*vind; %heat transfer coefficient
C_pv = 4.1796; %varmekapasitet per volum
T_om = 15+273.15; %temperatur ute
T_0 = 15+273.15; %starttemp til basseng
T_onsket = 30+273.15; %celsius + konstant for kelvi
t_sim = 50000; %simuleringstid

sim('bassengmodell_1',t_sim);
plot(T) 