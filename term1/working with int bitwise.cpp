#include <iostream>
using namespace std;

int main()
{
    int a; cin >> a;
    int b; cin >> b;

    char* p1 = (char*)&a;
    char* p2 = (char*)&b;

    for(int i=0; i<4; i++)
    {
        char tmp = *(p1+i);
        *(p1+i) = *(p2+3-i);
        *(p2+3-i) = tmp;
    }

    cout << a << endl << b;

    return 0;
}
