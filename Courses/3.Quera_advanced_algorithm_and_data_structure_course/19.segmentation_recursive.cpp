#include <iostream>
using namespace std;

long long check_subsets(long long nums[], long long aux[], int n, int ind, long long* min_differ){
    if(n == ind){
        long long in=0, out=0;
        for(int i=0; i<n; i++){
            if(aux[i] == -1)
                out += nums[i];
            else
                in += nums[i];
        }
        long long curr_differ = abs(in-out);
        if(curr_differ < *min_differ)
            *min_differ = curr_differ;

        return 0;
    }
    if(ind != 0){
        aux[ind] = -1;
        check_subsets(nums, aux, n, ind+1, min_differ);
    }

    aux[ind] = 1;
    check_subsets(nums, aux, n, ind+1, min_differ);

    return *min_differ;

}

int main(){
    int n; cin >> n;
    long long nums[n];
    for(int i=0; i<n; i++)
        cin >> nums[i];
    long long aux[n];
    aux[0] =1;
    for(int i=1; i<n; i++)
        aux[i] = -1;
    long long min_differ = 1e10;
    cout << check_subsets(nums, aux, n, 0, &min_differ);

    return 0;
}