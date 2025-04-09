#include <iostream>
using namespace std;

const int MOD = 1337;

long long digit_pow(int base, int exp){
    if(exp == 0)
        return 1;
        
    long long half_res = digit_pow(base, exp/2);
    if(exp % 2 == 0)
        return (half_res*half_res)%MOD;
    else
        return (half_res*half_res*base)%MOD;
}

long long arr_pow(int base, int* exp_arr, int exp_last_ind){
    if(exp_last_ind < 0)
        return 1;

    // (a^b)%mod = (a%mod ^ b) % mod
    // b = 10q + r
    // a ^ b = a ^ (10q + r) = (a ^ 10q) * (a ^ r) = ((a ^ q) ^ 10) * (a ^ r)
    return (digit_pow(arr_pow(base, exp_arr, exp_last_ind-1), 10) * digit_pow(base, exp_arr[exp_last_ind])) % MOD;
}


int main() {
    long long a; cin >> a;
    int n; cin >> n;
    int b[n];
    for(int i=0; i<n; i++)
        cin >> b[i];
    
    cout << arr_pow(a, b, n-1) << endl;
    return 0;
}