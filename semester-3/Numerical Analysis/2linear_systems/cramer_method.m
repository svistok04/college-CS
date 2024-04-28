function x = cramer_method(A, b)

disp('Metoda Cramera');

W = det(A);

for i = 1:max(size(A))
    Ai = A;
    Ai(:,i) = b;
    Wi = det(Ai);
    x(i,1) = Wi/W;
end

disp(x)

end