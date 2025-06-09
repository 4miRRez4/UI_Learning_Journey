#include <iostream>
using namespace std;

void merge_2_arr(int* a, int a_size, int* b,int b_size, int* c){
    int i=0, j=0, k=0;
    while(i < a_size && j < b_size){
        if(a[i] < b[j])
            c[k++] = a[i++];
        else
            c[k++] = b[j++];
    }

    while(i<a_size)
        c[k++] = a[i++];
    while(j<b_size)
        c[k++] = b[j++];
}

void merge_k_arr(int** arrs, int* res, int l, int r, int n){
    if(r == l){
        for(int i=0; i<n; i++)
            res[i] = arrs[l][i];
        return;
    }

    int mid = (r+l)/2;
    int left_size = (mid-l+1) * n;
    int right_size = (r-mid) * n;

    int* left_res = new int[left_size];
    int* right_res = new int[right_size];

    merge_k_arr(arrs, left_res, l, mid, n);
    merge_k_arr(arrs, right_res, mid+1, r, n);

    merge_2_arr(left_res, left_size, right_res, right_size, res);

    delete[] left_res;
    delete[] right_res;
}

int main(){
    int n,k; cin >> n >> k;
    int** arrs = new int*[k];
    for(int i=0; i < k; i++)
        arrs[i] = new int[n];

    for(int i=0; i<k; i++)
        for(int j=0; j<n; j++)
            cin >> arrs[i][j];

    int* res = new int[n*k];
    merge_k_arr(arrs, res, 0, k-1, n);

    for(int i=0; i<n*k; i++)
        cout << res[i] << " ";

    for(int i=0; i<k; i++)
        delete[] arrs[i];
    delete[] arrs;
    delete[] res;

    return 0;
}