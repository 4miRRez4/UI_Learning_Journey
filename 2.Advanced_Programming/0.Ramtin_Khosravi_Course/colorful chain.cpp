//https://ramtung.ir/teaching.html#courses ap assignment1 part 1

#include <iostream>
using namespace std;


int iteratingThrough(string chain, int len, int* where)
{
    //iterating through chain and count score of it and compare it;(I considered selected nut with left side)
    chain += chain; //dealing with feature of chain

    int max =0, selectedScore, j;
    char selectedColor;
    for(int i=0; i<2*len; i++)
    {
        selectedScore = 0;
        //counting scores of left side
        j = i;
        if(chain[j] == 'r' || chain[j] == 'b')
            selectedColor = chain[i];
        else if(j>0)
            j--;
        else
            selectedColor = 'c';
        while((chain[j] == selectedColor) || (chain[j] == 'w') & (j>=0))
        {
            selectedScore++;
            j--;
        }
        //counting scores of right side
        j = i+1;
        if(chain[j] == 'r' || chain[j] == 'b')
            selectedColor = chain[j];
        else if(j<2*len)
            j--;
        else
            selectedColor = 'c';

        while((chain[j] == selectedColor) || (chain[j] == 'w') & (j<2*len))
        {
            selectedScore++;
            j++;
        }
        //comparing to max score:
        if(selectedScore > max)
        {
            max = selectedScore;
            *where = i;
        }
    }
    return max;
}

int main()
{
    int n; cin >> n;
    string chain; cin >> chain;

    int where = -1;
    int maxScore = iteratingThrough(chain, n, &where);;
    cout << "Best score can be achieved via: " << where << "th place, with score of " << maxScore;

    return 0;
}