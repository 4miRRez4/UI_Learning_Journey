#include <iostream>
using namespace std;

// //counting sort
// int main(){
//     int n; cin >> n;
//     int MAXNUM = 1000;
//     long long count[1000] = {};

//     int tmp=0;
//     for(int i=0; i<n; i++){
//         cin >> tmp;
//         count[tmp]++;
//     }

//     for(int i=0; i<MAXNUM; i++)
//         for(int j=0; j<count[i]; j++)
//             cout << i << " ";


//     return 0;
// }


// //bubble sort
// int main() {
//     int n; cin >> n;
//     long long nums[n] = {};
//     for(int i=0; i<n; i++)
//         cin >> nums[i];
        
//     for(int i=0; i<n; i++){
//         for(int j=0; j<n-i; j++){
//             if(nums[j] > nums[j+1]){
//                 long long tmp = nums[j];
//                 nums[j] = nums[j+1];
//                 nums[j+1] = tmp;
//             }
//         }
//     }
    
//     for(int i=0; i<n; i++)
//         cout << nums[i] << " ";
//     return 0;
// }


// //selection sort
// int main() {
//     int n; cin >> n;
//     long long nums[n]={};
//     for(int i=0; i<n; i++)
//         cin >> nums[i];
        
//     for(int i=0; i<n-1; i++){
//         int min_ind = i;
//         for(int j=i+1; j<n; j++){
//             if(nums[j] < nums[min_ind]){
//                 min_ind = j;
//             }
//         }
//         int tmp = nums[i];
//             nums[i] = nums[min_ind];
//             nums[min_ind] = tmp;
//     }
    
//     for(int i=0; i<n; i++)
//         cout << nums[i] << " ";
//     return 0;
// }


// //insertion sort
// int main(){
//     int n; cin >> n;
//     long long nums[n]={};
//     for(int i=0; i<n; i++)
//         cin >> nums[i];

//     for(int i=1; i<n; i++){
//         long long tmp = nums[i];
//         int j = i-1;
//         while(nums[j] > tmp & j>=0){
//             nums[j+1] = nums[j];
//             j--;
//         }
//         nums[j+1] = tmp;
//     }

//     for(int i=0; i<n; i++)
//         cout << nums[i] << " ";
//     return 0;
// }