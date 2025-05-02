#include <iostream>
using namespace std;



int find_peak_idx(int arr[], int n){
    int left = 0, right = n;
    while(left < right){
        int mid = (left + right) / 2;
        if(arr[mid] > arr[mid-1] && arr[mid] > arr[mid+1])
            return mid;
        else if(arr[mid] > arr[mid-1])
            left = mid+1;
        else
            right = mid;
    }

    return -1;
}

int main(){
    int n; cin >> n;
    int arr[n];
    for(int i=0; i<n; i++)
        cin >> arr[i];

    cout << find_peak_idx(arr, n) << endl;

    return 0;
}