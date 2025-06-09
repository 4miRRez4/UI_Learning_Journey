#include <iostream>
using namespace std;

void swap3(int* a, int* b)
{

    if (a == b)
        return;
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

int main() {
    int n;
    cin >> n;

    int nums[n];
    for(int i=0; i<n; i++) cin >> nums[i];

    for(int j=0; j<(n/2); j++)
    {
        //swaping element j with l-j;
        //using + -:
//        nums[j] = nums[j] + nums[n-j-1];
//        nums[n-j-1] = nums[j] - nums[n-j-1];
//        nums[j] = nums[j] - nums[n-j-1];


        //using xor
//        nums[j] = nums[j] ^ nums[n-j-1];
//        nums[n-j-1] = nums[j] ^ nums[n-j-1];
//        nums[j] = nums[j] ^ nums[n-j-1];

        //using a function and pointers;
        swap3(&nums[j], &nums[n-j-1]);
    }

    for(int i=0; i<n; i++)
    {
        cout << nums[i] << ' ';
    }

    return 0;
}
