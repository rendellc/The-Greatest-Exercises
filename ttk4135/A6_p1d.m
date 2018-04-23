T = 0.5;
m = 1;

Ad = [1 T; 0 1];
Bd = [T^2/(2*m);
      T/m];

Q = 2*eye(2);
R = 2;

[K,~,~] = dlqr(Ad,Bd,Q,R);
e = eig(Ad - Bd*K);

