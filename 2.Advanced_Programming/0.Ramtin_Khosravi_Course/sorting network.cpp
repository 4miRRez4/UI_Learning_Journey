//https://ramtung.ir/apnotes/html/05_Recursion.html
#include <iostream>
#include <vector>

using namespace std;

void isCharOkay(char in)
{
    if ((in != '-') & ((in <= 'a') & (in >= 'z')))
    {
        cout << "Invalid_network";
        exit(0);
    }
}

void isNetworkValid(vector<string> network, int column, int row)
{
    int counter =0;
    for(int c=0; c<column; c++)//column=>network[0].size();
    {
        for(int r=0; r<row; r++)//row=>network.size();
        {
            char selected = network[r][c];
            network[r][c] == '-';
            isCharOkay(selected);
            if(selected == '-')
                continue;
            
            counter++;
            for(int t=r+1; t<row; t++)
            {
                if(network[t][c] == selected)
                {
                    counter++;
                    network[t][c] = '-';
                }
            }
            
            if(counter != 2)
            {
                cout << "Invalid_network";
                exit(0);
            }
            counter = 0;
        }
    }
};

void swapTags(vector<int>& tag, int row1, int row2)
{
    int tmp = tag[row1];
    tag[row1] = tag[row2];
    tag[row2] = tmp;
}

void apply(vector<string>& network, vector<int>& tag, int row, int column)
{
    for(int c=0; c<column; c++)//iterating through each column
    {
        for(int r=0; r<row; r++)//iterating through each row of specified column
        {
            char character = network[r][c];
            if(character == '-')
                continue;

            for(int t=r+1; t<row; t++)//iterating through characters below selected character
            {
                char below = network[t][c];
                if(below == '-')
                    continue;
                else//its alphabet
                {
                    if((character == below) & (tag[r]>tag[t]))
                    {
                        swapTags(tag, r, t);
                        //avoiding duplicate calculation
                        network[r][c] = '-';
                        network[t][c] = '-';
                    }
                }

            }
        }
    }
}

bool isSorted(vector<int> tag, int row)
{
    for(int r=0; r<row-1; r++)
    {
        if(tag[r] > tag[r+1])
            return false;
    }
    return true;
}

int main()
{
    //getting user input
    int row, column;
    cin >> row; cin >> column;

    vector<string> network(row);
    for(int i=0; i<row; i++)
        cin >> network[i];

    cout << network[0].size();
    // vector<int> tag(row);
    // for(int i=0; i<row; i++)
    //     cin >> tag[i];

    // isNetworkValid(network, column, row);

    // apply(network, tag, row, column);

    // if(isSorted(tag, row))
    //     cout << "Sorted";
    // else
    //     cout << "Not_sorted";

    return 0;
}