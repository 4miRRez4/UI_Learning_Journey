#include <iostream>
using namespace std;

int main(){
    int n;cin >> n;
    int nums[n];
    for (int i = 0; i < n; i++)
        cin >> nums[i];
    
    long long int maxSum = -1000000000;
    for (int l = 0; l < n; l++)
    {
        long long int sum = 0;
        for (int r = l; r < n; r++)
        {
            sum += nums[r];
            if (maxSum < sum)
                maxSum = sum;
        }
    }
    
    cout << maxSum << endl;
}