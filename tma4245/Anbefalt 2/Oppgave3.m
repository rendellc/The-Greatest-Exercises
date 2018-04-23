i = 1:12;
j = 1:12;
[X,Y] = meshgrid(i,j);
C=1;

p0_notadjusted = @(x,y) exp(-1/(2*8)*((x-6.5).^2 + (y-6.5).^2));
C = 1/sum(sum(p0_notadjusted(X,Y)));
p0 = @(x,y) C*exp(-1/(2*8)*((x-6.5).^2 + (y-6.5).^2));

surf(p0(X,Y));

