function x = gauss_jordan_elimination(A,b)

disp('Metoda Gaussa');

    n = size(b,1);
    x = zeros(n, 1);
    Ab = [A b];
    for i = 1:n
        Ab(i,:) = Ab(i,:)./Ab(i,i);
        for j = 1:n
            if i ~= j
                Ab(j,:) = Ab(j,:) - Ab(i,:) * Ab(j,i);
            end
        end
    end
    x = Ab(:,n+1);

disp(x)

end

