#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main()
{
    int n, q, x1, x2, y1, y2, tnts; scanf("%d %d", &n, &q);
    // char** backYard = new char*[n];
    // for(int i=0; i<n; i++)
    //     backYard[i] = new char [n];
    // char backYard[n][n];
    // vector<vector<char>> backYard(n, vector<char>(n));
    int backYard[n][n] = {0};
    char tmp;
    for (int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            scanf(" %c", &tmp);
            backYard[i][j] = (tmp == '*') ? 1:0;
            if(j>0)
                backYard[i][j] += backYard[i][j-1];
        }
    }
    while(q--)
    {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        tnts = 0;
        for (int row = x1 - 1; row < x2; row++)
        {
            tnts+= backYard[row][y2-1] - ((y1>1) ? backYard[row][y1-2]:0);
        }
        printf("%d\n", tnts);
    }

    return 0;
}