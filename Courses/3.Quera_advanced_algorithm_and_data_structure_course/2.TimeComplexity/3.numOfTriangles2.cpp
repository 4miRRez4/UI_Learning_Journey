#include <iostream>
using namespace std;


int main(){
    int n; cin >> n;
    
    int cnt=0;
    for(int a=1; a<n; a++){
        for(int b=a; b<(n-a); b++){
            int c = n-a-b;
            if(a+b > c && c>=b)
                cnt++;
        }
    }

    cout << cnt << endl;


    return 0;
}