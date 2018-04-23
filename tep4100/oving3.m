% konstanter
rho_m = 1400;
rho_d = 2700;
dam_height = 1.25;
g = 9.81;

mu_1 = 0.4;
mu_2 = 0.6;


% funksjoner
slide_height = @(mu, width) sqrt(2*rho_d*dam_height*width*mu/rho_m);
flip_height = @(width) nthroot(3*rho_d*width.^2*dam_height/rho_m, 3);

% kalkulasjoner
dam_widths = 0.05:0.05:1;

slides_04 = slide_height(0.4, dam_widths);
slides_06 = slide_height(0.6, dam_widths);
flips = flip_height(dam_widths);


plot(dam_widths, slides_04);
hold on;
plot(dam_widths, slides_06);
plot(dam_widths, flips);
ylabel('Kritisk høyde (m)');
xlabel('Demningsbredde (m)');
legend('Skli ved f=0.4', 'Skli ved f=0.6', 'Veltehøyde', 'Location', 'best');

