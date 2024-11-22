#include <iostream>
using namespace std;

const int MAXN = 1000;
int ARR[MAXN] = {};
int main() {// brute force
    int n, q, x, counter;
    cin >> n >> q;
    for(int i = 0; i < n; i++)
        cin >> ARR[i];
    
    for(int i=0; i<q; i++){
        cin >> x;
        
        counter = 0;
        for(int j=0; j<n; j++)
            if(ARR[j] < x)
                counter++;
                
        cout << counter << endl;
    }
    
    return 0;
}