#include <iostream>
using namespace std;


int main()
{
    int grade=0, n=0;
    float sum=0;
    while(grade!=-1)
    {
        sum+= grade;
        n++;
        cout << "please enter your grade:(for finish enter -1) ";
        cin >> grade;
    }
    float avg = sum/(n-1);
    cout << "average of your term is: " << avg;
    return 0;
}
