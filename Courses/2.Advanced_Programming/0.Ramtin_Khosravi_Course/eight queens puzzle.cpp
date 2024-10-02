//ramtin khosravi ap section 5
//https://en.wikipedia.org/wiki/Eight_queens_puzzle
#include <iostream>
#include <vector>
using namespace std;
const int SIZE = 8;//dimention of board

int queens_col_in_row[SIZE];//we don't wanna use 2d array, so we can store col of queen in each row and handle it in print and so on.

bool threat(int row, int col, int prevRow, int queenCol)//does the queen at prevRow and queenCol threat new queen at row and col?
{
    return (row == prevRow || col == queenCol || abs(row - prevRow) == abs(col - queenCol));
}

bool isSafe(int row, int col)//is place of row and col safe for new queen?
{
    for(int prevRow=0; prevRow<row; prevRow++)//iterating on all rows before given row to check it's queen attack zone;
        if(threat(row, col, prevRow, queens_col_in_row[prevRow]))
            return false;
    return true;
}

void printBoard()
{
    for(int row=0; row<SIZE; row++)
    {
        for(int col=0; col<SIZE; col++)
            cout << (col == queens_col_in_row[row] ? "QQ" : "--");
        cout << endl;
    }
}

void play(int currentRow, int& counter)
{
    // cout << currentRowow << endl;
    // printBoard();

    if (currentRow == SIZE)//do all of rows been checked?
    {
        counter++;
        cout << "----------" << endl;
        printBoard();
        return;
    }

    for(int col=0; col<SIZE; col++)// iterating on each col of this row for possible move;
    {
        if(isSafe(currentRow, col))//checking for being safe
        {
            queens_col_in_row[currentRow] = col;//move
            play(currentRow+1, counter);
            queens_col_in_row[currentRow] = -1;//if solving sub problem wasn't successful, backtrack last move;
        }
    }
}

int main()
{
    for (int row = 0; row < SIZE; row++)
        queens_col_in_row[row] = -1;
    int counter =0;
    play(0, counter);
    cout << counter << endl;

    return 0;
}