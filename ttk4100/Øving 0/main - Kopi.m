%definerer variablene
mu=5;

%ulike verdier som skal testes
x1_0 = 5;
x2_0 = 5;

figure(1); clf(1);
hold on; grid on;

sim simulation
    
%plotter data
plot(x1.data, x2.data);

title('varierende initialkondisjoner');
xlabel('x1'); ylabel('x2')
legend(legend_to_set, 'location', 'eastoutside')
