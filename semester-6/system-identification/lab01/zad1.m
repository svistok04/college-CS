% zadanie 1
clc
clear all
close all

x = 1:4:17;
y = 0.01:0.01:0.05;
z = [0 0 0 0 0; 6.3 4.6 3.85 3.3 3; 8.7 6.25 5.15 4.5 4 ; 10.05 7.3 6 5.25 4.8 ; 11.2 8 6.7 5.8 5.3]';
[X, Y] = meshgrid(x, y);
xx=x(1):0.8:x(end);
yy=y(1):0.002:y(end);
[XX,YY]=meshgrid(xx,yy);
xp=reshape(X,1,[]);
yp=reshape(Y,1,[]);
zp=reshape(z,1,[]);
d=length(xp);
Z=[xp;yp;ones(1,d)];
C=zp*Z'*inv(Z*Z');
F1  = @(a, b) (C(1)*a + C(2)*b + C(3));
%disp(C);

%plot3(X,Y,z,'.b', MarkerSize=10);
%title('F1 w = c1*x + c2*y + c3')
%hold on
%W = F1(XX,YY);
%mesh(XX,YY,W);

Z=[xp.^2;yp.^2;ones(1,d)];
C=zp*Z'*inv(Z*Z');
F2  = @(a, b) (C(1)*a.^2 + C(2)*b.^2 + C(3));
subplot(2, 2, 1);
plot3(X, Y, z, '.b', MarkerSize=10);
title('F2 w = c1*x^2 + c2*y^2 + c3');
hold on
W = F2(XX, YY);
mesh(XX, YY, W);
x_test = 7:4:15;
y_test = [0.04 0.05 0.02];
z_real = [4 4.5 7.7];
z_test = F2(x_test, y_test);
%disp(z_test);
mse = mean((z_real-z_test).^2);
disp(mse)

Z=[xp.^2;yp.^2;xp.*yp;ones(1,d)];
C=zp*Z'*inv(Z*Z');
F6  = @(a, b) (C(1)*a.^2 + C(2)*b.^2 + C(3)*a.*b + C(4));
subplot(2, 2, 2);
plot3(X, Y, z, '.b', MarkerSize=10);
title('F6 w = c1*x^2 + c2*y^2 + c3*x*y + c4');
hold on
W = F6(XX, YY);
mesh(XX, YY, W);
z_test = F6(x_test, y_test);
%disp(z_test);
mse = mean((z_real-z_test).^2);
disp(mse)

Z=[xp;yp.^3;yp.^2;yp;ones(1,d)];
C=zp*Z'*inv(Z*Z');
F10 = @(a, b) (C(1)*a + C(2)*b.^3 + C(3)*b.^2 + C(4)*b + C(5));
subplot(2, 2, 3);
plot3(X, Y, z, '.b', MarkerSize=10);
title('F10 w = c1*x + c2*y^3 + c3*y^2 + c4*y + c5');
hold on
W = F10(XX, YY);
mesh(XX, YY, W);
z_test = F10(x_test, y_test);
%disp(z_test);
mse = mean((z_real-z_test).^2);
disp(mse)

Z=[xp.^3;xp.^2;yp.^3;yp.^2;xp.^2.*yp.^2;xp.*yp;ones(1,d)];
C=zp*Z'*inv(Z*Z');
F15 = @(a, b) (C(1)*a.^3 + C(2)*a.^2 + C(3)*b.^3 + C(4)*b.^2 + C(5)*a.^2.*b.^2 + C(6)*a.*b + C(7));
subplot(2, 2, 4);
plot3(X, Y, z, '.b', MarkerSize=10);
title('F15 w = c1*x^3 + c2*x^2 + c3*y^3 + c4*y^2 + c5*x^2*y^2 + c6*x*y + c7');
hold on
W = F15(XX, YY);
mesh(XX, YY, W);
z_test = F15(x_test, y_test);
%isp(z_test);
mse = mean((z_real-z_test).^2);
disp(mse)

% zadanie 2