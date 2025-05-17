#include <iostream>
using namespace std;

int main(){
    int t; cin >> t;

    while(t--){
        string x; cin >> x;
        int k; cin >> k;

        int idx = 0;
        while(k && !x.empty()){
            if(idx == 0 && x[1] == '0'){
                idx++;
                continue;
            }

            if(x[idx] != 0 && x[idx] >= x[idx+1]){
                //better to delete
                x.erase(idx, 1);
                k--;
                if(idx != 0)
                    idx--;
            }else{
                idx++;
            }
        }

        cout << x << endl;
    }
    return 0;
}