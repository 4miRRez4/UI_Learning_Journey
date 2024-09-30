#include <iostream>
using namespace std;

int main()
{
    float n;
    cin >> n;

    float num;
    float sum;

    cin >> num;
    sum += num;
    float max = num;
    float min = num;
    for (int i = 0; i<(n-1); i++)
    {
        cin >> num;
        sum += num;
        if(num > max)
        {
            max = num;
        }else if (num < min)
        {
            min = num;
        }
    }

    cout << "Max: " << max << endl;
    cout << "Min: " << min << endl;
    float avg = sum/n;
    cout << "Avg: " << avg << endl;
}