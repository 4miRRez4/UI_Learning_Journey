#include <iostream>
using namespace std;

void print_maze(int* maze, int n)
{
    for(int r = 0; r < n; r++)
    {
        for(int c = 0; c < n; c++)
        {
            cout << *(maze + r * n + c) << " ";
            if(*(maze + r * n + c) < 10)
                cout << " ";
        }
        cout << endl;
    }
}


void generateSpiralMaze(int* maze, int n, int origin, int destination, 
                        int& originRow, int& originCol, int& destRow, int& destCol)
{
    int num = 0;
    int bottom_row = n - 1, right_col = n - 1, up_row = 0, left_col = 0;

    while(num < n * n)
    {
        // Filling bottom side
        for(int c = left_col; c <= right_col; c++)
        {
            *(maze + bottom_row * n + c) = ++num;
            if (num == origin) originRow = bottom_row, originCol = c;
            else if (num == destination) destRow = bottom_row, destCol = c;
        }
        bottom_row--;

        // Filling right side
        for(int r = bottom_row; r >= up_row; r--)
        {
            *(maze + r * n + right_col) = ++num;
            if (num == origin) originRow = r, originCol = right_col;
            else if (num == destination) destRow = r, destCol = right_col;
        }
        right_col--;

        // Filling up side
        for(int c = right_col; c >= left_col; c--)
        {
            *(maze + up_row * n + c) = ++num;
            if (num == origin) originRow = up_row, originCol = c;
            else if (num == destination) destRow = up_row, destCol = c;
        }
        up_row++;

        // Filling left side
        for(int r = up_row; r <= bottom_row; r++)
        {
            *(maze + r * n + left_col) = ++num;
            if (num == origin) originRow = r, originCol = left_col;
            else if (num == destination) destRow = r, destCol = left_col;
        }
        left_col++;
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


    cout << abs(horizontal) << " " << ((horizontal > 0) ? "R" : "L") << endl;
    cout << abs(vertical) << " " << ((vertical < 0) ? "U" : "D") << endl;

    print_maze(maze, n);

    free(maze);

    return 0;
}
