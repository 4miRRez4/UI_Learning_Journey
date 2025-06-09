#include <iostream>

using namespace std;

int main() 
{
    int rows;
    cin >> rows;

    //iterating for printing each numbers;
    for(int line = 1; line <= rows; line++)
    {
        //iterating for printing start spaces;
        for(int space = 1; space <= (rows-line); space++)
        {
            cout << "    ";
        }

        //iterating for printing ascending numbers;
        for(int i = 1; i <= line; i++)
        {
            cout << i << "   ";
        }

        //iterating for printing descending numbers;
        for(int j = (line-1); j >= 1; j--)
        {
            cout << j << "   ";
        }

        //iterating for printing last spaces;
        for(int space = 1; space <= (rows-line); space++)
        {
            cout << "    ";
        }
        cout << endl;
    }


    //iterating for printing alphabet;
    for(int line = rows; line > 0; line--)
    {
        //iterating for printing start spaces;
        for(int space = 1; space <= (rows-line); space++)
        {
            cout << "    ";
        }

        //iterating for printing ascending alphabet;
        for(char chr = 65; chr < (65+line); chr++)
        {
            cout << chr << "   ";
        }
            
        //iterating for printing descending alphabet;
        for(char chr= (65+line-2); chr >=65; chr--)
        {
            cout << chr << "   ";
        }

        //iterating for printing last spaces;
        for(int space = 1; space <= (rows-line); space++)
        {
            cout << "    ";
        }
        cout << endl;
    }
}