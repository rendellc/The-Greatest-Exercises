clear;

g = 9.81; % gravity
P1 = 240000;
L = 0.5;
v_water = 1e-6;
D_bottle = 0.1;
D_tube = 0.01;
D_nozzle = 0.005;
rho = 1000; 

h_L_minor = @(V) 0.5*(1-(D_tube/D_bottle)^2)*(D_nozzle/D_tube)^4*V.^2 / (2*g) + 0.5*(1 - (D_nozzle/D_tube)^2)*V.^2 / (2*g);    

Re_old = 0; 
Re_new = 1e9;
eps = 1e-2;
syms f_ positive
syms V_ positive
counter = 0;
while abs(Re_old - Re_new) > eps
    counter = counter + 1;
    Re_old = Re_new;
    f_calc = vpasolve(1/sqrt(f_) == 2.0*log10(Re_old*sqrt(f_)) - 0.8);
    
    % calculate V_out
    h_L_major = @(V) f_calc*L/D_tube * (D_nozzle/D_tube)^4*V.^2 / (2*g);
    
    bern_eq = @(V) P1 + 0.5*rho*(D_nozzle/D_bottle)^4 * V.^2 - rho*g*h_L_minor(V) - rho*g*h_L_major(V) - 0.5*rho*V.^2;
    
    V_out = solve(bern_eq(V_) == 0,  V_);
    
    Re_new = V_out * D_tube / v_water;
    
end

V_out
counter