//https://quera.org/course/assignments/67595/problems
#include <iostream>
using namespace std;

int main(){
    int n; cin >> n;

    int a,b,c,canBe = 0;
    for( a=1; a <= n/3; a++)
        for( b=n/2 -a+1; b<=(n-a)/2 ; b++)
        {
            c= n-a-b;
            // cout << a << b << c;
            if(a<=b && b<=c)
            {
                // cout << "tick";
                canBe++;
            }
            // cout << endl;
        }
    cout << canBe << endl;
    return 0;
}