//checking number of numbers that are bigger than x
#include <iostream>
#include <algorithm>
using namespace std;

// int MAXN = 1000;
// int ARR[MAXN] = 0;
// int main() {// brute force
//     int n, q, x, counter;
//     cin >> n >> q;
//     for(int i = 0; i < n; i++)
//         cin >> ARR[i];
    
//     for(int i=0; i<q; i++){
//         cin >> x;
        
//         counter = 0;
//         for(int j=0; j<n; j++)
//             if(ARR[j] < x)
//                 counter++;
                
//         cout << counter << endl;
//     }
    
//     return 0;
// }


// int main(){//binary search
//     int n, q, x, counter;
//     cin >> n >> q;

//     int arr[n];
//     for(int i=0; i<n; i++)
//         cin >> arr[i];
    
//     std::sort(arr, arr + n);
//     for(int i=0; i < q; i++){
//         cin >> x;

//         //searching for first element which is bigger than x;
//         int first=0, last=n-1, mid;
//         while(first <= last){
//             mid = (first + last) /2;
//             if(arr[mid] < x){
//                 first = mid + 1;
//                 mid = first;
//             }
//             else if(arr[mid] >= x){
//                 if(arr[mid-1] >= x)
//                     last = mid - 1;
//                 else{
//                     break;
//                 }
//             }
//         }
//         cout << mid << endl;   
//     }
// }

// int ALL_NUMS[1000] = {};
// int main(){ 
//     int n, q, x, num, counter;
//     cin >> n >> q;

//     for(int i=0; i<n; i++){
//         cin >> num;
//         ALL_NUMS[num-1]++;
//     }

//     for(int i=0; i<q; i++){
//         cin >> x;
//         counter = 0;
//         for(int j=0; j<x-1; j++){
//             counter += ALL_NUMS[j];
//         }
//         cout << counter << endl;
//     }
//     return 0;
// }


#include <iostream>
using namespace std;

const int MAXN = 1000 * 100 + 5;
const int MAXD = 1000 * 1000 + 5;

int n, q, x;
int question[MAXN], memo[MAXD]={};

int main()//memoization
{
    cin >> n >> q;
    for (int i = 0; i < n; i++){
        cin >> x;
        memo[x-1]++;
    }

    for(int i=1; i<MAXD; i++){
        memo[i] += memo[i-1];
    }
    for (int i = 0; i < q; i++){
        cin >> x;
        cout << memo[x-2] << endl;
    }


        
    return 0;
}