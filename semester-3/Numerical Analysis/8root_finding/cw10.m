F = @(x) exp(x) + x.^2 + - 2;


x = -2:0.1:2;
y = F(x);
plot(x, y, LineWidth=2);
grid on
axis([-2, 2, -2, 10]);
a = input("Wprowadz a = ");
b = input("Wprowadz b = ");

disp('Metoda polowienia');
counter_bisection = 0;
a_bisection = a;
b_bisection = b;
c = 0;
precision = 0.001;
while (abs(b_bisection-a_bisection) > precision) 
    counter_bisection = counter_bisection + 1;
    c = (a_bisection + b_bisection) / 2;
    if F(c) * F(a) < 0
        b_bisection = c;
    else
        a_bisection = c;
    end
end
fprintf("Wynik: %f \n", c);
fprintf("Liczba iteracji: %d \n", counter_bisection);

disp('Metoda reguly Falsi');
counter_falsi = 1;
xi = (a*F(b)-b*F(a))/(F(b)-F(a));
if F(a)*F(xi) < 0
    xi1 = (xi*F(a)-a*F(xi))/(F(a)-F(xi)); 
elseif F(b)*F(xi) < 0
    xi1 = (xi*F(b)-b*F(xi))/(F(b)-F(xi)); 
end
while abs(xi1 - xi) > precision
    counter_falsi = counter_falsi + 1;
    xi = xi1;
    if F(a)*F(xi) < 0
        xi1 = (xi*F(a)-a*F(xi))/(F(a)-F(xi)); 
    elseif F(b)*F(xi) < 0
        xi1 = (xi*F(b)-b*F(xi))/(F(b)-F(xi)); 
    end
end
fprintf("Wynik: %f \n", xi1);
fprintf("Liczba iteracji: %d \n", counter_falsi);

disp('Metoda Newtona');
counter_newton = 1;
xi = a;
h = 0.5;
derivative = (F(xi + h) - F(xi - h))/(2 * h);
xi1 = xi - F(xi) / derivative;
while abs(xi1 - xi) > precision
    xi = xi1;
    derivative = (F(xi + h) - F(xi - h))/(2 * h);
    xi1 = xi - F(xi) / derivative;
    counter_newton = counter_newton + 1;
end
fprintf("Wynik: %f \n", xi1);
fprintf('Liczba iteracji: %d \n', counter_newton);

disp('Metoda wdudowana')
fprintf("%f \n",fzero(F, [a, b]));
