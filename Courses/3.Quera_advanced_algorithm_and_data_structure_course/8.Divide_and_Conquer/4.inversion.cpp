#include <iostream>
using namespace std;

int inversion_in_merge(int arr[], int n, int l, int mid, int r){
    //[l, mid), [mid, r)
    int cnt=0;
    int k=mid;
    for(int i=l; i<mid; i++){
        int elem_of_first_arr = arr[i];
        while(k < r && elem_of_first_arr > arr[k]){
            k++;
        }
        cnt += (k-mid);
    }
    return cnt;
}

void merge(int arr[], int n, int l, int mid, int r){
    int n1 = mid-l, n2 = r-mid;
    int merged[n1+n2]; 
    int a = l, b = mid, c = 0;
    while(a < mid && b < r){
        if(arr[a] < arr[b]){
            merged[c++] = arr[a++];
        }else{
            merged[c++] = arr[b++];
        }
    }
    
    while(a < mid){
        merged[c++] = arr[a++];
    }
    while(b < r){
        merged[c++] = arr[b++];
    }

    for(int i=0; i<n1+n2; i++){
        arr[l+i] = merged[i];
    }
}

int count_inversion(int arr[], int n, int l, int r){
    //[l,r)
    if(r == l+1){
        return 0;
    }

    int cnt = 0;

    int mid = l + (r-l)/2;
    cnt += count_inversion(arr, n, l, mid);
    cnt += count_inversion(arr, n, mid, r);

    cnt += inversion_in_merge(arr, n, l, mid, r);

    merge(arr, n, l, mid, r);
    return cnt;
}

int main(){
    int n; cin >> n;
    int arr[n];
    for(int i=0; i<n; i++)
        cin >> arr[i];

    cout << count_inversion(arr, n, 0, n);

    return 0;
}