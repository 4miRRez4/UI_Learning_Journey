#include <iostream>
#include <cstring>
using namespace std;

int main() {
    int r,c;
    cin >> r; cin >> c;
    string envir[r][c];

    for(int row=0; row<r; row++)
    {
        for(int column=0; column<c; column++)
        {
            cin >> envir[row][column];
        }
    }

    for(int column =0; column<c; column++)//iterating on columns from right to left;
    {
        int temperature = 0;
        for(int row=r-1; row>=0; row--)//iterating on rows from buttom to up;
        {
            string element = envir[row][column];
            if(element != "b")//adding up temperature of baloon at current place;
            {
                int k =0;
                int sum =0;
                while(element[k])
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
                    envir[row][column] = "x";
                    break;
                }
                else
                {
                    if(row-1 < 0) break;
                    string next = envir[row-1][column];
                    int k =0;
                    int sum =0;
                    while(next[k])
                    {
                        int digit = next[k]-48;
                        sum = sum*10 + digit;
                        k++;
                    }

                    temperature += sum;

                    envir[row][column] = next;
                    if(temperature >= 100)
                    {
                        envir[row-1][column] = "x";
                        break;
                    }else
                    {
                        envir[row-1][column] = "b";
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

    return 0;
}
