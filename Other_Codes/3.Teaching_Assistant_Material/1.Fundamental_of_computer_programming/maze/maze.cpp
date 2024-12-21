#include <iostream>
using namespace std;

void print_maze(int* maze, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << *(maze + i * n + j) << " ";
            if(*(maze + i * n + j) < 10)
                cout << " ";
        }
        cout << endl;
    }
}


void generateSpiralMaze(int* maze, int n, int origin, int destination, 
                        int& originRow, int& originCol, int& destRow, int& destCol)
{
    int num = 0;
    int bottom = n - 1, right = n - 1, up = 0, left = 0;

    while(num < n * n)
    {
        // Filling bottom side
        for(int c = left; c <= right; c++)
        {
            *(maze + bottom * n + c) = ++num;
            if (num == origin) originRow = bottom, originCol = c;
            else if (num == destination) destRow = bottom, destCol = c;
        }
        bottom--;

        // Filling right side
        for(int r = bottom; r >= up; r--)
        {
            *(maze + r * n + right) = ++num;
            if (num == origin) originRow = r, originCol = right;
            else if (num == destination) destRow = r, destCol = right;
        }
        right--;

        // Filling up side
        for(int c = right; c >= left; c--)
        {
            *(maze + up * n + c) = ++num;
            if (num == origin) originRow = up, originCol = c;
            else if (num == destination) destRow = up, destCol = c;
        }
        up++;

        // Filling left side
        for(int r = up; r <= bottom; r++)
        {
            *(maze + r * n + left) = ++num;
            if (num == origin) originRow = r, originCol = left;
            else if (num == destination) destRow = r, destCol = left;
        }
        left++;
    }
}

int main()
{
    int n, origin, destination;
    cin >> n >> origin >> destination;

    int originRow = 0, originCol = 0, destRow = 0, destCol = 0;

    int* maze = (int*)calloc(n * n, sizeof(int));

    generateSpiralMaze(maze, n, origin, destination, originRow, originCol, destRow, destCol);

    int horizontal = destCol - originCol;
    int vertical = destRow - originRow;

    print_maze(maze, n);

    cout << abs(horizontal) << " " << ((horizontal > 0) ? "R" : "L") << endl;
    cout << abs(vertical) << " " << ((vertical < 0) ? "U" : "D") << endl;


    free(maze);

    return 0;
}
