F = @(x) x^3+x^2-20*x;
a = 0;
b = 6;
precision = 0.01;

disp('Metoda zlotego podzialu');
counter_golden = 0;
a_golden = a;
b_golden = b;
while (abs(b_golden-a_golden) > precision)
    counter_golden = counter_golden + 1;
    x1 = a_golden+0.382*(b_golden-a_golden);
    x2 = a_golden+0.618*(b_golden-a_golden);
    if F(x1) < F(x2)
        b_golden = x2;
    else
        a_golden = x1;
    end
end
x_min = (a_golden+b_golden)/2;
fprintf("Wynik: %f, Liczba iteracji: %d;\n", x_min, counter_golden);

disp('Metoda polowienia');
counter_bisection = 0;
a_bisection = a;
b_bisection = b;
x_min = 0;
precision = 0.001;
while abs(b_bisection-a_bisection) > precision
    counter_bisection = counter_bisection + 1;
    x_min = (a_bisection + b_bisection) / 2;
    x1 = (a_bisection + x_min) / 2;
    x2 = (b_bisection + x_min) / 2;
    if F(x_min) > F(x1)
        b_bisection = x_min;
    elseif F(x_min) < F(x2)
        a_bisection = x1;
        b_bisection = x2;
    else
        a_bisection = x_min;
    end
end
fprintf("Wynik: %f, Liczba iteracji: %d;\n", x_min, counter_bisection);

disp('Metoda Newtona');
counter_newton = 0;
x_old = a;
h = 0.01;
x_new = 1000;
temp = 0;
while abs(x_new - temp) > precision
    derivative = (F(x_old + h) - F(x_old - h))/(2 * h);
    derivative2nd = (F(x_old) - 2*F(x_old-h) + F(x_old-2*h)) / h^2;
    temp = x_old;
    x_new = x_old - derivative/derivative2nd;
    x_old = x_new;
    counter_newton = counter_newton + 1;
end
x_min = x_new;
fprintf("Wynik: %f, Liczba iteracji: %d;\n", x_min, counter_newton);

disp('Metoda wbudowana')
x_min = fminbnd(F, a, b);
fprintf("Wynik: %f\n", x_min);
