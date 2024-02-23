//https://quera.org/course/assignments/2693/problems/9124
#include <iostream>
using namespace std;

int main()
{
    int x1,y1,x2,y2;
    cin >> x1 >> y1 >> x2 >> y2;
    
    if(x1 < x2)
    {
        cout << "Right";
    }else
        cout << "Left";


    return 0;
}