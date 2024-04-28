F = @(x) x^3+2*x^2-100;
y = fzero(F, [4, 4.5]);
disp(y);