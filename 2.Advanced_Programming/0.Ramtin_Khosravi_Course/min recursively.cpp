//finding minimum of an array using recursion(ap section 4)
#include <iostream>
#include <vector>
using namespace std;

int minRec(vector<int> nums, int where=0, int min=1000)
{
    if(where == nums.size())
        return min;
    else if(nums[where] < min)
        min = nums[where];
    return minRec(nums, where+1, min);
}

int main()
{
    int num;
    vector<int> nums;
    while(cin >> num) 
        nums.push_back(num);
    
    cout << "min is: " << minRec(nums);

    return 0;
}