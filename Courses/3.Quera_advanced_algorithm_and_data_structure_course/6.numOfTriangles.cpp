//number of different triangles that sum of sides is equal to given n
#include <iostream>
using namespace std;

bool isTriangle(int a, int b, int c){
    return ((a+b > c) && (a+c > b) && (b+c > a));
}

int main(){
    int n; cin >> n;
    
    int cnt=0;
    for(int a=1; a<n/2 +1; a++){
        for(int b=a; b<(n-a)/2 +1; b++){
            int c = n-a-b;
            if(isTriangle(a,b,c))
                cnt++;
        }
    }

    cout << cnt << endl;


    return 0;
}