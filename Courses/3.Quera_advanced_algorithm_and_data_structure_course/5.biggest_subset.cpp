//finding subsequence of a given array with max value;
#include <iostream>
using namespace std;

// int main(){
//     int n;
//     cin >> n;
//     long long nums[n];
//     for(int i=0; i<n; i++)
//         cin >> nums[i];

//     long long sum=0, maxSum=-1000000000000;
//     for(int len=1; len<=n; len++)
//         for(int start=0; start<n-len+1; start++){
//             for(int i=0; i<len; i++){
//                 sum += nums[(start+i)];
//             }
//             if(sum > maxSum)
//                 maxSum = sum;
//             sum=0;
//         }

//     cout << maxSum;

//     return 0;
// }

// int main(){
//     int n;cin >> n;
//     int nums[n];
//     for (int i = 0; i < n; i++)
//         cin >> nums[i];
    
//     long long int maxSum = -1000000000;
//     for (int l = 0; l < n; l++)
//     {
//         long long int sum = 0;
//         for (int r = l; r < n; r++)
//         {
//             sum += nums[r];
//             if (maxSum < sum)
//                 maxSum = sum;
//         }
//     }
    
//     cout << maxSum << endl;
// }

// int main(){
//     int n;
//     cin >> n;
//     long long calc[n][n] = {};
//     long long maxSum=-1000000000;    
//     for(int i=0; i<n; i++){
//         cin >> calc[0][i];
//         if(calc[0][i] > maxSum)
//             maxSum = calc[0][i];
//     }


//     for(int r=1; r<n; r++)
//         for(int c=0; c<n-r ; c++){
//             calc[r][c] = calc[r-1][c] + calc[0][(c+r)];
//             if(calc[r][c] > maxSum)
//                 maxSum = calc[r][c];
//         }

//     cout << maxSum << endl;
//     // for(int i=0; i<n; i++){
//     //     for(int j=0; j<n; j++)
//     //         cout << calc[i][j] << " ";
//     //     cout << endl;
//     // }
//     return 0;
// }


int main(){
    int n;cin >> n;
    long long nums[n];
    for (int i = 0; i < n; i++)
        cin >> nums[i];

    long long current_sum = nums[0];
    long long max_sum = nums[0];
    for(int i=1; i<n; i++){
        current_sum = max(nums[i], nums[i] + current_sum);
        max_sum = max(current_sum, max_sum);
    }

    cout << max_sum << endl;
}