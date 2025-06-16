clc; 
clear all; 
close all;
x_test = [3 11 15 19];
y_test = [0.04 0.05 0.02 0.06];
z_real = [2.6 4.4 7.7 5];

x = 1:4:21;
y = 0.01:0.01:0.07;
z = [0 0 0 0 0 0 0; 6.3 4.6 3.85 3.3 3 2.8 2.3; 8.7 6.25 5.15 4.5 4 3.8 3.2; 10.05 7.3 6 5.25 4.8 4.4 3.85; 11.2 8 6.7 5.8 5.3 5.2 4.5; 12 8.65 7.1 6.2 5.6 5.2 4.5]';
[X, Y] = meshgrid(x, y);
xx=x(1):0.8:x(end);
yy=y(1):0.002:y(end);
[XX,YY]=meshgrid(xx,yy);
xp=reshape(X,1,[]);
yp=reshape(Y,1,[]);
zp=reshape(z,1,[]);
d=length(xp);
Z=[ones(1,d); xp; yp];
C=zp*Z'*inv(Z*Z');
F1  = @(a, b) (C(1) + C(2)*a + C(3)*b);
z_test = F1(x_test, y_test)
mse = mean((z_real-z_test).^2);
disp(mse)
subplot(1, 3, 3);
plot3(X,Y,z,'.b', MarkerSize=10);
title('c) F1 w = c1 + c2*x + c3*y 42 samples MSE = ', num2str(mse));
hold on
W = F1(XX,YY);
mesh(XX,YY,W);


x = [1 21];
y = [0.01 0.07];
z = [0 12; 0 4.5];
[X, Y] = meshgrid(x, y);
xx=x(1):0.8:x(end);
yy=y(1):0.002:y(end);
[XX,YY]=meshgrid(xx,yy);
xp=reshape(X,1,[]);
yp=reshape(Y,1,[]);
zp=reshape(z,1,[]);
d=length(xp);
Z=[ones(1,d); xp; yp];
C=zp*Z'*inv(Z*Z');
F1  = @(a, b) (C(1) + C(2)*a + C(3)*b);
z_test = F1(x_test, y_test)
mse = mean((z_real-z_test).^2);
disp(mse)
subplot(1, 3, 1);
plot3(X,Y,z,'.b', MarkerSize=10);
title('a) F1 w = c1 + c2*x + c3*y 4 samples MSE = ', num2str(mse));
hold on
W = F1(XX,YY);
mesh(XX,YY,W);

x = [1 11 21];
y = [0.01 0.04 0.07];
z = [0 0 0; 9.5 4.95 3.55; 12 6.2 4.5]';
[X, Y] = meshgrid(x, y);
xx=x(1):0.8:x(end);
yy=y(1):0.002:y(end);
[XX,YY]=meshgrid(xx,yy);
xp=reshape(X,1,[]);
yp=reshape(Y,1,[]);
zp=reshape(z,1,[]);
d=length(xp);
Z=[ones(1,d); xp; yp];
C=zp*Z'*inv(Z*Z');
F1  = @(a, b) (C(1) + C(2)*a + C(3)*b);
z_test = F1(x_test, y_test)
mse = mean((z_real-z_test).^2);
disp(mse)
subplot(1, 3, 2);
plot3(X,Y,z,'.b', MarkerSize=10);
title('b) F1 w = c1 + c2*x + c3*y 9 samples MSE = ', num2str(mse));
hold on
W = F1(XX,YY);
mesh(XX,YY,W);