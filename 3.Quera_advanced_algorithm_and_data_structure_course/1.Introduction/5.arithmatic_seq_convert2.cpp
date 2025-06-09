#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;
int main(){
    int n; cin >> n;
    ll k; cin >> k;
    ll a[n];
    for(int i=0; i<n; i++)
        cin >> a[i];

    ll b[n];
    b[0] = a[0];
    for(int i=1; i<n; i++){
        b[i] = a[i] - (i)*k;
    }

    sort(b, b+n);
    ll median = b[(n-1)/2];

    ll diff =0;
    for(int i=0; i<n; i++)
        diff += abs(b[i]-median);

    cout << diff << endl;

    return 0;
}