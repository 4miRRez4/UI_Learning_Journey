#include <iostream>
// #include <cmath>
using namespace std;

double power(int x, int n)
{
    if(n==0) return 1;
    else return (x*power(x, n-1));
}

double fact(int x)
{
    if(x==0) return 1;
    else return x*fact(x-1);
}

double ghadr(double x)
{
    if(x >= 0)
        return x;
    else 
        return -x;
}

double sinCalculator(int x)
{
    double out=0;
    double newJ=0;
    int n = 1;
    int sign = 1;

    do
    {
        newJ = sign * (power(x, n) / fact(n));
        out += newJ;

        n += 2;
        sign *= -1;
    }while(ghadr(newJ) >= 1e-6);

    return out;
}

double cosCaculator(int x)
{
    double out=0;
    double newJ=0;
    int n = 0;
    int sign = 1;

    do
    {
        newJ = sign * (power(x, n) / fact(n));
        out += newJ;

        n += 2;
        sign *= -1;
    }while(ghadr(newJ) > 1e-6);

    return out;
}


int main(){
    int x; cin >> x;

    double fx = sinCalculator(x);
    double gx = cosCaculator(x);

    printf("%.4f %.4f", fx, gx);

    // fx = sin(x);
    // gx = cos(x);
    // printf("%.4f %.4f", fx, gx);

    return 0;
}