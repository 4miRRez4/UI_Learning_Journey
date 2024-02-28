//ramtin khosravi ap section 5
//https://www.geeksforgeeks.org/the-knights-tour-problem/
//https://www.youtube.com/watch?v=ab_dY3dZFHM
#include <iostream>
#include <vector>
using namespace std;

const int ROW_NUM = 5;
const int COL_NUM = 5;
const int POSSIBLE_MOVES = 8;

//possible moves of knight
int row_delta[POSSIBLE_MOVES] = {2, 1, -1, -2, -2, -1, 1, 2};
int col_delta[POSSIBLE_MOVES] = {-1, -2, -2, -1, 1, 2, 2, 1};

int sum(vector<int> arr, int i=0)
{
    if(i >= arr.size())
        return 0;
    return arr[i] + sum(arr, i+1);
}   

void printList(vector<vector<int>> board)
{
//     for(int i=0; i<board.size(); i++)
//     {
//         for(int j=0; j<board[i].size(); j++)
//         {
//             cout << board[i][j] << "  ";
//         }
//         cout << endl;
//     }
    for(auto arr:board)
    {
        for(auto num:arr)
        {
            if(num <10)
                cout << " ";
            cout << num << " ";
        }
        //cout << "  => " << sum(arr);
        cout << endl;
    }
 }

bool tour(vector<vector<int>>& board, int moveNum, int currentRow, int currentCol)
{
    cout << moveNum << "-----------" << endl;
    printList(board); 

    if(moveNum == ROW_NUM * COL_NUM) //does knight have seen all places?
        return true;

    for(int move=0; move< POSSIBLE_MOVES; move++) //iterating on all possible move from current place of knight
    {
        int newRow = currentRow + row_delta[move];
        int newCol = currentCol + col_delta[move];

        //is new place valid?
        if(newRow < 0 || newRow >= ROW_NUM || newCol < 0 || newCol >= COL_NUM)
            continue;

        //does the knight seen this new place?
        if(board[newRow][newCol] != 0)
            continue;

        //knight makes his next move
        moveNum++;
        board[newRow][newCol] = moveNum;
        
        //making move after this move
        if(tour(board, moveNum, newRow, newCol))
            return true;
        else//didn't new move work, so undo last move;
        {
            board[newRow][newCol] = 0;
            moveNum--;
        }
    }
    return false;//non of 8 possible moves of knight lead to finding solution!!!
}

int main()
{
    vector<vector<int>> board(ROW_NUM, vector<int> (COL_NUM,0));

    board[2][2] = 1;//first step

    if (tour(board, 1, 2, 2))
    {
        cout << "last ======" << endl;
        printList(board);
    }
    else
        cout << "Failed to find a tour!\n";
    
    return 0;
}