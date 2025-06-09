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

void AddThreat(int (&table)[N][N], int (&threat)[N][N][N], int (&numOfThreats)[N][N]
                , int i, int j, int k){
    threat[i][j][k] += 1;

    if(threat[i][j][k] == 1) numOfThreats[i][j] += 1;
}

void RemoveThreat(int (&table)[N][N], int (&threat)[N][N][N], int (&numOfThreats)[N][N]
                , int i, int j, int k){
    threat[i][j][k] -= 1;

    if(threat[i][j][k] == 0) numOfThreats[i][j] -= 1;
}

bool Put(int (&table)[N][N], int (&threat)[N][N][N], int (&numOfThreats)[N][N]
            , int i, int j, int k){
    if(table[i][j] != 0 || threat[i][j][k-1] > 0)
        return false;
    
    table[i][j] = k;
    // Add threat
    for(int c=0; c<N; c++){
        AddThreat(table, threat, numOfThreats, i, c, k-1); // threat for row
        AddThreat(table, threat, numOfThreats, c, j, k-1); // threat for col
    }
    // threat for box
    for(int a=0; a<3; a++)
        for(int b=0; b<3; b++){
            AddThreat(table, threat, numOfThreats, 3*(i/3) + a, 3*(j/3) + b, k-1);
        }
    
    return true;
}

void Pick(int (&table)[N][N], int (&threat)[N][N][N],  int (&numOfThreats)[N][N]
            , int i, int j, int k){
    table[i][j] = 0;

    // Decrease threat
    for(int c=0; c<N; c++){
        RemoveThreat(table, threat, numOfThreats, i, c, k-1);
        RemoveThreat(table, threat, numOfThreats, c, j, k-1);
    }
    for(int a=0; a<3; a++){
        for(int b=0; b<3; b++){
            RemoveThreat(table, threat, numOfThreats, 3*(i/3) + a, 3*(j/3) + b, k-1);
        }
    }
}

bool FindNextCandidate(int (&table)[N][N], int (&numOfThreats)[N][N], int &x, int &y){
    int min_threat = N+1;
    bool found = false;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(table[i][j] == 0){
                if(numOfThreats[i][j] == N)
                    return false; // No digits can go here

                if(numOfThreats[i][j] < min_threat){
                    x = i;
                    y = j;
                    min_threat = numOfThreats[i][j];
                    found = true;
                }
            }
        }
    }
    
    return found;
}

bool Solve(int (&table)[N][N], int (&threat)[N][N][N], int (&numOfThreats)[N][N]
            , int emptyCells, int level){

    if(emptyCells <= level){
        PrintSolution(table);
        return true;
    }

    int x, y;
    if(FindNextCandidate(table, numOfThreats, x, y)){
        for(int k=1; k<=N; k++){
            if(Put(table, threat, numOfThreats, x, y, k)){
                if(Solve(table, threat, numOfThreats, emptyCells, level+1))
                    return true;
                Pick(table, threat, numOfThreats, x, y, k);
            }
        }
    }else
        return false;

    return false;
}
    


int main(){
    int table[N][N] = {};
    int numOfThreats[N][N] = {};
    int threat[N][N][N] = {};
    int emptyCells = 0, k;

    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++){
            cin >> k;
            if(k == 0) emptyCells++;
            else if(!Put(table, threat, numOfThreats, i, j, k)){
                cout << "Invalid Input!!!" << endl;
                exit(1);
            }
        }

    cout << endl;
    if(!Solve(table, threat, numOfThreats, emptyCells, 0)){
        cout << "No solutions exists" << endl;
    }

    return 0;
}