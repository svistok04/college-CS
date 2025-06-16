% zadanie 2
clc; 
clear all; 
close all;

x = 0:10;
y = [-0.2 -0.13 -0.08 -0.05 -0.042 -0.025 -0.018 -0.007 -0.008 -0.005 -0.002];
N = length(x);
xx = linspace(min(x), max(x), 300);

% model 1: F1 w = c1*x + c2
Z = [x; ones(1, N)];
C = y * Z' * inv(Z * Z');
F1 = @(x) C(1)*x + C(2);
subplot(2, 2, 1);
plot(x, y, '.b', MarkerSize=10); hold on;
plot(xx, F1(xx), '-r');
mse = mean((y - F1(x)).^2);
title(['F1 w = c1*x + c2, MSE = ', num2str(mse, '%.8f')]);
disp('C1 ='); disp(C);
disp(['MSE1 = ', num2str(mse)]);

% model 2: F2 w = c1*x^2 + c2*x + c3
Z = [x.^2; x; ones(1, N)];
C = y * Z' * inv(Z * Z');
F2 = @(x) C(1)*x.^2 + C(2)*x + C(3);
subplot(2, 2, 2);
plot(x, y, '.b', MarkerSize=10); hold on;
plot(xx, F2(xx), '-r');
mse = mean((y - F2(x)).^2);
title(['F2 w = c1*x^2 + c2*x + c3, MSE = ', num2str(mse, '%.8f')]);
disp('C2 ='); disp(C);
disp(['MSE2 = ', num2str(mse)]);

% model 3: F3 w = c1*x^3 + c2*x^2 + c3*x + c4
Z = [x.^3; x.^2; x; ones(1, N)];
C = y * Z' * inv(Z * Z');
F3 = @(x) C(1)*x.^3 + C(2)*x.^2 + C(3)*x + C(4);
subplot(2, 2, 3);
plot(x, y, '.b', MarkerSize=10); hold on;
plot(xx, F3(xx), '-r');
mse = mean((y - F3(x)).^2);
title(['F3 w = c1*x^3 + c2*x^2 + c3*x + c4, MSE = ', num2str(mse)]);
disp('C3 ='); disp(C);
disp(['MSE3 = ', num2str(mse)]);

% model 4: F4 w = c1*exp(c2*x)
Ylog = log(y);
disp(Ylog);
Z = [x; ones(1, N)];
C = Ylog * Z' * inv(Z * Z');
F4 = @(x) exp(C(2)) * exp(C(1)*x);
subplot(2, 2, 4);
plot(x, y, '.b', MarkerSize=10); hold on;
plot(xx, F4(xx), '-r');
mse = mean((y - F4(x)).^2);
title(['F4 w = c1*exp(c2*x), MSE = ', num2str(mse)]);
disp('C4 ='); disp(C);
disp(['MSE4 = ', num2str(mse)]);
