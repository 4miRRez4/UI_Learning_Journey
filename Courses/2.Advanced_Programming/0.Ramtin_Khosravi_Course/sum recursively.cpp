//در این مثال، مجموع اعداد موجود در یک بردار را به صورت بازگشتی محاسبه می‌کنیم. (ap section4)
#include <iostream>
#include <vector>
using namespace std;

int sumRec(vector<int> nums, int where)
{
    if(where == nums.size())
        return 0;
    else 
        return nums[where] + sumRec(nums, where+1);
}

int main()
{
    vector<int> nums;
    int n;
    while(cin >> n)
        nums.push_back(n);

    cout << "Sum: " << sumRec(nums, 0);
    return 0;
}
