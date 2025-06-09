#include <iostream>
using namespace std;

int main()
{
    int t; cin >> t;
    // for(int i=0; i<t; i++)
    // {
    //     int a,b,d;
    //     cin >> a >> b;
    //     if(((a+b) % 3 == 0))
    //     {       
    //         while(a!=0 && b!=0)
    //         {
    //             if(a+b < 3)
    //                 break;
    //             if(a>b)
    //             {
    //                 d = a-b;
    //                 a-=2*d;
    //                 b-=1*d;
    //             }else if(a<b)
    //             {
    //                 d = a-b;
    //                 b-=2*d;
    //                 a-=1*d;
    //             }else //a==b
    //             {
    //                 a-=2*d;
    //                 b-=1*d;
    //             }
    //         }
    //     }
    //     if(a==0 && b==0)
    //         cout << "YES" << endl;
    //     else
    //         cout << "NO" << endl;
    // }
    
    //a = 2x + y -> b= x + 2y => 2a - b = 3x
    for(int i=0; i<t; i++)
    {
        long long int a,b,p,n; cin >> a >> b;
        p = max(a,b); n = min(a,b);
        if(n==0 && p==0)
        {
            cout << "YES" << endl;
            continue;
        }
        if(p > 2*n)
            {
            cout << "NO" << endl;
            continue;
        }
        if((2*p - n) %3 != 0)
        {
            cout << "NO" << endl;
            continue;
        }
        long long int x = (2*p-n) /3;
        long long int y = (p-(x*2));
        if(n == (x + 2*y))
            cout << "YES" << endl;
        else 
            cout << "NO" << endl;
    }
    return 0;
}