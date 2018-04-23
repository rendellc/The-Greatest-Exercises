levetider = load('levetider.txt');
korrigerte_levetider = levetider(levetider<100);

avg0 = mean(levetider);
avg1 = mean(korrigerte_levetider);

med0 = median(levetider);
med1 = median(korrigerte_levetider);

std0 = std(levetider);
std1 = std(korrigerte_levetider);

boxplot(korrigerte_levetider);
ylabel('Levetid i år');
title('Boxplot for levetid til komponent');

figure; hold on; box on;
histogram(korrigerte_levetider, 10, 'Normalization', 'pdf');
xlim([0 6]);

xverdier = 0:.01:6;
f = @(x, alpha) x.* exp(-x.^2 /(2*alpha)) .* alpha;

fverdier = f(xverdier, 0.5);
plot(xverdier, fverdier, 'r-');
fverdier = f(xverdier, 1);
plot(xverdier, fverdier, 'g-');
fverdier = f(xverdier, 2);
plot(xverdier, fverdier, 'b-');

legend('Data', 'alpha=0,5', 'alpha=1', 'alpha=2');
