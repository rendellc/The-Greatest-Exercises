U0 = 1;
b = 1;
C = -2:0.5:2;

x = 0:1:10;

figure();
hold on;
for c = C
   y = c./(U0 + b.*x);
   plot(x,y);
end
xlabel('x (m)');
ylabel('y (m)');
legend(string(C));
