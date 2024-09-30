#include <iostream>
using namespace std;

void sort(int *p, int n)
{

    for(int i =0; i< n-1; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            int *a = &*(p+j);
            int *b = &*(p+j+1);
            if(*a > *b)
            {
                int tmp = *a;
                *a = *b;
                *b = tmp;
            }
        }
    }
}

int main() {
    int n;
    cin >> n;

    int nums[n];
    for(int i=0; i<n; i++) cin >> nums[i];


    sort(nums, n);

    for(int i = 0; i<n; i++) cout << nums[i] << ' ';

    return 0;
}
