#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    long long calc[n][n] = {};
    long long maxSum=-1000000000;    
    for(int i=0; i<n; i++){
        cin >> calc[0][i];
        if(calc[0][i] > maxSum)
            maxSum = calc[0][i];
    }


    for(int r=1; r<n; r++)
        for(int c=0; c<n-r ; c++){
            calc[r][c] = calc[r-1][c] + calc[0][(c+r)];
            if(calc[r][c] > maxSum)
                maxSum = calc[r][c];
        }

    cout << maxSum << endl;
    // for(int i=0; i<n; i++){
    //     for(int j=0; j<n; j++)
    //         cout << calc[i][j] << " ";
    //     cout << endl;
    // }
    return 0;
}