#include <iostream>
using namespace std;

int partition(int arr[], int l, int r){
    int pivot_val = arr[l];

    int ls = l;
    for(int i=l+1; i<=r; i++){
        if(arr[i] <= pivot_val){
            swap(arr[i], arr[++ls]);
        }
    }
    swap(arr[ls], arr[l]);
    
    return ls;
}

void quick_sort(int arr[], int l, int r){
    if(r <= l)
        return;
    
    int p = partition(arr, l, r);
    cout << arr[p] << " ";

    quick_sort(arr, l, p-1);
    quick_sort(arr, p+1, r);
}

int main(){
    int n; cin >> n;
    int arr[n];
    for(int i=0; i<n; i++)
        cin >> arr[i];

    quick_sort(arr, 0, n-1);

    return 0;
}