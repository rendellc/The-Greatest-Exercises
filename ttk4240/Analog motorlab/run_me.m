%% Analog motorlab TTK4240
% You can use this script as a starting point to see step responses and
% test different control parameters. The script calls the simulink model
% analogmotorlab_sim.slx

% You will need to complete the simulink model in order to have the
% closed-loop system operative

% In the end of the script it is shown how to calculate circuit elements (R
% and C) based on the controller parameters (Kp and Ti). 

%% INPUT DATA
%   Motor parameters (you can adjust these later based on measured
%   open-loop response)
tau_m = 0.04;
a = 15;
K_m = a*tau_m;

K_p=1;      % Just an example value
T_i=0.1;    % Just an example value

%% Run simulation
global V_s; V_s = 15;   % Globals used in tacho2pot() - DO NOT CHANGE
global K_rev; K_rev = 0.156; % Globals used in tacho2pot() - DO NOT CHANGE
sim('analogmotorlab_startingpoint_2015a');

%%  Calculate R and C values based on controller parameters

P_Rin = 10*1e3; % 10k on each sum input
P_Rf = P_Rin * K_p; % Calculating the resistance corresponding to Kp

I_Cf = 100*1e-9; % The capacitor in the integrator path is fixed to 100 nF
I_Rin = T_i/I_Cf; % The resistor needed to have integral time T_i

% output human-readable(ish) values

disp(['P_Rf:  ', num2sip(P_Rf), ...
    9, ' (with P_Rin = ', num2sip(P_Rin), ')'])
disp(['I_Rin: ', num2sip(I_Rin), ...
    9, ' (with I_Cf = ', num2sip(I_Cf), ')'])

