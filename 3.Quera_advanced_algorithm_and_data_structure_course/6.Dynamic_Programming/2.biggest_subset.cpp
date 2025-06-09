#include <iostream>
using namespace std;

long long maxSum[100000]={};

int main() {
    int n; cin >> n;
    long long newVal;
    for(int i=0; i<n; i++){
        cin >> newVal;
        maxSum[i] = max(newVal, newVal + maxSum[i-1]);
    }

    long long answer = maxSum[0];
    for(int i=0; i<n; i++){
        answer = max(answer, maxSum[i]);
    }
    
    cout << answer << endl;
    return 0;
}