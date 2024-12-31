#include <iostream>
using namespace std;

int f(int n){
    if(n == 0)
        return 5;

    if(n % 2 == 0)
        return f(n-1)-21;
    else{
        int tmp = f(n-1);
        return tmp*tmp;
    }
}

int main(){
    int n; cin >> n;
    cout << f(n) << endl;

    return 0;
}
