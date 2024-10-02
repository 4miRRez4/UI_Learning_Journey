//finding gcd recursively
#include <iostream>
using namespace std;

long long gcd(long long x, long long y){
    if(y == 0)
        return x;
    else    
        return gcd(y, x%y);
}

int main(){
    long long a, b; cin >> a >> b;
    cout << gcd(a, b) << endl;

    return 0;
}