#include <iostream>
using namespace std;

int ALL_NUMS[1000] = {};
int main(){ 
    int n, q, x, num, counter;
    cin >> n >> q;

    for(int i=0; i<n; i++){
        cin >> num;
        ALL_NUMS[num-1]++;
    }

    for(int i=0; i<q; i++){
        cin >> x;
        counter = 0;
        for(int j=0; j<x-1; j++){
            counter += ALL_NUMS[j];
        }
        cout << counter << endl;
    }
    return 0;
}