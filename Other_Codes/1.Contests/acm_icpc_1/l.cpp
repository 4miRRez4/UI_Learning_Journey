#include <iostream>
#include <vector>
using namespace std;

void sortVec(vector<int>& nums)
{
    for(int i=0; i<nums.size()-1; i++)
    {
        for(int j=0; j<nums.size()-1; j++)
        {
            if(nums[j] > nums[j+1])
            {
                int tmp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = tmp;
            }
        }
    }
}

int main()
{
    int n; cin >> n;
    vector<int> nums(2*n);
    for(int i=0; i<2*n; i++)
        cin >> nums[i];

    sortVec(nums);

    int sum = 0;
    for(int k=0; k<2*n; k+=2)
    {
        sum += nums[k];
    }
    cout << sum;
    return 0;
}