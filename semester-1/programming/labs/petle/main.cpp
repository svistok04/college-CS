// Petle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
    // Zadanie 1.
    printf("Zadanie 1. Program wczytujacy ze standardowego wejscia dwie dodatnie liczby calkowite n i m,"
        "i wypisujacy w kolejnych wierszach na standardowym wyjœciu wszystkie dodatnie wielokrotnoœci n mniejsze od m.\n");
    int n, m;
    scanf("%d %d", &n, &m);
    while (n <= 0 || m <= 0)
    {
        printf("Wprowadzone wartosci nie sa dodatne!\n");
        scanf("%d %d", &n, &m);
    }
    int c = 0;
    for (int i = 1; ; i++) {
        c = n * i;
        if (c >= m) break;
        printf("%d\n", c);
    }


    // Zadanie 2.
    printf("Zadanie 2. Program wczytujacy ze standardowego wejscia dwie dodatnie liczby calkowite n i m, i wypisujacy na"
        " standardowym wyjsciu m pierwszych wielokrotnosci liczby n.\n");
    scanf("%d %d", &n, &m);
    while (n <= 0 || m <= 0) {
        printf("Wprowadzone wartosci nie sa dodatne!\n");
        scanf("%d %d", &n, &m);
    }
    for (int i = 1; i <= m; i++) {
        c = n * i;
        printf("%d\n", c);
    }
    // Zadanie 3.
    printf("Zadanie 3. Program wczytujacy ze standardowego wejscia trzy dodatnie liczby calkowite n, m i k, i wypisujacy w "
        "kolejnych wierszach wszystkie wielokrotnosci n wieksze od m i mniejsze od k.\n");
    int k;
    c = 0;
    scanf("%d %d %d", &n, &m, &k);
    while (n <= 0 || m <= 0 || k <= 0) {
        printf("Wprowadzone wartosci nie sa dodatne!\n");
        scanf("%d %d %d", &n, &m, &k);
    }
    while (m + n >= k) {
        printf("Przeczytaj zadanie ponownie i wpisz nowe dane, inaczej program nie ma wyniku!\n");
        scanf("%d %d %d", &n, &m, &k);
    }
    for (int i = 1; i < k / n; i++) {
        c = n * i;
        if (c > m) {
            printf("%d\n", c);
        }
    }

    // Zadanie 4.
    printf("Zadanie 4. Program, ktory wczytuje ze standardowego wejscia nieujemna liczbe calkowita n i wypisuje na "
        "standardowym wyjsciu liczbe n!.\n");
    scanf("%d", &n);
    while (n < 0) {
        printf("Wprowadzona wartosc jest ujemna!\n");
        scanf("%d", &n);
    }
    c = 1;
    for (int i = 1; i <= n; i++) {
        c *= i;
    }
    printf("%d\n", c);

    // Zadanie 5.
    printf("Zadanit 5. Program, ktory wczytuje ze standardowego wejscia nieujemna liczbe calkowit¹ n i wypisuje na"
        " standardowym wyjsciu sume kwadratow liczb od 0 do n, czyli wartosc 0^2 + 1^2 + 3^2 + ... + n^2.\n");
    scanf("%d", &n);
    while (n < 0)
    {
        printf("Wprowadzona wartosc jest ujemna!\n");
        scanf("%d", &n);
    }
    c = 0;
    for (int i = 0; i <= n; i++) {
        c += i ^ 2;
    }
    printf("%d\n", c);

    // Zadanie 6.
    printf("Zadanie 6. Program, ktory wczytuje ze standardowego wejscia liczbê cal³kowita ¹ n (n > 2) i wypisuje na standardowym wyjsciu"
        " iloczyn liczb parzystych z zakresu od 2 do n(czyli 2 * 4 * . ..* n dla n parzystych i 2 * 4 * . ..*(n - 1)"
        " w przeciwnym wypadku).\n");
    scanf("%d", &n);
    while (n < 2)
    {
        printf("Wprowadzona wartosc jest mniejsza od 2!\n");
        scanf("%d", &n);
    }
    c = 1;
    if (n % 2 == 0)
    {
        for (int i = 2; i <= n; i += 2)
        {
            c *= i;
        }
    }
    else
    {
        for (int i = 2; i <= (n - 1); i += 2)
        {
            c *= i;
        }
    }
    printf("%d", c);

    // Zadanie 7.
    printf("Zadanie 7. Program, ktory wczytuje ze standardowego wejscia dwie liczby ca³kowite n i m (zakladamy, ¿e n < m)"
        " i wypisuje na standardowym wyjsciu liczbe n * . ..* m.\n");
    scanf("%d %d", &n, &m);
    while (n >= m)
    {
        printf("n musi byc mniejsze od m!\n");
        scanf("%d %d", &n, &m);
    }
    for (int i = n; i < m; i++)
    {
        c *= i;
    }
    printf("%d\n", c);

    // Zadanie 8.

    printf("Zadanie 8. Program, ktory wczytuje ze standardowego wejscia nieujemna liczbe calkowita n i wypisuje na"
        " standardowym wyjsciu element ciagu Fibonacciego o indeksie n.\n");
    scanf("%d", &n);
    while (n < 0)
    {
        printf("Wprowadzona wartosc jest ujemna!\n");
        scanf("%d", &n);
    }
    int t1 = 0, t2 = 1;

    for (int i = 1; i < n; i++)
    {
        c = t1 + t2;
        t1 = t2;
        t2 = c;
    }
    if (n == 1) c = 1;
    printf("%d", c);

    // Zadanie 9.
    printf("Zadanie 9. Program, ktory wczytuje ze standardowego wejscia dodatnie liczby calkowite n i m, i wypisuje na "
        "standardowym wyjsciu najwiekszy wspolny dzielnik tych liczb.\n");
    int  a = 0;
    scanf("%d %d", &n, &m);
    while (n <= 0 || m <= 0)
    {
        printf("Wprowadzone wartosci nie sa dodatne!\n");
        scanf("%d %d", &n, &m);
    }
    while (n % m > 0)
    {
        a = n % m;
        n = m;
        m = a;
    }
    printf("%d", m);

    /*
    // Zadanie 10.
    float l;
    printf("Zadanie 10. Program, ktory wczytuje ze standardowego wejscia nieujemna liczbe n i wypisuje na standardowym "
           "wyjsciu wartosc ⌊√n⌋(wartość √n  zaokrągloną  w  dół  do  najbliższej  wartości  całkowitoliczbowej)). Program"
           " napisz bez uzycia funkcji z biblioteki matematycznej.\n");
    scanf("%d", &l);
    while (l < 0)
    {
        printf("Wprowadzona wartosc jest ujemna!\n");
        scanf("%d", &l);
    }
*/
}