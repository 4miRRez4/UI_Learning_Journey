#include <iostream>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    
    int sum=0;
    //iterating on numbers between n and m;
    for (int i = n; i<=m; i++)
    {
        
        int c = 0;
        //iterating on numbers less than i;
        for (int j = 1; j<=i; j++)
        {
            
            if (i % j == 0)
            {
                c++;
            }
        }
        //adding up prime numbers;
        if ((c <= 2) && (i!=1))
        {
            sum += i;
        }
    }
    cout << sum;
}