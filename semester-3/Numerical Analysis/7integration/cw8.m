F = @(x) x.^cos(x);

a = 0;
b = 10;
n = 1000;
h = (b-a)/n;
x = a:h:b;

disp('metoda prostokatow');
J1 = sum(F(a:h:b-h))*h;
disp(J1);

disp('metoda trapezow');
J2 = (F(b)/2 + sum(F(a+h:h:b-h)) + F(a)/2)*h;
disp(J2);

disp('metoda simspona');
J3 = (F(a) + 4*sum(F(a+h:h*2:b-h)) + 2*sum(F(a+2*h:h*2:b-2*h)) + F(b))*(h/3);
disp(J3);

disp('metoda wbudowana');
J4 = quad(F, a, b);
disp(J4);

disp("metoda Monte Carlo");
hold on;
n = 10000;
c = max(F(x));
x1 = a + (b - a) * rand(1, n);
y1 = c * rand(1, n);
ntraf = 0;
for i = 1:n
    if F(x1(i)) > y1(i)
        ntraf = ntraf + 1;
        plot(x1(i), y1(i), 'og')
    else
        plot(x1(i), y1(i), 'or')
    end
end
J5 = c * (b - a) * ntraf / n;
title(J5)
disp(J5)