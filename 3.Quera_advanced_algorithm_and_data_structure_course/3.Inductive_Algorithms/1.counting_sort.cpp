#include <iostream>
using namespace std;
int main(){
    int n; cin >> n;
    int MAXNUM = 1000;
    long long count[1000] = {};

    int tmp=0;
    for(int i=0; i<n; i++){
        cin >> tmp;
        count[tmp]++;
    }

    for(int i=0; i<MAXNUM; i++)
        for(int j=0; j<count[i]; j++)
            cout << i << " ";


    return 0;
}

