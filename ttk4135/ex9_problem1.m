
%x0 = [-1.2, 1];
x0 = [1.2, 1.2];

%[x_opt, fval_opt, x_iter, f_iter, alpha] = min_rosenbrock_newton(x0); plot_iter_rosenbrock(x_iter); title('Newton')
%[x_opt, fval_opt, x_iter, f_iter, alpha] = min_rosenbrock_bfgs(x0); plot_iter_rosenbrock(x_iter); title('BFGS')
[x_opt, fval_opt, x_iter, f_iter, alpha] = min_rosenbrock_sd(x0); plot_iter_rosenbrock(x_iter); title('Steepest Descent')


ks = 1:size(alpha,2);
subplot(1,2,1)
plot(ks, alpha);
xlabel('k');
ylabel('\alpha_k');
subplot(1,2,2)
plot(ks, f_iter);
xlabel('k');
ylabel('f(x_k)');
