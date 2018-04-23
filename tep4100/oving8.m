clc;
% --- constants ---
g = 9.81; % gravitational acc.
z0 = 3;     % meters above ground
u2 = 20.4;  % exit velocity
anglesDeg = 0:5:70;
dt = 0.01;


% calculations
angles = deg2rad(anglesDeg);
x = @(t, theta) u2.*cos(theta).*t;
z = @(t, theta) z0 + u2.*sin(theta).*t - 0.5*g.*t.^2;

% collide with water time
t_collide = fsolve(@(t) z(t, angles), repmat(5, size(angles))); % find zero of all z-functons

% maximum distance is at theta=45
x_max = x(t_collide(anglesDeg==45), angles(anglesDeg==45));


% plotting
figure;
hold on;
for i = 1:size(angles, 2)
    xs = x(0:dt:t_collide(i), angles(i));
    zs = z(0:dt:t_collide(i), angles(i));
    
    plot(xs, zs);
    t_collide(i);
end
plot(x_max, 0, 'ro'); 
xlabel('Horistontal avstand (m)');
ylabel('Høyde  (m.o.h)');
title('Brannbåts rekkevidde');
legend('\theta = ' + string(anglesDeg), 'Maks avstand');

