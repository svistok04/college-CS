x = 0:0.5:3;
y = sin(x.^2);

xi = 0:0.001:3;

yi = sin(xi.^2);

w_linear = interp1(x, y, xi, 'linear');

w_spline = interp1(x, y, xi, 'spline');

w_cubic = interp1(x, y, xi, 'cubic');


subplot(2, 2, 1);
plot(x, y, 'o', xi, w_linear, xi, yi, '--');
axis([0, 3, -1, 1.5]);

title('Interpolacja liniowa');

subplot(2, 2, 2);
plot(x, y, 'o', xi, w_spline, xi, yi, '--');
axis([0, 3, -1, 1.5]);

title('Interpolacja funkcjami sklejonymi');

subplot(2, 2, 3);
plot(x, y, 'o', xi, w_cubic, xi, yi, '--');
axis([0, 3, -1, 1.5]);

title('Interpolacja wielomianami 3-go stopnia');

subplot(2, 2, 4);
A = polyfit(x,y,length(x)-1);
w = polyval(A, xi);
plot(x, y, 'o', xi, w, xi, yi, '--');
axis([0, 3, -1, 1.5]);

title('Interpolacja wielomianowa');

sgtitle('Metody interpolacji dla y = sin(x^2)');