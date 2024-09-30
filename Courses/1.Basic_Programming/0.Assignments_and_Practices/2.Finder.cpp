#include <iostream>

using namespace std;

int main()
{
    long long num;
    cin >> num;

    int n;
    cin >> n;
    
    //calculating lenght of n.
    int tmp = n;
    int len = 0;
    while (tmp > 0)
    {
        len++;        
        tmp = (tmp-tmp%10)/10;

    }
    
    //iterating on num with len of n and comparing it with n.
    int p = 1;
    for(int i = 0; i<len; i++)
    {
        p *= 10;
    }

    while (num > 0) 
    {
        int selected = num % p;
        if (selected == n )
        {
            cout << "YEY";
            exit(0);
        }
        num = (num-(num%10))/10;
    }
    cout << "NEY";
}

