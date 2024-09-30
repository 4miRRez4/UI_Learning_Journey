#include <iostream>

using namespace std;

int main()
{
    int lines;
    cin >> lines;


    int nums[lines];
    int j = 1;
    for(int i = 0; i<= (lines-1); i++)
    {
        nums[i] = j;
        cout << nums[i];
        j += 1;
        if (i != (lines-1))
        {
            cout << " | ";
        }

    }
    
    
    for(int line = 2; line <= lines; line++)
    {
        cout << endl;
        for(int k = 0; k <= lines-1; k++)
        {
            cout << line*nums[k] ;
            if (k != (lines-1))
            {
                cout << " | ";
            }
            
        }
    }
}