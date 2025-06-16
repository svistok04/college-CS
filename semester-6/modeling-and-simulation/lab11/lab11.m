clear all;
close all;
clc ;

load('lab11_data1.mat') % dane testowe
load('lab11_data2.mat') % dane uczące

% model 1
X_uczace = data2(:, 1:2)';
Z_uczace1 = data2(:, 3:6)'; % (a1x' + a2y' + a3x + a4y)
A1 = X_uczace * Z_uczace1' * inv(Z_uczace1 * Z_uczace1');

% testowanie
xpp_testowe = data1(:, 1)';
ypp_testowe = data1(:, 2)';
xpp1 = A1(1, :) * data1(:, 3:6)';
ypp1 = A1(2, :) * data1(:, 3:6)';
xpp_mse1 = mean((xpp_testowe - xpp1).^2);
ypp_mse1 = mean((ypp_testowe - ypp1).^2);
err1 = mean(xpp_mse1 + ypp_mse1); % 7.0921e-30

% model 2
Z_uczace2 = [data2(:, 3).^2, data2(:, 4).^2, data2(:, 5), data2(:, 6), data2(:, 3).*data2(:, 4)]';
A2 = X_uczace * Z_uczace2' * inv(Z_uczace2 * Z_uczace2');

xpp2 = A2(1, :) * [data1(:, 3).^2, data1(:, 4).^2, data1(:, 5), data1(:, 6), data1(:, 3).*data1(:, 4)]';
ypp2 = A2(2, :) * [data1(:, 3).^2, data1(:, 4).^2, data1(:, 5), data1(:, 6), data1(:, 3).*data1(:, 4)]';
xpp_mse2 = mean((xpp_testowe - xpp2).^2);
ypp_mse2 = mean((ypp_testowe - ypp2).^2);
err2 = mean(xpp_mse2 + ypp_mse2); % 0.0904

% zadanie 3 euler
d2x = @(d1x, d1y, x, y) A1(1, 1) * d1x + A1(1, 2) * d1y + A1(1, 3) * x + A1(1, 4) * y;
d2y = @(d1x, d1y, x, y) A1(2, 1) * d1x + A1(2, 2) * d1y + A1(2, 3) * x + A1(2, 4) * y;
h = 2^(-8);
stop = 500;
x0 = [60];
y0 = [0];
x1 = [0];
y1 = [0];
x2 = [d2x(x1(end), y1(end), x0(end), y0(end))];
y2 = [d2y(x1(end), y1(end), x0(end), y0(end))];
disp(x2);
disp(y2);
for t = h : h : stop
    x0(end + 1) = x0(end) + x1(end) * h;
    y0(end + 1) = y0(end) + y1(end) * h;
    x1(end + 1) = x1(end) + x2(end) * h;
    y1(end + 1) = y1(end) + y2(end) * h;
    x2(end + 1) = d2x(x1(end), y1(end), x0(end), y0(end));
    y2(end + 1) = d2y(x1(end), y1(end), x0(end), y0(end));

end
plot(data1(:, 5), data1(:, 6), 'b');
title('data');
figure
plot(x0, y0, 'r');
title('Euler');