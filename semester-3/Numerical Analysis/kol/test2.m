F = @(x) nthroot(2*x, 3);
F_der = @(x) nthroot(2, 3)/(3*nthroot(x^2, 3));
F_der2 = @(x) -(2^(4/3))/(9*x^(5/3));

x = 2;
h = 0.1;

df1 = (F(x+h) - F(x)) / h;
df2 = (F(x) - F(x-h)) / h;
df3 = (F(x+h)-F(x-h)) / (2*h);
second = (F(x-(3*h)) + 16*F(x-h) - 30*F(x) + 16*F(x+h) - F(x+(3*h))) / (12 * h^2);
second2 = F_der2(x);
second3 = (2*F(x) - 5*F(x+h) + 4*F(x+2*h) - F(x+3*h))/h^2;
dokl = F_der(x);
disp(df1);
disp(df2);
disp(df3);
disp(dokl);
disp(second);
disp(second2);
disp(second3);