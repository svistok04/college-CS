syms x;
F(x) = x^cos(x);

h = 0.2;
x = 0:h:10;

y = F(x);

dif = diff(F);
df = dif(x);

df2 = (F(x+h)-F(x))/h;

df3 = (F(x+h)-F(x-h)) / (2*h);

df5 = (F(x-(2*h)) - 8*F(x-h) + 8 * F(x+h) - F(x+(2*h))) / (12 * h);

figure;
hold on;
xlabel('x')
ylabel('df/dx')
plot(x, y, 'r');
plot(x, df, 'b');
plot(x, df2, 'm');
plot(x, df3, 'y');
plot(x, df5, 'g');
legend('F(X)', 'df1', 'df2', 'df3', 'df5')
grid on;