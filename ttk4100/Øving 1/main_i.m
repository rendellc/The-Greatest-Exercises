m = 200;
k = 100;

%første simulering
v_0 = 0;
u = 200;
[t1,xVec1,y1] = sim('simulation1',[0 15]);

%andre simulering
v_0 = xVec1(end);
u = 0;
[t2,xVec2,y2] = sim('simulation1', [15 30]);

%lager figur og plotter data
figure(1); clf(1);
grid on; hold on;
plot(t1,xVec1); plot(t2,xVec2);
title('Fart over tid');
xlabel('Tid (s)'); ylabel('Fart (m/s)');