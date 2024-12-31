#include <iostream>
using namespace std;


int main(){
    int n; cin >> n;
    
    int cnt=0;
    for(int a=1; a<n/3 +1; a++){
        for(int b=a; b<(n-a)/2 +1; b++){
            int c = n-a-b;
            if(a+b > c)
                cnt++;
        }
    }

    cout << cnt << endl;


    return 0;
}