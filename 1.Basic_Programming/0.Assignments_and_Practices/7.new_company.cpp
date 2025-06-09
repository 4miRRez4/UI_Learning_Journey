#include <iostream>
#include <vector>
using namespace std;


int main()
{
    int t; cin >> t;
    while(t--)
    {
        int w, h, n; cin >> w >> h >> n;
        vector<vector<int>> floor (h, vector<int> (w,0));
        vector<string> names (n);
        vector<vector<int>> rooms (n, vector<int> (4, 0));
        for(int i=0; i<n; i++)
        {
            string name; cin >> name;
            names[i] = name;
            int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            rooms[i][0] = x1;
            rooms[i][1] = y1;
            rooms[i][2] = x2;
            rooms[i][3] = y2;

            for(int r=y1; r<y2; r++)
            {
                for(int c=x1; c<x2; c++)
                {
                    floor[r][c]++;
                }
            }
        }
        cout << w*h << endl;

        int empty = 0;
        int moreThanOne = 0;
        for(int r=0; r<h; r++)
            for(int c=0; c<w; c++)
            {
                if(floor[r][c] == 0)
                    empty++;
                else if(floor[r][c] > 1)
                    moreThanOne++;
            }

//         for(int r=0; r<h; r++)
// {            for(int c=0; c<w; c++)
//             {
//                 cout << floor[r][c] << " ";
//             }
//             cout << endl;}

        cout << empty << endl;
        cout << moreThanOne << endl;

        for(int p=0; p<n; p++)
        {
            cout << names[p] << " ";
            int sureThing = 0;
            for(int r=rooms[p][1]; r<rooms[p][3]; r++)
                for(int c=rooms[p][0]; c<rooms[p][2]; c++)
                    if(floor[r][c] == 1)
                        sureThing++;
            cout << sureThing << endl;
        }
    }

    return 0;
}