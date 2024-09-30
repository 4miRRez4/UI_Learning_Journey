//BinarySearch recursively
#include <iostream>
#include <vector>
using namespace std;

int binarySearch(vector<int>& nums, int val, int first, int last)
{
    if (nums.size() == 0)
        return -1;
    if(first > last)
        return -1;
    int mid = (first+last)/2;
    if(nums[mid] == val)
        return mid;
    else if(nums[mid] < val)
        first = mid+1;
    else 
        last = mid-1;
    return binarySearch(nums, val, first, last);
}

int main()
{
    vector<int> nums; int n, tmp, val;

    cout << "enter number of numbers: "; cin >> n;
    for(int i=0; i<n; i++) 
    {
        cin >> tmp;
        nums.push_back(tmp);
    }
    cout << "enter your wanter number: "; cin >> val;
    cout << "index of wanted number is ";
    int idx = binarySearch(nums, val, 0, nums.size()-1);
    if (idx == -1)
        cout << "value not found" << endl;
    else
        cout << "value is found at index " << idx << endl;
    return 0;
}