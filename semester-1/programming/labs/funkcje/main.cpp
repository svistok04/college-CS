
#include <iostream>
#include <cmath>

int scanOneWholeNumber();
int scanOneNonNegativeWholeNumber();
double scanOneNonNegativeNumber();
void zad1(int);
int zad2(int);
int zad3(int);
double zad45(int);
double zad67(int, int);
int zad8(int);
double zad9_1(double, double);
int zad9_2(double, int);
int zad10_1(int);
int zad10_2(int);
int zad11_1(int);
int zad11_2(int);

int main()
{
    int a, b;

     printf("Zadanie 1. Program, ktory wczytuje ze standardowego wejscia liczbe calkowita n i wypisuje na standardowe "
            "wyjscie wartosc bezwzgledna z n. \n");
     a = scanOneWholeNumber();
     zad1(a);

     printf("Zadanie 2. Program, ktory wczytuje ze standardowego wejscia nieujemna liczbe calkowita n i wypisuje na"
            " standardowym wyjsciu liczbe n! \n");
     a = scanOneNonNegativeWholeNumber();
     printf("%d \n", zad2(a));

     printf("Zadanie 3. Program, ktory wczytuje ze standardowego wejscia nieujemna liczbe calkowita n (n > 2) i wypisuje"
            " na standardowym wyjsciu najwieksza liczbe k taka, ze k dzieli n i k < n \n");
     scanf("%d", &a);
     while (a < 2)
     {
         printf("Liczba musi byc wieksza niz 2");
         scanf("%d", &a);
     }
     printf("%d", zad3(a));

     printf("Zadanie 4. Program, ktory dostaje jako argument nieujemna liczbe calkowita n i zwraca jako wartosc liczbe 2^n \n");
     a = scanOneNonNegativeWholeNumber();
     printf("%f \n", zad45(a));

     printf("Zadanie 5. Program, ktory dostaje jako argument liczbe calkowita n i zwraca jako wartosc liczbe 2^n \n");
     a = scanOneWholeNumber();
     printf("%f \n", zad45(a));

     printf("Zadanie 6. Program, ktory dostaje jako argumenty nieujemne liczby calkowite n i m, z ktorych co najmniej jedna jest "
            "rozna od zera i zwraca jako wartosc n^m \n");
     a = scanOneNonNegativeWholeNumber();
     b = scanOneNonNegativeWholeNumber();
     while (a == 0 || b == 0)
     {
         printf("Co najmniej jedna z liczb musi sie roznic od zera! Sprobuj ponownie \n");
         a = scanOneNonNegativeWholeNumber();
         b = scanOneNonNegativeWholeNumber();
     }
     printf("%f \n", zad67(a, b));

     printf("Zadanie 7. Program, ktory dostaje jako argumenty liczby calkowite n i m, z ktorych co najmniej jedna jest "
            "rozna od zera i zwraca jako wartosc n^m");
     a = scanOneWholeNumber();
     b = scanOneWholeNumber();
     while (a == 0 || b == 0)
     {
         printf("Co najmniej jedna z liczb musi sie roznic od zera! Sprobuj ponownie \n");
         a = scanOneWholeNumber();
         b = scanOneWholeNumber();
     }

     printf("%f \n", zad67(a, b));

     printf("Zadanie 8. Program, ktory dostaje jako argumenty liczbe dodatnia n i zwraca jako wartosc isqrt(n) \n");
     a = scanOneNonNegativeNumber();
     printf("%d \n", zad8(a));

     double n;
     int m;
     printf("Zadanie 9. Program, ktory dostaje jako argumenty liczbe calkowita m (m > 1) oraz nieujemna liczbe n i zwraca"
            "jako wartość [mth root of n] \n");
     m = scanOneWholeNumber();
     while (m <= 1)
     {
         printf("Liczba m musi byc wieksza niz 1!");
         m = scanOneWholeNumber();
     }
     n = scanOneNonNegativeNumber();
     printf("%d", zad9_2(n, m));

     printf("Zadanie 10. Program, ktory wczytuje ze standardowego wejscia nieujemna liczbe calkowita n i "
            "wypisuje  na standardowym  wyjsciu  sume  liczb  mniejszych  od  n  i  zarazem  wzglednie  pierwszych  z n \n");
     a = scanOneNonNegativeWholeNumber();
     printf("%d", zad10_1(a)+ zad10_2(a));

    printf("Zadanie 11. Program, ktory wczytuje ze standardowego wejscia nieujemna liczbe calkowita n i wypisuje na "
           "standardowym wyjsciu nastepujaca sume [√0] + [√1] + ... + [√n].\n");
    a = scanOneNonNegativeWholeNumber();
    printf("%d", zad11_2(a));
}

int scanOneWholeNumber() {
    int a;
    scanf("%d", &a);
    return a;
}

int scanOneNonNegativeWholeNumber()
{
    int a;
    scanf("%d", &a);
    while (a < 0)
    {
        printf("Liczba musi byc nieujemna \n");
        scanf("%d", &a);
    }
    return a;
}

double scanOneNonNegativeNumber()
{
    double a;
    scanf("%lf", &a);
    while (a < 0)
    {
        printf("Liczba musi byc nieujemna \n");
        scanf("%lf", &a);
    }
    return a;
}

void zad1(int a)
{
    printf("%d \n", (a > 0) ? a : -a);
}

int zad2(int a)
{
    if (a > 1)
    {
        return a * zad2(a - 1);
    }
    else
    {
        return 1;
    }
}

int zad3(int a)
{
    for (int i = 2; i <= sqrt(a); i++)
    {
        if (a % i == 0)
        {
            return a / i;
        }
    }
    return 1;
}

double zad45(int a)
{
    return double(pow(2, a));
}

double zad67(int a, int b)
{
    return double(pow(a, b));
}

int zad8(double a)
{
    int r = a;

    while (r * r > a)
    {
        r = r - 1;
    }
    return r;
}

double zad9_1(double a, double b){
    double t = 1;
    for(int i = 0;i<b;++i)
        t *= a;
    return t;
}
int zad9_2(double n, int m){
    double x;
    double dx;
    double eps = 0.1;
    x = n * 0.5;
    dx = (n / zad9_1(x, m - 1) - x) / m;
    while(dx >= eps || dx <= -eps){
        x = x + dx;
        dx = (n / zad9_1(x, m - 1) - x) / m;
    }
    return int(x);
}

int zad10_1(int a)
{
    int result = 0;
    for (int i = 1; i < a; i++)
    {
        result += i;
    }
    return result;
}

int zad10_2(int a)
{
    int sum = 0;
    for (int i = 1; i <= a; i++) {
        bool isPrime = true;
        if(i == 1) {
            isPrime = false;
        }
        for (int j = 2; j*j <= i; j++) {
            if (i % j == 0) {
                isPrime = false;
                break;
            }
            else isPrime = true;
        }
        if (isPrime) {
            sum = sum + i;
        }
    }
    return sum;
}

int zad11_1(int a)
{
    int r = a;

    while (r * r > a)
    {
        r = r - 1;
    }
    return r;
}

int zad11_2(int a)
{
    int r;
    for (int i = 1; i <= a; i++)
    {
        r += zad11_1(i);
    }
    return r;
}

/*
int zad10_1(int a)
{
    int r;
    for (int i = 1; i < a; i++)
    {
        r += i;
    }
    return r;
}

int zad10_2(int a)
{

} */

/*    int k;
    if (a % 2 == 0)
    {
        printf("%d \n", a / 2);
    }
    else
    {
        k = 3;
        while (k * k <= a)
        {
            if (a % k == 0)
            {
                printf("%d", a / k);
                break;
            }
            k += 2;
        }
    }*/
