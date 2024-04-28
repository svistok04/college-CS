A = input('Wprowadz macierz wspolcz. A ');
b = input('Wprowadz macierz wynikow rownian b ');

metoda_gaussa = gauss_jordan_elimination(A, b);
metoda_cramera = cramer_method(A, b);
dzielenie_macierzy = matrix_division(A, b);
macierz_odwrotna = inverse_matrix(A, b);