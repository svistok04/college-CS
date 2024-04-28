x = input("Współrzedne X: ");
y = input("Współrzedne Y: ");
p = input("Stopień wielomianu: ");

n=length(x);

psi = zeros(p+1);
F = zeros(p+1, 1);

for k = 1:n
   for i = 1:p+1
       for j = 1:p+1
          psi(i,j) = psi(i,j) + x(k)^(i+j-2);
       end
   end
end
for j = 1:n
    for i = 1:p+1
       F(i) = F(i) + x(j)^(i-1)*y(j);
    end
end

A = psi \ F;

xx = min(x):0.1:max(x);
W = 0;
for i = 1:p+1
    W = W + A(i) * xx.^(i-1);
end

plot(x, y, 'or');
hold on;
plot(xx, W, 'b');
