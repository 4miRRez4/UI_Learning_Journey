#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    //aX2 + bX + c =0
    int a, b, c;
    cin >> a >> b >> c;
    
    float delta = b*b - 4*a*c;
    if(delta == 0)// has one answer
    {
        float answer = (-b + sqrt(delta))/2*a;
        cout << answer;
    }else if (delta > 0)// has two answers
    {
        float answer1 = (-b + sqrt(delta))/2*a;
        float answer2 = (-b - sqrt(delta))/2*a;
        cout << answer1 << " and " << answer2;
    }else //delta <0. has zero answers
    {
        cout << "NOT ANSWER";
    }


    return 0;
}