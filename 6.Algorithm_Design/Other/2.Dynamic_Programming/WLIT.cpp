#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 100;
ll a[MAXN], before_i[MAXN], after_i[MAXN], until_i[MAXN];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n; cin >> n;
    for(int i=0; i<n-1; i++)
        cin >> a[i];

    before_i[0] = 0;
    for(int i=1; i<n; i++){
        before_i[i] = (a[i-1] == 1) ? 0 : before_i[i-1] + a[i-1] - (a[i-1] & 1ll);
    }

    after_i[n-1] = 0;
    for(int i=n-2; i >= 0; i--){
        after_i[i] = (a[i] == 1) ? 0 : after_i[i+1] + a[i] - (a[i] & 1ll);
    }

    long long ans = 0;
    int ans_i = 0;
    until_i[0] = 0;
    for(int i=1; i<n; i++){
        until_i[i] = max(before_i[i], until_i[i-1] + (a[i-1] & 1ll) ? a[i-1] : a[i-1]-1);
        ans = max(ans, until_i[i]);

        if(ans == until_i[i])
            ans_i = i;
    }

    cout << ans+1 << ans_i << endl;

    return 0;
}