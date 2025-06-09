#include <iostream>
using namespace std;

const int N = 9;

void PrintSolution(int table[N][N]){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++)
            cout << table[i][j] << " ";
        cout << endl;
    }
}

bool canPut(int (&table)[N][N], int i, int j, int k){
    //check Row and Column
    for (int c=0; c<N; c++)
        if (table[i][c] == k || table[c][j] == k)
            return false;


    //check 3x3 box
    int startRow = i - (i % 3), startCol = j - (j % 3);
    for (int a=0; a<3; a++)
        for (int b=0; b<3; b++)
            if (table[a + startRow][b + startCol] == k)
                return false;

    return true;
}

bool Solve(int (&table)[N][N], int i, int j){
    if(i == N-1 && j == 1) // Reached to the end of table
        return true;
    
    if(j == N){
        i++;
        j = 0;
    }

    //Cell is not empty
    if(table[i][j] != 0)
        return Solve(table, i, j+1);

    // Try all number for the cell
    for(int k=1; k<=N; k++){
        if(canPut(table, i, j, k)){
            table[i][j] = k;
            if(Solve(table, i, j+1)) return true;
            table[i][j] = 0;
        }
    }

    return false;
}
    


int main(){
    int table[N][N] = {};

    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++){
            cin >> table[i][j];
        }

    cout << endl;
    if(!Solve(table, 0, 0)){
        cout << "No solutions exists" << endl;
    }else{
        PrintSolution(table);
    }

    return 0;
}