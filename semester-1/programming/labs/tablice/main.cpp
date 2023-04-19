// Tablice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <valarray>

int scanOneNonNegativeWholeNumber();
int* randomArray1(int*, int);
int* randomArray2(int*, int);
const int* randomArray3(const int*, int);
void printAnArrayOut(int*, int);
void Zad1_a(int*, int);
void Zad1_b(int*, int);
void Zad1_c(int*, int);
void Zad2_a(int*, int);
void Zad2_b(int*, int);
void Zad2_c(int*, int);
void Zad3(const int*, int);
void Zad4_a(int*, int*, int);
void Zad4_b(int*, int*, int);
void Zad5_a(int*, int*, int*, int);
void Zad5_b(int*, int*, int*, int);
void Zad5_c(int*, int*, int*, int);


int main()
{
    int n;
    int* tab;
    srand(time(NULL));
    // Zad 1.
    printf("Program, ktory otrzymuje dwa argumenty: nieujemna liczbe calkowita n oraz n-elementowa tablice tab elementow typu int");
    n = scanOneNonNegativeWholeNumber();
    tab = (int*)malloc(sizeof(int)*n);
    free(tab);

    // Zad 2.
    printf("Zadanie 2. Program, ktory otrzymuje dwa argumenty : dodatnia liczbe calkowita n oraz n - elementowa tablice tab o elementach typu int\n");
    n = scanOneNonNegativeWholeNumber();
    tab = (int*)malloc(sizeof(int)*n);
    tab = randomArray1(tab, n);
    printAnArrayOut(tab, n);
    Zad2_a(tab, n);
    Zad2_b(tab, n);
    Zad2_c(tab, n);
    free(tab);

    // Zad 3.
    printf("Zadanie 3. Program, ktory otrzymuje dwa argumenty: dodatnia liczbe calkowita n oraz "
        "n-elementowa tablicê tab o elementach typu const int i zwraca jako wartosc srednia arytmetyczna elementów tablicy tab");
    n = scanOneNonNegativeWholeNumber();
    const int* tab3 = new const int[n];
    tab3 = randomArray3(tab3, n);

    // Zad 4.
    printf("Zadanie 4. Program, ktory otrzymuje trzy argumenty: dodatnia liczbe calkowita n oraz dwie n-elementowe tablice "
        "tab1, tab2 o elementach typu int\n");
    n = scanOneNonNegativeWholeNumber();
    int* tab1 = (int*)malloc(sizeof(int)*n);
    int* tab2 = (int*)malloc(sizeof(int) * n);
    tab1 = randomArray1(tab1, n);
    tab2 = randomArray1(tab2, n);
    printf("Tablica tab1: "); printAnArrayOut(tab1, n);
    printf("Tablica tab2: "); printAnArrayOut(tab2, n);
    free(tab1);
    free(tab2);

    // Zad 5.
    printf("Zadanit 5. Program,  ktory otrzymuje cztery argumenty: dodatnia liczbe calkowita n oraz trzy n-elementowe "
        "tablice tab1, tab2 i tab3 o elementach typu int\n");
    n = scanOneNonNegativeWholeNumber();
    int* tab1 = (int*)malloc(sizeof(int) * n);
    int* tab2 = (int*)malloc(sizeof(int) * n);
    int* tab3 = (int*)malloc(sizeof(int) * n);
    tab1 = randomArray1(tab1, n);
    tab2 = randomArray1(tab2, n);
    tab3 = randomArray1(tab3, n);
    printf("Tablica tab1: "); printAnArrayOut(tab1, n);
    printf("Tablica tab2: "); printAnArrayOut(tab2, n);
    printf("Tablica tab3: "); printAnArrayOut(tab3, n);
    Zad5_a(tab1, tab2, tab3, n);
    Zad5_b(tab1, tab2, tab3, n);
    Zad5_c(tab1, tab2, tab3, n);

    // Zad 6.
    printf("\n Zadanie 6. Program, ktory otrzymuje cztery argumenty: dodatni¹ liczbê ca³kowit¹ n, n-elementowe tablice tab1 "
           "i tab2 oraz 2 · n - elementow¹ tablicê tab3 o elementach typu double");
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

int* randomArray1(int* tab, int n)
{
    for (int i = 0; i < n; i++)
    {
        tab[i] = (rand() % 20);
    }
    return tab;
}

int* randomArray2(int* tab, int n)
{
    for (int i = 0; i < n; i++)
    {
        tab[i] = (rand() % 20) - 10;
    }
    return tab;
}

/*const int* randomArray3(const int* tab, int n)
{
    for (const int i = 0; i < n; i++)
    {
        const tab[i] = (rand() % 20);
    }
    return tab;
}*/

void printAnArrayOut(int* tab, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d, ", tab[i]);
    }
    printf("\n");
}

void Zad1_a(int* tab, int n)
{
    for (int i = 0; i < n; i++)
    {
        tab[i] = 0;
    }
}

void Zad1_b(int* tab, int n)
{
    for (int i = 0; i < n; i++)
    {
        tab[i] = i;
    }
}

void Zad1_c(int* tab, int n)
{
    for (int i = 0; i < n; i++)
    {
        tab[i] = i * 2;
    }
}

void Zad2_a(int* tab, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += tab[i];
    }
    printf("Srednia arytmetyczna wynosi: %d \n", (sum / n));
}

void Zad2_b(int* tab, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += tab[i];
    }
    printf("Suma elementow tablicy wynosi: %d \n", sum);
}

void Zad2_c(int* tab, int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += pow(tab[i], 2);
    }
    printf("Suma kwadratow elementow tablicy wynosi: %.0lf \n", sum);
}

void Zad4_a(int* tab1, int* tab2, int n)
{
    printf("Nowy tab1: ");
    for (int i = 0; i < n; i++)
    {
        tab2[i] = tab1[i];
        printf("%d, ", tab2[i]);
    }
}

void Zad4_b(int* tab1, int* tab2, int n)
{
    printf("Nowy tab1: ");
    for (int i = 0; i < n; i++)
    {
        tab2[n - i - 1] = tab1[i];
        printf("%d, ", tab2[n - i - 1]);
    }
}

void Zad5_a(int* tab1, int* tab2, int* tab3, int n)
{
    printf("Podpunkt A, nowy tab3: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d, ", tab2[i] + tab1[i]);
    }
    printf("\n");
}

void Zad5_b(int* tab1, int* tab2, int* tab3, int n)
{
    printf("Podpunkt B, nowy tab3: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d, ", (tab1[i] > tab2[i]) ? tab1[i] : tab2[i]);
    }
    printf("\n");
}

void Zad5_c(int* tab1, int* tab2, int* tab3, int n)
{
    int* temp1 = tab2;
    int* temp2 = tab3;
    tab2 = tab1;
    tab3 = temp1;
    tab1 = temp2;
    printf("Podpunkt C, nowy tab1: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d, ", tab1[i]);
    }
    printf("\nnowy tab12: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d, ", tab2[i]);
    }
    printf("\nnowy tab3: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d, ", tab3[i]);
    }
}
