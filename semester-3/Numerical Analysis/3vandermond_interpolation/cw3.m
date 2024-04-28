x = input('Podaj wspolczynyiki x: ');
y = input('Podaj wspolczynniki y: ');


n = length(x);

xx = min(x):0.1:max(x);

m = length(xx);

V = zeros(n, n);

for i = 1:n
    for j = 1:n
        V(i,j) = x(i).^(j-1);  
    end
end 


A = V \ y.';

disp(A);

yy = zeros(size(xx));

for i = 1:n
    yy = yy + A(i) * xx.^(i-1);
end


figure;
hold on;

plot(x, y, 'o');

plot(xx, yy, 'r');

grid on;

