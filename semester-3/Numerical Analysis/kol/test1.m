syms x1 x2 x3 x4;
eqn1 = x1 + x2 + x3 == 5;
eqn2 = -x2 + 2*x3 - 5*x4 == 0;
eqn3 = 3*x1 - x3 - x4 == -3;
eqn4 = x1 + 2*x2 -2*x3 == -1;
[A,B] = equationsToMatrix([eqn1, eqn2, eqn3, eqn4], [x1, x2, x3, x4]);
X = linsolve(A,B)