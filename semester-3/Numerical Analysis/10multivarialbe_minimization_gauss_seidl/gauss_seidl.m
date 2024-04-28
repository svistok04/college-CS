F = @(x, y) 2*x.^2+y.^2+x*y-6*x-5*y+8;
F_vector = @(v) F(v(1), v(2));
precision = 0.001;
a = -5; b = 5;
x_curr = y_curr = -4;
x_prev = y_prev = Inf;
path = [x_curr, y_curr];
iterations = 0;
while (sqrt((x_curr-x_prev)^2+(y_curr-y_prev)^2) > precision)
    iterations = iterations + 1;
    x_prev = x_curr;
    y_prev = y_curr;
    a_golden = a;
    b_golden = b;
    while (abs(b_golden-a_golden) > precision)
        x1 = a_golden + 0.382 * (b_golden-a_golden);
        x2 = a_golden + 0.618 * (b_golden-a_golden);
        if (F(x1, y_curr) < F(x2, y_curr))
            b_golden = x2;
        else
            a_golden = x1;
        end
    end
    x_curr = (a_golden + b_golden) / 2;
    path = [path; x_curr, y_curr];
    a_golden = a;
    b_golden = b;
    while (abs(b_golden-a_golden) > precision)
        y1 = a_golden + 0.382 * (b_golden-a_golden);
        y2 = a_golden + 0.618 * (b_golden-a_golden);
        if (F(x_curr, y1) < F(x_curr, y2))
            b_golden = y2;
        else
            a_golden = y1;
        end
    end
    y_curr = (a_golden + b_golden) / 2;
    path = [path; x_curr, y_curr];
end
fprintf('Minimum found at x = %f, y = %f\n', x_curr, y_curr);
fprintf('Iterations = %d\n', iterations);
fprintf('Minimum value = %f\n', F(x_curr, y_curr));
[X, Y] = meshgrid(-5:0.1:5, -5:0.1:5);
contour(X, Y, F(X, Y), 50);
hold on;
plot(path(:,1), path(:,2), 'r-o', 'LineWidth', 2);
xlabel('x');
ylabel('y');

[x_min, fval] = fminsearch(F_vector, [-4, -4]);
fprintf('Minimum found at x = %f, y = %f, with function value = %f\n', x_min(1), x_min(2), fval);
