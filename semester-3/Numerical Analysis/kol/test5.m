x = [-2, 1, 3, 7];
y = [0, 2, 3, 11];
x_point = 6;

y_linear = interp1(x, y, x_point, 'linear');
%y_spline = spline(x, y, x_point);
y_spline = interp1(x, y, x_point, 'spline');
p = polyfit(x, y, 1);
disp(p);
y_poly = polyval(p, x_point);
disp(y_linear);
disp(y_spline);
disp(y_poly);