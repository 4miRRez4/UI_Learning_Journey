#include <iostream>
#include <cstring>
using namespace std;

int main() {
    int r,c;
    cin >> r; cin >> c;
    char*** envir = new char**[r];

    for(int row=0; row<r; row++)
    {
        envir[row] = new char *[c];
        for(int column=0; column<c; column++)
        {
            envir[row][column] = new char[100];
            cin >> envir[row][column];
        }
    }

    for(int column =0; column<c; column++)//iterating on columns from right to left;
    {
        int temperature = 0;
        for(int row=r-1; row>=0; row--)//iterating on rows from buttom to up;
        {
            char element[10] = {};
            strcpy(element, envir[row][column]);
            if(strcmp(element, "b") != 0)//adding up temperature of baloon at current place;
            {
                int k =0;
                int sum =0;
                while(element[k])//
                {
                    int digit = element[k]-48;
                    sum = sum*10 + digit;
                    k++;
                }

                temperature += sum;
                continue;
            }else//baloon going up
            {
                if(temperature >= 100)
                {
                    strcpy(envir[row][column], "x");
                    break;
                }
                else
                {
                    if(row-1 < 0) break;
                    char next[10] = {};
                    strcpy(next, envir[row-1][column]);
                    int k =0;
                    int sum =0;
                    while(next[k])
                    {
                        int digit = next[k]-48;
                        sum = sum*10 + digit;
                        k++;
                    }

                    temperature += sum;

                    strcpy(envir[row][column], next);
                    if(temperature >= 100)
                    {
                        strcpy(envir[row-1][column] , "x");
                        break;
                    }else
                    {
                        strcpy(envir[row-1][column] , "b");
                    }

                }
            }
        }
    }

    for(int row=0; row<r; row++)
    {
        for(int column=0; column<c; column++)
        {
            cout << envir[row][column] << ' ';
        }
        if(row != r-1) cout << endl;
    }

    for(int row=0; row<r; row++)
    {
        for(int column=0; column<c; column++)
        {
            delete [] envir[row][column];
        }
        delete [] envir[row];
    }
    delete [] envir;

    return 0;
}
