//sum of a vector recursively,
#include <iostream>
#include <vector>
using namespace std;

int sum_of_positive_ints(vector<int> nums, int where =0)
{
    if(where == nums.size())
        return 0;
    if(nums[where] > 0)
        return nums[where] + sum_of_positive_ints(nums, ++where);
    else
        return 0 + sum_of_positive_ints(nums, where+1);//where++ is wrong!!!
}

int main()
{
    int n; cout << "please enter a length of your list: "; cin >> n;
    vector<int> nums;
    int tmp;
    for(int i=0;i<n;i++)
    {
        cout << "enter " << i << "th number of your list: ";
        cin >> tmp;
        nums.push_back(tmp);
    }
    cout << "sum of positive integers in your list is: " << sum_of_positive_ints(nums);

    return 0;
}