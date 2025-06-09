#include <iostream>
using namespace std;

int main()
{

    char num1[100];
    cin >> num1;

    //initializing an array with number 0(cleaning garbage value;
    int num_a[100] = {};

    //finding length on num1 by iterating on pointers;
    int l = 0;
    char* p = &num1[0];
    while(*p!='\0')
    {
        l++;
        p++;
    }

    //setting num1 to an array backward;
    for(int z=l-1; z>=0; z--)
    {
        num_a[l-z-1] = num1[z]-48;
    }

    //getting the second number;
    char num2[100];
    cin >> num2;

    int num_b[100] = {};

    //finding length on num2 by iterating on pointers;
    int l2 = 0;
    char* m = &num2[0];
    while(*m!='\0')
    {
        l2++;
        m++;
    }

    //setting num2 to an array backward;
    for(int z=l2-1; z>=0; z--)
    {
        num_b[l2-z-1] = num2[z]-48;
    }

    //summing up;
    int hand = 0;
    int x = 0;
    int length;
    if(l2>l)
    {
        length = l2;
    }else
    {
        length = l;
    }

    for(int k=0; k<length; k++)
    {
        x = (num_a[k] + num_b[k] + hand);
        num_a[k] = x % 10;
        hand = x/10;
    }
    if(hand != 0)
    {
        cout << 1;
    }

    for(int r = length-1; r>=0; r--){
        cout << num_a[r];
    }



    return 0;
}

