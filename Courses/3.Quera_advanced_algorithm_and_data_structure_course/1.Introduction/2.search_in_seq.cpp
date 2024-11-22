#include <iostream>
#include <algorithm>
using namespace std;


int main(){//binary search
    int n, q, x, counter;
    cin >> n >> q;

    int arr[n];
    for(int i=0; i<n; i++)
        cin >> arr[i];
    
    std::sort(arr, arr + n);
    for(int i=0; i < q; i++){
        cin >> x;

        //searching for first element which is bigger than x;
        int first=0, last=n-1, mid;
        while(first <= last){
            mid = (first + last) /2;
            if(arr[mid] < x){
                first = mid + 1;
                mid = first;
            }
            else if(arr[mid] >= x){
                if(arr[mid-1] >= x)
                    last = mid - 1;
                else{
                    break;
                }
            }
        }
        cout << mid << endl;   
    }
}