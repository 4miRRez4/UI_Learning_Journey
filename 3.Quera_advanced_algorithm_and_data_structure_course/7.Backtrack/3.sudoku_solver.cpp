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

bool Put(int (&table)[N][N], int (&threat)[N][N][N], int i, int j, int k){
    if(table[i][j] != 0 || threat[i][j][k-1] > 0)
        return false;
    
    table[i][j] = k;
    // Add threat
    for(int c=0; c<N; c++){
        threat[i][c][k-1] += 1; // threat for row
        threat[c][j][k-1] += 1; // threat for col
    }
    // threat for box
    for(int a=0; a<3; a++)
        for(int b=0; b<3; b++){
            threat[3*(i/3) + a][3*(j/3) + b][k-1] += 1;
        }
    
    return true;
}

void Pick(int (&table)[N][N], int (&threat)[N][N][N], int i, int j, int k){
    table[i][j] = 0;
    // Decrease threat
    for(int c=0; c<N; c++){
        threat[i][c][k-1] -= 1;
        threat[c][j][k-1] -= 1;
    }
    for(int a=0; a<3; a++){
        for(int b=0; b<3; b++){
            threat[3*(i/3) + a][3*(j/3) + b][k-1] -= 1;
        }
    }
}

void Solve(int (&table)[N][N], int (&threat)[N][N][N], int emptyCells, int level){
    if(emptyCells <= level){
        PrintSolution(table);
        return;
    }

    // Iterate on table to find empty cell to fill
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(table[i][j] == 0){
                for(int k=1; k<=N; k++){
                    if(Put(table, threat, i, j, k)){
                        Solve(table, threat, emptyCells, level+1);
                        Pick(table, threat, i, j, k);
                    }
                }
            }
        }
    }

}

int main(){
    int table[N][N] = {};
    int threat[N][N][N] = {};
    int emptyCells = 0, k;

    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++){
            cin >> k;
            if(k == 0) emptyCells++;
            else if(!Put(table, threat, i, j, k)){
                cout << "Invalid Input!!!" << endl;
                exit(1);
            }
        }

    Solve(table, threat, emptyCells, 0);

    return 0;
}