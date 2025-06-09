#include <iostream>
using namespace std;

void initializingMatris(int**& matris, int row, int col)
{
    matris = new int *[row];
    for(int r=0; r<row; r++)
        matris[r] = new int [col];
}

void gettingMatrix(int** matris, int row, int col)
{
    for(int r=0; r<row; r++)
    {
        for(int c=0; c<col; c++)
        {
            cout << "enter element of row:" << r+1 << " and column:" << c+1 << endl;
            cin >> matris[r][c];
        }
    }
}

void printMatris(int** matris, int row, int col){
    for(int r=0; r<row; r++)
    {
        for(int c=0; c<col; c++)
        {
            cout << matris[r][c] << " ";
        }
        cout << endl;
    }
}

int main()
{
    //getting matris 1
    int row, col;
    cout << "enter row and column: ";
    cin >> row >> col;
    int** a;
    initializingMatris(a, row, col);
    cout << "enter elements of first one: " << endl;

    gettingMatrix(a, row, col);
    //getting matris 2
    int** b;
    initializingMatris(b, row, col);
    cout << "enter elements of second one: " << endl;
    gettingMatrix(b, row, col);
    //calculating sum of matrises:
    int** sum;
    initializingMatris(sum, row, col);
    for(int r=0; r<row; r++)
    {
        for(int c=0; c<col; c++)
        {
            sum[r][c] = a[r][c] + b[r][c];
        }
    }
    //printing answer
    printMatris(sum, row, col);

    return 0;
}