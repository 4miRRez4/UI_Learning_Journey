//value of x in given polynomial
#include <iostream>
using namespace std;

int main(){
    int n; long long x; cin >> n >> x;
    long long coefficient[n+1];
    for(int i=0; i<n+1; i++)
        cin >> coefficient[i];
    
    long long output = coefficient[0];
    for(int i=1; i<n+1; i++)
        output = (output * x + coefficient[i]) % 1000000007;
    
    while(output < 0)
        output += 1000000007;
    cout << output << endl;

    return 0;
}