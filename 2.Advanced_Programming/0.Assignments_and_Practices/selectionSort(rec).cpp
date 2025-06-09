//selection sort(recursively)
#include <iostream>
#include <vector>
using namespace std;

int indexOfMin(vector<int>& nums, int until)
{
    if(until == 0)
        return until;
    int minIndRest = indexOfMin(nums, until-1);
    if(nums[minIndRest] > nums[until])
        return until;
    else
        return minIndRest;
}

void swap(int& i,int& j)
{
    int tmp = i;
    i = j;
    j = tmp;
}

void selectionSort(vector<int>& nums, int until)
{
    if(until == 0)
        return;
    int minI = indexOfMin(nums, until);
    swap(nums[minI], nums[until]);
    selectionSort(nums, until-1);
}   

void printList(vector<int> nums,int i=0)
{
    if(i == nums.size())
        return;
    cout << nums[i] << endl;
    printList(nums, i+1);
}

int main()
{
    vector<int> nums; int n;
    while(cin>>n)
        nums.push_back(n);

    selectionSort(nums, nums.size()-1);

    printList(nums);

    return 0;
}