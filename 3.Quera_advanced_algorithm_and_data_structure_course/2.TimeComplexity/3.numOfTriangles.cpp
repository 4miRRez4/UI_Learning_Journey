#include <iostream>
using namespace std;

int main(){
    int n; cin >> n;
    
    long long cnt=0;
    for(int a=1; a<n; a++)
        for(int b=a; b<n; b++)
            for(int c=b; c<n; c++)
                if(a+b+c == n && a+b>c)
                    cnt++;
                    
    cout << cnt << endl;
    return 0;
}