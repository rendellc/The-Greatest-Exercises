%definerer variablene
m = 2;
d = 4; 
k = 6;
t_sim = 10;

%definerer p og q
p = d./m;
q = k./m;

%Initialbetingelser
x_0 = 1;
x_dot_0 = 0;

sim('simulation2',t_sim)

figure(1); clf(1);
grid on;
plot(x);
xlabel('Tid(s)'); ylabel('Posisjon');
title('Masse-fjær-demper');