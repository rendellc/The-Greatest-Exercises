%definerer variablene
v(1) = 0;
u = 500;
m = 200;
k = 100;
h = 0.1;
t = 0:h:15;
 
%implementerer eulers metode
for i=2:(15/h+1),
    v(i)=v(i-1)+h*(u/m - v(i-1)*k/m);
end

figure(1); clf(1);
grid on; hold on;
plot(t,v);
title('Eulers metode');
xlabel('Tid (s)'); ylabel('Fart (m/s)');