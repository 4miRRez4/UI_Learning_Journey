#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    long long nums[n];
    for(int i=0; i<n; i++)
        cin >> nums[i];

    long long sum=0, maxSum=-1000000000000;
    for(int len=1; len<=n; len++)
        for(int start=0; start<n-len+1; start++){
            for(int i=0; i<len; i++){
                sum += nums[(start+i)];
            }
            if(sum > maxSum)
                maxSum = sum;
            sum=0;
        }

    cout << maxSum;

    return 0;
}