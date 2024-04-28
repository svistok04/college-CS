%matlab first
%ceny = [2, 1.5, 3];
%bialko = [4, 6, 15];
%tluszcze = [2, 2, 0];
%witaminy = [5, 3, 4];
%weglowodany = [7, 3, 12];
%skladnikiOdzywcze = [bialko; tluszcze; witaminy; weglowodany];
%minimumSkadnikow = [250, 60, 100, 220];
%lb = zeros(3, 1);
%ub = Inf(3,1);
%
%[x, fval] = glpk(ceny, -skladnikiOdzywcze, -minimumSkadnikow, lb, ub);
%
%fprintf('Najtanszy zestaw kosztuje %f zl i sklada sie z:\n', fval);

%c = [2; 1.5; 3];  % Cost vector: [sandwiches; dumplings; sweets]
%
%A = [-4, -6, -15;  % Protein
%     -2, -2, 0;    % Fat
%     -5, -3, -4;   % Vitamins
%     -7, -3, -12]; % Carbohydrates
%
%b = [-250; -60; -100; -220];  % Minimum requirements, negated
%
%ctype = repmat('U', size(b));
%
%lb = zeros(3, 1);  % You cannot buy negative amounts
%ub = [];           % No upper bounds specified
%
%vartype = repmat('I', size(c));
%
%[x, fval] = glpk(c, A, b, lb, ub, ctype, vartype);
%
%disp("Amounts to purchase:");
%disp(x);
%disp("Minimum cost:");
%disp(fval);
