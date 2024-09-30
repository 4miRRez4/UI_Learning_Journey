//https://quera.org/problemset/179665
#include <iostream>
#include <vector>
using namespace std;

void print_maze(vector<vector<int>> maze)
{
    for(auto array:maze)
    {
        for(auto number:array)
        {
            cout << number << " ";
            if(number < 10)
                cout << " ";
        }
        cout << endl;
    }
}

void isThePlace(vector<vector<int>>& road, int num, int origin, int destination, int row, int col)
{
    if(num == origin) 
    {
        road[0][0] = row;
        road[0][1] = col;
    }else if(num == destination) 
    {
        road[1][0] = row;
        road[1][1] = col;
    }
}

void generateSpiralMaze(vector<vector<int>>& maze, int n, int origin, int destination,vector<vector<int>>& road)
{
    int num=0;
    int bottom=n-1, right=n-1, up=0, left =0;

    while(num<n*n)
    {
        //filling bottom side
        for(int c=left; c<=right; c++)
        {
            maze[bottom][c] = ++num;
            isThePlace(road, num, origin, destination, bottom, c);
        }
        bottom--;

        //filling right side 
        for(int r=bottom; r>=up; r--)
        {
            maze[r][right] = ++num;
            isThePlace(road, num, origin, destination, r, right);
        }
        right--;

        //filling up side
        for(int c=right; c>=left; c--)
        {
            maze[up][c] = ++num;
            isThePlace(road, num, origin, destination, up, c);
        }
        up++;

        //filling left side
        for(int r=up; r<=bottom; r++)
        {
            maze[r][left] = ++num;
            isThePlace(road, num, origin, destination, r, left);
        }
        left++;
    }
}

int main()
{
    int n, origin, destination; cin >> n >> origin >> destination;

    vector<vector<int>> maze (n, vector<int> (n));
    vector<vector<int>> road (2, vector<int> (2,0)); //{{originRow, originCol},{destinationRow, destinationCol}}
    generateSpiralMaze(maze, n, origin, destination, road);

    int horizontal = road[1][1] - road[0][1]; //destinationCol - originCol
    int vertical = road[1][0] - road[0][0]; //destinationRow - destinationRow
    
    if(horizontal != 0)
        cout << abs(horizontal) << " " << ((horizontal>0) ? "R" : "L") << endl;
    if(vertical != 0)
        cout << abs(vertical) << " " << ((vertical<0) ? "U" : "D") << endl;


    // print_maze(maze);
    return 0;
}