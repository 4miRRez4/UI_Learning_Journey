#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

int main(){
    int t; cin >> t;

    while(t--){
        string x; cin >> x;
        int k; cin >> k;

        stack<char> digits;
        digits.push(x[0]);

        for(int i=1; i<x.length(); i++){
            while(!digits.empty() && digits.top() > x[i] && k){
                if(x[i] == '0' && digits.size() <= 1){
                    break;
                }
                digits.pop();
                k--;
                
            }            
            digits.push(x[i]);
        }

        while(k--)
            digits.pop();
        
        string res = "";
        while(!digits.empty()){
            res += digits.top();
            digits.pop();
        }
        reverse(res.begin(), res.end());
        cout << res << endl;
    }

    return 0;
}