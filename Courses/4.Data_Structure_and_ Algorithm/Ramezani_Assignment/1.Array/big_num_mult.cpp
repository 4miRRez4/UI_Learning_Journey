#include<iostream>
using namespace std;


int main(){
    string a, b; cin >> a >> b;
    int len_a = a.length();
    int len_b = b.length();

    int len_c = len_a + len_b;
    int c[len_c] = {};
    int carry = 0;
    for(int b_idx = len_b-1; b_idx >= 0; b_idx--){
        int c_idx = len_c-(b.length()-b_idx);
        int digit2 = b[b_idx]-'0';
        for(int a_idx = len_a-1; a_idx >= 0 ; a_idx--){
            int digit1 = a[a_idx]-'0';

            int newVal =  c[c_idx] + digit1*digit2 + carry;
            c[c_idx] = (newVal)%10;
            carry = newVal/10;
            c_idx--;
        }

        while(carry){
            c[c_idx] += carry%10;
            carry /= 10;
            c_idx--;
        }
    }

    int c_idx = 0;
    while(c[c_idx] == 0)
        c_idx++;

    while(c_idx < len_c){
        cout << c[c_idx];
        c_idx++;
    }


    return 0;
}