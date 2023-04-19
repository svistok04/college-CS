
#include <iostream>
#include <math.h>

using std::cout;

int main()
{
    int a, b, c;
    // 1.
    printf("Zadanie 1.\n");
    printf("Wpisz liczbe calkowita: \n");
    scanf("%d", &a);
    a = (a < 0) ? -a : a;
    printf("%d \n\n", a);

    // 2.
    printf("Zadanie 2.\n");
    printf("Wpisz dwie liczby calkowite:\n");
    scanf("%d %d", &a, &b);
    if (a <= b)
    {
        printf("%d\n\n", b);
    }
    else printf("%d\n\n", a);

    // 3.
    printf("Zadanie 3.\n");
    printf("Wpisz trzy liczby calkowite: \n");
    scanf("%d %d %d", &a, &b, &c);
    if (a <= b)
    {
        if (b <= c)
        {
            printf("%d\n\n", c);
        }
        else
        {
            printf("%d\n\n", b);
        }
    }
    else
    {
        printf("%d\n\n", a);
    }

    // 4.
    printf("Zadanie 4.\n");
    printf("Wpisz dwie liczby calkowite:\n");
    scanf("%d %d", &a, &b);
    if (abs(a) <= abs(b))
    {
        printf("%d\n\n", b);
    }
    else printf("%d\n\n", a);

    // 5.
    printf("Zadanie 5.\n");
    printf("Napisz 1 zeby wprowadzic podstawe i wysokosc trojkata lub 2 zeby wprowadzic wszystkie go strony: \n");
    int z = 0;
    float j, k, l, p;
    scanf("%d", &z);
    switch (z)
    {
        case 1:
            printf("Wprowadz podsawe i wysokosc:");
            scanf("%f %f", &j, &l);
            printf("Pole trojkata wynosi: %f\n\n", (j+ l) / 2);
            break;

        case 2:
            printf("Wprowadz wszystkie strony");
            scanf("%f %f %f", &j, &k, &l);
            p = (j + k + l) / 2;
            printf("Pole trojkata wynosi: %f\n\n", sqrt(p * (p - j) * (p - k) * (p - l)));
            break;

        default: "Wprowadziles zla wartosc\n\n"; break;
    }

    // 6.
    printf("Zadanie 6.\n");
    int a1, b1, c1, a2, b2, c2;
    printf("Wprowadz wspolczynniki pierwszego rowniania oraz go wynik");
    scanf("%d %d %d", &a1, &b1, &c1);
    printf("Wprowadz wspolczynniki drugiego rowniania oraz go wynik");
    scanf("%d %d %d", &a2, &b2, &c2);
    float A = float(a1 * b2 - a2 * b1);
    float A1 = float(c1 * b2 - b1 * c2);
    float A2 = float(a1 * c2 - c1 * a2);
    if (A != 0 && A1 != 0 && A2 != 0)
    {
        printf("X = %f, Y = %f\n\n", A1 / A, A2 / A);
    }
    else printf("Brak rozwiazan\n\n");

    // 7.
    printf("Zadanie 7.\n");
    printf("Wprowadz wspolczynniki rowniania kwadratowego");
    scanf("%d %d %d", &a, &b, &c);
    float D = sqrt(float(b ^ 2 - 4 * a * c));
    if (D > 0)
    {
        float x1 = float(-b + D) / (2 * a);
        float x2 = float(-b - D) / (2 * a);
        printf("Wynik: %f %f \n\n", x1, x2);
    }
    else if (D == 0)
    {
        float x = float(-b) / (2 * a);
        printf("Wynik: %f\n\n", x);
    }
    else printf("Brak wyniku\n\n");

    // 8.
    printf("Zadanie 8.\n");
    printf("Napisz 1 zeby wprowadzic strone kwadratu, 2 dla stron prostokata czy 3 dla trojkata");
    scanf("%d", &z);
    switch (z)
    {
        case 1:
            printf("Wprowadz strone kwadratu:");
            scanf("%d", &a);
            printf("Pole kwadratu wynosi: %d", a * a);
            break;

        case 2:
            printf("Wprowadz strony prostokata");
            scanf("%d %d", &a, &b);
            printf("Pole prostokata wynosi: %d", a * b);
        case 3:
            printf("Wprowadz wszystkie strony trojkata");
            scanf("%f %f %f", &j, &k, &l);
            p = (j + k + l) / 2;
            printf("Pole trojkata wynosi: %f\n\n", sqrt(p * (p - j) * (p - k) * (p - l)));
            break;

        default: "Wprowadziles zla wartosc\n\n"; break;
    }

    // 9.
    printf("Zadanie 9.\n");
    printf("Wybierz operacje arytmetryczna (+, -, *, /):");
    char o;
    scanf("%c", &o);
    printf("Wprowadz dwie cyfry:");
    scanf("%f, %f", &k, &l);
    switch (o)
    {
        case '+':
            printf("Wynik: %f", k + l);
            break;

        case '-':
            printf("Wynik: %f", k - l);
            break;

        case '*':
            printf("Wynik: %f", k * l);
            break;

        case '/':
            printf("Wynik: %f", k / l);
            break;

        default: printf("Wprowadziles zly symbol"); break;
    }

}
