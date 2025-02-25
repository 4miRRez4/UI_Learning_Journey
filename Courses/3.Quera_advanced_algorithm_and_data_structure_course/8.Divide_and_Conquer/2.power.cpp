#include <iostream>
#include <iomanip>
using namespace std;

double power(double base, long long exp){
    if(exp == 0)
        return 0;
        
    if(exp == 1)
        return base;
        
    double half_res = power(base, exp/2);
    if(exp % 2 == 0)
        return half_res*half_res;
    else
        return half_res*half_res*base;
}

int main() {
    double base;
    long long exp;
    cin >> base >> exp;
    cout << fixed << setprecision(3);
    cout << power(base, exp) << endl;
    return 0;
}