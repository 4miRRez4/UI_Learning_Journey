#include <iostream>
#include <cstring>
#include <istream>

using namespace std;

int main () {
    int row;
    cin >> row;

    int column;
    cin >> column;

    cin.ignore();

    char environment[row][column];
    for (int r = 0; r < row; r++) {
        for(int c=0; c<column; c++)
        {
            cin >> environment[r][c];
        }
    }

    bool change;
    do {
        change = false;
        //iterating on each row;
        for (int r = 0; r < row - 1; r++) {
            //iterating on each column;
            for (int c = 0; c < column; c++) {
                //checking if below selected character is empty to fall down for apple;
                if ((environment[r][c] == 'a') && (environment[r + 1][c] == '.')) {
                    environment[r + 1][c] = 'a';
                    environment[r][c] = '.';

                    change = true;
                }
            }
        }
    }while(change);

    for(int r=0; r<row; r++)
    {
        for (int c = 0; c < column; c++)
        {
            cout << environment[r][c];
        }
        cout << endl;
    }

    return 0;
}

