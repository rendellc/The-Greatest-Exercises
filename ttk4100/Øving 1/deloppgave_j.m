%definerer variablene;
v_0 = 0;
m = 200;
k = 100;

%figuren
figure(1); clf(1);
grid on; hold on;

%fra 0 til 15 
t = 0:1:15;
u = 200;
v = u./k + v_0./(exp(k.*t./m));
plot(v,t)

%fra 15 til 30
t = 15:1:30;
v_0 = v(end);
v = v_0./exp(k.*t./m);
plot(v,t)

%lager figur og plotter data
title('Fart over tid');
xlabel('Tid (s)'); ylabel('Fart (m/s)');