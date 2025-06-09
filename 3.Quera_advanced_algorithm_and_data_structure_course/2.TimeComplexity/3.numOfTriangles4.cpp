#include <iostream>
using namespace std;

int main(){
    int n; cin >> n;

    long long cnt =0;
    for(int a=1; a<=n/3; a++)
        cnt += (n- 3*a)/2 - max(0, n/2 - 2*a +1) +1;
    cout << cnt << endl;

    return 0;
}