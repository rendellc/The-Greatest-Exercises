%definerer variablene
mu=5;
t_sim = 1000;
%initialverdier
x1_0_verdier = [-10,-9,-8,8,9,10];
x2_0_verdier = [10,5,-2,4,-10,3];

%formatering
formats = {'r','g','b','m','c','b'};

%legend, brukes mot slutten
legend_to_set = {};

figure(1); clf(1);
hold on; grid on;

for i = 1:6
    x1_0 = x1_0_verdier(i);
    x2_0 = x2_0_verdier(i);

    sim('simulation',t_sim);

    %plotter data
    plot(x1.data, x2.data, formats{i});
    legend_to_set{i}=['x1_0 = ', num2str(x1_0), ' og x2_o = ', num2str(x2_0)];
end

title('varierende initialkondisjoner');
xlabel('x1'); ylabel('x2');
legend(legend_to_set, 'location', 'eastoutside');