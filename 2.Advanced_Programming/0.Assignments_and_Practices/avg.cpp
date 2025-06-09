#include <iostream>
using namespace std;

int main()
{
    int n, i=0, num; 
    float sum=0;
    cout << "enter number of numbers you want to enter: "; cin >> n;

    while(i<n) //while(cin>>num)
    {
        cout << "please enter " << i+1 << "th number: ";
        cin >> num;
        sum+=num;
        i++;
    }

    float avg = sum/n;
    cout << "sum is: " << sum << " and average is: " << avg;

    return 0;
}