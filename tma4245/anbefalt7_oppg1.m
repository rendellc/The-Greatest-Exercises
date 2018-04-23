clf; clear;
n = 8;
%N_V = 1;
lambda = 0.2;

tic
%V = zeros(1, N_V);
%for i = 1:N_V
%    V(i) =  max(exprnd(repmat(1./lambda, 1, n)));   
%end
toc
%histogram(V, 'Normalization', 'cdf'); %'probability');
%hold on


f_V = @(v) (1-exp(-lambda*v)).^n * n*lambda.*exp(-lambda*v)./(1-exp(-lambda*v));
F_V = @(v) (1-exp(-lambda.*v)).^n;

% P(V > 30)
%p_estimate = sum(V>30)/length(V);
%p_theoretical = 1 - F_V(30);
%p_estimate - p_theoretical

%dt = 0.1;
%v = (0+dt):dt:max(V);
%plot(v, f_V(v));
%plot(v, F_V(v));


% 1 e
N_ROUNDS = 1000000;
P_reasure = 2/3;
reasurance_cost = 5;
loan_cost = 5;

n_prob = 1e4; % used for probability testing
total_stock = 0;
tic
for i = 1:N_ROUNDS
    net_stock = 30;
    V = max(exprnd(repmat(1./lambda, 1, n)));
 
    if (V <= 30)
        net_stock = net_stock - V;
    else
        
        if (randsample(n_prob,1) <= (P_reasure * n_prob))
            % got reasurance
            net_stock = net_stock - reasurance_cost;
        else
            % didn't get reasurance
            net_stock = net_stock - 25;
            net_stock = net_stock - loan_cost;
        end
    end
    
    total_stock = total_stock + net_stock;
end
toc
total_stock = total_stock/N_ROUNDS;

disp('Estimated stock: ' + string(total_stock));
disp('Based on ' + string(N_ROUNDS) + ' simulated years.');







