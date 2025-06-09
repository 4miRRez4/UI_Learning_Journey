//https://ramtung.ir/teaching.html#courses ap assignment1 part 2
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    //getting input
    int n; cin >> n;
    vector<string> before;
    string line;
    for(int i=0; i<n; i++)
    {
        cin>>line;
        before.push_back(line);
    }
    vector<string> after;
    for(int i=0; i<n; i++)
    {
        cin>>line;
        after.push_back(line);
    }

    //generating each command
    vector<string> generated = before;

    //1.90 degree clockwise rotation
    //iterating through each character and using formula=> newColumn = n-1-oldRow; newRow = oldColumn
    for(int r=0; r<n; r++)
    {
        for(int c=0; c<n; c++)
        {
            generated[c][n-1-r] = before[r][c];
        }
    }
    //comparing
    if(after == generated)
    {
        cout << "90 degree clockwise rotation";
        return 0;
    }
    //2.180 degree clockwise rotation
    //iterating through each character and using formula=> newColumn = n-1-oldColumn and newRow = n-1-oldRow
    for(int r=0; r<n; r++)
    {
        for(int c=0; c<n; c++)
        {
            generated[n-1-r][n-1-c] = before[r][c];
        }
    }
    //comparing
    if(after == generated)
    {
        cout << "180 degree clockwise rotation";
        return 0;
    }
    
    //3.Projection around the vertical axis of the middle of the table
    for(int r=0; r<n; r++)
    {
        for(int c=0; c<n; c++)
        {
            generated[r][n-1-c] = before[r][c];
        }
    }
    //comparing
    if(after == generated)
    {
        cout << "180 degree clockwise rotation";
        return 0;
    }

    


    cout << "generated: " << endl;
    for (int i=0; i<n; i++)
        cout << generated[i] << endl;

    
    return 0;
}