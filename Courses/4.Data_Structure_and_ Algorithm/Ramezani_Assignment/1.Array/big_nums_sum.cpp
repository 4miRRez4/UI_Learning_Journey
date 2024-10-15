#include <iostream>
using namespace std;

int main(){
    string a, b; cin >> a >> b;

    int a_idx = a.length()-1;
    int b_idx = b.length()-1;

    string tmp_zeros = "";
    int idx;
    for(int i=0; i<abs(a_idx-b_idx); i++)
        tmp_zeros += "0";
    if(a_idx > b_idx){
        idx = a_idx;
        b = tmp_zeros + b;
    }else{
        idx = b_idx;
        a = tmp_zeros + a;
    }

    string reverse_sum = "";
    int carry = 0;
    while(idx >= 0){
        int tmp_sum = a[idx]-'0' + b[idx]-'0' + carry;

        char digit = (tmp_sum)%10 + '0';
        reverse_sum += digit;

        carry = (tmp_sum >= 10) ? 1:0;
        idx--;
    }
    if(carry)
        reverse_sum += "1";
    
    for(int i=reverse_sum.length(); i>=0; i--)
        cout << reverse_sum[i];
    

    return 0;
}