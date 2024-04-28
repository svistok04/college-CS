 zysk = [100, 200];
 drewno = [5, 25];
 skora = [0.5, 0];
 klej = [100, 250];
 nakladPracy = [10, 10];
 zasoby = [drewno; skora; klej; nakladPracy];
 ograniczenia = [500, 15, 7500, 400];

 ctype = repmat('U', size(ograniczenia), 1);
lb = zeros(length(zysk), 1);
ub = [100, 100];

vartype = repmat('I', size(zysk));
[x, fval] = glpk(zysk, zasoby, ograniczenia, lb, ub, ctype, vartype, -1);
disp("Amounts to produce:");
disp(x);
disp("Maximum income:");
disp(fval);

%zysk = [100, 200];  % Profit for each product
%
%drewno = [5, 25];
%skora = [0.5, 0];
%klej = [100, 250];
%nakladPracy = [10, 10];
%
%zasoby = [drewno; skora; klej; nakladPracy];
%
%ograniczenia = [500; 15; 7500; 400];  % Resource limits
%
%ctype = repmat('U', length(ograniczenia), 1);
%
%lb = zeros(length(zysk), 1);
%
%ub = [100; 100];  % Assuming you can produce at most 100 of each product
%
%vartype = repmat('I', length(zysk), 1);
%
%[x, fval] = glpk(zysk, zasoby, ograniczenia, lb, ub, ctype, vartype, -1);
%
%disp("Amounts to produce:");
%disp(x);
%disp("Maximum income:");
%disp(fval);
%
