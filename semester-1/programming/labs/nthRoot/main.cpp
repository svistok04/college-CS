#include <iostream>

using namespace std;
double exp(double, double);
double nthRoot(double, double);
int main()
{
    double n;
    cout << "Print your number" << endl;
    scanf(" %lf", &n);
    double m = 3;
    cout << (nthRoot(n, m));
}

double exp(double a, double b){
    double t = 1;
    for(int i = 0;i<b;++i)
        t *= a;
    return t;
}
double nthRoot(double n, double m){
    double x;
    double dx;
    double eps = 0.000001;
    x = n * 0.5;
    dx = (n / exp(x, m - 1) - x) / m;
    while(dx >= eps || dx <= -eps){
        x = x + dx;
        dx = (n / exp(x, m - 1) - x) / m;
    }
    return x;
}