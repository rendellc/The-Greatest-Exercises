%% Setup
Ad = [0 0 0;
      0 0 1;
      0.1 -0.79 1.78];
Bd = [1 0 0.1]';
C = [0 0 1];

x0 = [0 0 1]';
N = 30;
N_u = 6; % split input into N_u equally sized blocks
r = 1;


%% Quadprog
% assert(~rem(N,N_u), 'N_u needs to divide N');
nx = size(Ad,2); nu = size(Bd,2);
% 
Q = (C'*C);
R = r;
G11 = kron(eye(N),Q);
G12 = zeros(N*nx, N_u*nu);
G21 = zeros(N_u*nu, N*nx);
G22 = kron(eye(N_u), R);
G = [G11 G12; 
     G21 G22];

% Aeq_right = kron(kron(eye(N_u),ones(N/N_u,1)),-Bd);
A_on_left = kron(eye(N),-Ad);
Aeq_left = kron(eye(N),eye(nx)) + [A_on_left(:,nx+1:end) zeros(N*nx,nx)];
% Aeq = [Aeq_left Aeq_right];
beq = [Ad*x0; 
       zeros((N-1)*nx,1)];

z_lb = -Inf*ones(N*(nx+nu),1);
z_lb(N*nx+(1:N*nu)) = -ones(N*nu,1);
z_ub = Inf*ones(N*(nx+nu),1);
z_ub(N*nx+(1:N*nu)) = ones(N*nu,1);
% 
% 
% [z, ~, ~, OUTPUT] = quadprog(G,[],[],[],Aeq,beq,z_lb,z_ub);
% 
% n_zeros = 5;
% t = -n_zeros:N;
% x_star = [zeros(nx*n_zeros,1); x0; z(1:N*nx)];
% u_star = z((N*nx+1):end);
% 
% clf;
% hold on
% 
% if C==[0 0 1]
%    plot(t, x_star(3:nx:end));
% end
% 
% for i=1:nu
%    stairs(t((n_zeros+1):(N/N_u):end), [u_star(i:nu:end); u_star(end)]);
% end
% 
% title(['Optimal solution from quadprog with constraint, r=' num2str(r)]);
% axis([-n_zeros N -4 4]);
% legend('y_t', 'u_t');
% disp(['Number of iterations in quadprog: ' num2str(OUTPUT.iterations)]);

%% New sequence
seq = [1 1 2 4 8 14];
assert(sum(seq)==N, 'Invalid sequence')

columns = size(seq,2);
Aeq_right = zeros(N*nx, columns*nu);
for i=1:columns
    rowstart = 1 + sum(seq(1:(i-1)))*nx;
    Aeq_right(rowstart:(rowstart+seq(i)*nx-1),i) = repmat(-Bd,seq(i),1);
end

Aeq = [Aeq_left Aeq_right];
beq = [Ad*x0; zeros((N-1)*nx,1)];

[z, ~, ~, OUTPUT] = quadprog(G,[],[],[],Aeq,beq,z_lb,z_ub);

n_zeros = 5;
t = -n_zeros:N;
x_star = [zeros(nx*n_zeros,1); x0; z(1:N*nx)];
u_star = z((N*nx+1):end);

clf;
hold on

if C==[0 0 1]
   plot(t, x_star(3:nx:end))
end

for i=1:nu
    stairs([0 cumsum(seq)], [u_star(i:nu:end); u_star(end)])
end

title(['Optimal solution from quadprog with constraint, r=' num2str(r)]);
axis([-n_zeros N -4 4]);
legend('y_t', 'u_t');
disp(['Number of iterations in quadprog: ' num2str(OUTPUT.iterations)]);

