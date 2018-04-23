%definerer variablene
v(1) = 0;
u = 500;
m = 200;
k = 100;
h = 0.1;
t = 0:h:15;
v_eksakt = exp(-k/m*t)*(v(1)-u/k)+u/k;
 
%implementerer eulers metode
for i=2:(15/h+1),
    v(i)=v(i-1)+h*(u/m - v(i-1)*k/m);
end

figure(1); clf(1);
grid on; hold on;
plot(t,v,'--'); plot(t, v_eksakt); hold off;
title('Eulers metode');
legend('euler', 'eksakt løsning');
xlabel('Tid (s)'); ylabel('Fart (m/s)');