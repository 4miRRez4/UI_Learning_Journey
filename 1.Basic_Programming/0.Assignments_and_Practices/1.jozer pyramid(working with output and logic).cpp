#include <iostream>

using namespace std;

int main()
{
    int height;
    cin >> height;

    for(int line = 1; line <= height; line++)
        {
        int space = height-line;
        //printing start spaces.
        for (int i = 1; i <= space; i++)
        {
            cout << "  ";
        }
        
        //printing ascending numbers.
        for (int j = 1; j <= line ; j++)
        {
            cout << j << " ";
        }

        //printing descending numbers.
        for (int k = line-1; k >= 1 ;k--)
        {
            cout << k << " ";
        }

        //printing end spaces.
        for (int x = height-line; x >= 1; x--)
        {
            cout << "  ";
        }
        cout << endl;
        
    }

}