%definerer mu og simuleringstid
mu=5;
t_sim = 30;
%initialverdier
x1_0 = 1;
x2_0 = 1;


figure(1); clf(1);
hold on; grid on;

sim('simulation',t_sim);
    
%plotter data
plot(x1.data, x2.data);
legend_to_set=['x1_0 = ', num2str(x1_0), ' og x2_o = ', num2str(x2_0)];

title('initialkondisjoner');
xlabel('x1'); ylabel('x2');
legend(legend_to_set, 'location', 'eastoutside');