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

bool canPut(int (&table)[N][N], int i, int j, int k,  int (&row_mask)[N], int (&col_mask)[N], int (&box_mask)[N]){
    // check row
    if(row_mask[i] & (1 << k))
        return false;

    // check column
    if(col_mask[j] & (1 << k))
        return false;
    
    // check box
    if(box_mask[i/3*3 + j/3] & (1 << k))
        return false;

    return true;
}

void Put(int (&table)[N][N], int i, int j, int k, int (&row_mask)[N], int (&col_mask)[N], int (&box_mask)[N]){
    table[i][j] = k;

    row_mask[i] |= (1 << k);
    col_mask[j] |= (1 << k);
    box_mask[i/3*3 + j/3] |= (1 << k);
}

void Pick(int (&table)[N][N], int i, int j, int k, int (&row_mask)[N], int (&col_mask)[N], int (&box_mask)[N]){
    table[i][j] = 0;

    row_mask[i] &= ~(1 << k);
    col_mask[j] &= ~(1 << k);
    box_mask[i/3*3 + j/3] &= ~(1 << k);
}

bool Solve(int (&table)[N][N], int i, int j, int (&row_mask)[N], int (&col_mask)[N], int (&box_mask)[N]){
    if(i == N-1 && j == N) // Reached to the end of table
        return true;
    
    if(j == N){
        i++;
        j = 0;
    }

    //Cell is not empty
    if(table[i][j] != 0)
        return Solve(table, i, j+1, row_mask, col_mask, box_mask);

    // Try all number for the cell
    for(int k=1; k<=N; k++){
        if(canPut(table, i, j, k, row_mask, col_mask, box_mask)){
            Put(table, i, j, k, row_mask, col_mask, box_mask);

            if(Solve(table, i, j+1, row_mask, col_mask, box_mask)) return true;

            Pick(table, i, j, k, row_mask, col_mask, box_mask);
        }
    }

    return false;
}
    


int main(){
    int table[N][N] = {};
    int row_mask[N] = {}, col_mask[N] = {}, box_mask[N] = {};

    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++){
            int number; cin >> number;
            table[i][j] = number;
            if (number != 0) {
                row_mask[i] |= (1 << number);
                col_mask[j] |= (1 << number);
                box_mask[i/3*3 + j/3] |= (1 << number);
            }
        }

    cout << endl;
    if(!Solve(table, 0, 0, row_mask, col_mask, box_mask)){
        cout << "No solutions exists" << endl;
    }else{
        PrintSolution(table);
    }

    return 0;
}