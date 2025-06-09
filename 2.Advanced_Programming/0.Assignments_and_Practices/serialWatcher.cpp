//https://quera.org/problemset/10936
#include <iostream>
using namespace std;



int main()
{
    int n, k; cin >> n >> k;
    int a[n]={};
    for(int i=0; i<n; i++)
        cin>>a[i];

    int maxInRow = 0, inRow=0;
    for(int i=0; i<n; i++){
        while(a[i]+1 == a[i+1]){
            inRow++;
            i++;
        }
        if(inRow+1 > maxInRow)
            maxInRow = inRow+1;
        inRow=0;
    }
    int maxCanBeInRow = maxInRow+k;
    cout << ((maxCanBeInRow>n) ? n:maxCanBeInRow) << endl;

    return 0;
}
