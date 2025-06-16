clear
close all
clc
% zadanie 1
x = -3:0.5:3;
y = [-0.25, -0.5, -0.75, -0.55, 0.25, 0, 0.25, 0.5, 0.25, 0, -0.25, -0.5, -0.25];
% zadanie 2
x_testowy = 0.75;
y_testowy = 0.41;
y1 = interp1(x, y, x_testowy, 'nearest');
y2 = interp1(x, y, x_testowy, 'linear');
y3 = interp1(x, y, x_testowy, 'spline');
y4 = interp1(x, y, x_testowy, 'cubic');

err1 = abs(y_testowy - y1);
err2 = abs(y_testowy - y2);
err3 = abs(y_testowy - y3);
err4 = abs(y_testowy - y4);
fprintf('nearest err %f, linear err %f, spline err %f, cubic err %f \n', err1, err2, err3, err4);
% nearest err 0.160000, linear err 0.035000, spline err 0.000424, cubic err 0.003750
disp('Zad 2 najlepsza metoda to spline')


% zadanie 3
xx = -3:0.01:3;
yy = interp1(x, y, xx, 'nearest');
plot(xx, yy);
hold on

yy = interp1(x, y, xx, 'linear');
plot(xx, yy);
hold on

yy = interp1(x, y, xx, 'spline');
plot(xx, yy);
hold on

yy = interp1(x, y, xx, 'cubic');
plot(xx, yy);
hold on

legend('nearest', 'linear', 'spline', 'cubic', 'points');

plot(x, y, 'o');
hold on

disp('Zad 3 - najlepsza metoda to cubic');

% zadanie 4
for j = 1:12
    p = polyfit(x, y, j);
    y5 = polyval(p, xx);
    figure
    plot(xx, y5, x, y, 'o');
    title('wielomian ', num2str(j));
end
disp('Zad 4 - najlepszy wielomian to wielomian stopniu 10');

% zadanie 5
p = polyfit(x, y, 10);
y5 = polyval(p, x_testowy);
err5 = abs(y5 - y_testowy);
fprintf('nearest err %f, linear err %f, spline err %f, cubic err %f, polyval err %f \n', err1, err2, err3, err4, err5);
% nearest err 0.160000, linear err 0.035000, spline err 0.000424, cubic err 0.003750, polyval err 0.055842 
disp('zad 5 - dla podanych danych w danym punkcie najlepiej wypada interpolacja spline')