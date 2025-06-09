//giving perfect square numbers in given range
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int main()
{
    int numberOfInputs; cin >> numberOfInputs;
    for(int r=0; r<numberOfInputs; r++)
    {
        int start, end;
        cin >> start >> end;
        int n=0;
        vector<int> perfectSquares;
        int startSqrt = sqrt(start);
        int endSqrt = sqrt(end);
        //cout << startSqrt << endSqrt;
        if(start == startSqrt*startSqrt)
        {
            perfectSquares.push_back(startSqrt);
            n++;
        }
        for(int i=startSqrt+1; i<= endSqrt; i++)
        {
            perfectSquares.push_back(i);
            n++;
        }
        // for(int j=0; j<perfectSquares.size(); j++)
        //     cout << perfectSquares[j] << " ";
        cout << n;
        cout << endl;
    }


    return 0;
}