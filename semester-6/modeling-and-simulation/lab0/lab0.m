clc
clear
% zadanie 1
first = @(x) sin(x) + cos(x);
first(1:20)
second = @(x) exp(x) + log(x);
second(1:20)
third = @(x, y) sin(x) .* cos(y);
third(1:20, 1:20)

% zadanie 2
x = 0.1:0.1:4;
plot(x, first(x));
hold on
plot(x, second(x));
legend('sin(x) + cos(x)', 'e^x + log(x)');

% zadanie 3
x = -2*pi:0.1:2*pi;
y = x;
[X, Y] = meshgrid(x, y);
figure
surf(X, Y, third(X, Y));

% zadanie 4
x = rand(1, 7) * 3 + 2;
y = rand(1, 7) * 4 + 3;
figure
fun1(x, y);



function fun1(x, y)
    plot(x, y, 'sr', MarkerSize=15);
    hold on
    plot(x, y, '--k', LineWidth=3);

end