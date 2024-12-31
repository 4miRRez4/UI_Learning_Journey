#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;


void print_maze(int* maze, int n, string& answer)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            answer += to_string(*(maze + i * n + j)) + " ";
            if(*(maze + i * n + j) < 10)
                answer += " ";
        }
        answer += "\n";
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

string mazeQ(int n, int origin, int destination)
{
    int originRow = 0, originCol = 0, destRow = 0, destCol = 0;

    int* maze = (int*)calloc(n * n, sizeof(int));

    generateSpiralMaze(maze, n, origin, destination, originRow, originCol, destRow, destCol);

    int horizontal = destCol - originCol;
    int vertical = destRow - originRow;

    string answer = "";
    answer += to_string(abs(horizontal)) + " " + ((horizontal > 0) ? "R" : "L") + "\n";
    answer += to_string(abs(vertical)) + " " + ((vertical < 0) ? "U" : "D") + "\n";

    print_maze(maze, n, answer);

    free(maze);
    return answer;
}

void generateTestCase(string inFileName, string outFileName) {
    FILE* inFile = fopen(inFileName.c_str(), "w");
    if (!inFile) {
        cerr << "Error: Could not open file " << inFileName << " for writing." << endl;
        return;
    }

    int minVal1 = 2, maxVal1 = 9;
    int randNum1 = minVal1 + (rand() % (maxVal1 - minVal1 + 1));

    int minVal2 = 1, maxVal2 = randNum1 * randNum1;
    int randNum2 = minVal2 + (rand() % (maxVal2 - minVal2 + 1));
    int randNum3;
    do {
        randNum3 = minVal2 + (rand() % (maxVal2 - minVal2 + 1));
    } while (randNum3 == randNum2);

    fprintf(inFile, "%d %d %d\n", randNum1, randNum2, randNum3);
    fclose(inFile);

    FILE* outFile = fopen(outFileName.c_str(), "w");
    if (!outFile) {
        cerr << "Error: Could not open file " << outFileName << " for writing." << endl;
        return;
    }

    string answer = mazeQ(randNum1, randNum2, randNum3);
    fprintf(outFile, "%s", answer.c_str());


    fclose(outFile);
}

int main() {
    srand(time(nullptr));

    int n; cin >> n;
    for(int i=1; i<=n; i++){
        string inFileName = "input" + to_string(i) + ".txt";
        string outFileName = "output" + to_string(i) + ".txt";
        generateTestCase(inFileName, outFileName);
    }

    return 0;
}
