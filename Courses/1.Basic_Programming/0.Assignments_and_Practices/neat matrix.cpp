#include <iostream>
using namespace std;

void gettingMatris(int **matris, int r, int c)
{
    for(int i=0; i<r; i++)
    {
        for(int j=0; j<c; j++)
        {
            cin >> matris[i][j];
        }
    }

};

void deletingMatris(int **array, int r, int c)
{
    for(int i=0; i<r; i++)//deleting columns
    {
        delete [] array[i];
    }
    delete [] array;//deleting rows;
}

void printingMatrises(int **array, int r, int c)
{
    for(int i=0; i<r; i++)
    {
        for(int j=0; j<c; j++)
        {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}

void correspondingChange(int **a, int **b,int i, int j)
{
    int tmp = a[i][j];
    a[i][j] = b[i][j];
    b[i][j] = tmp;
}

bool isAscending(int **a, int r, int c)
{
    bool status = true;
    //checking for being ascending horizantal;
    for(int i=0; i<r; i++)//iterating on rows;
    {
        for(int j=0; j<c-1; j++)//iterating on columns;
        {
            if(a[i][j] >= a[i][j+1])
            {
                status = false;
            }
        }
    }

    //checking for being ascending vertical;
    for(int j=0; j<c; j++)//iterating on columns;
    {
        for(int i=0; i<r-1; i++)//iteratign on rows;
        {
            if(a[i][j] >= a[i+1][j])
            {
                status = false;
            }
        }
    }
    return status;
}

void seperating(int **a, int **b, int r, int c)
{
    //this function compares two elements of same place in matrises and swaps if not ascending(we wanna have bigger and smaller matrises)
    for(int i=0; i<r; i++)//iterating on rows
    {
        for(int j=0; j<c; j++)//iteratign on columns;
        {
            if(a[i][j] > b[i][j])
            {
                correspondingChange(a, b, i, j);
            }
        }
    }
}

int main() {
    int r,c; //getting rows and columns;
    cin >> r >> c;

    //initializing 2d arrays for storing the matrises;
    int **a = new int *[r];
    for(int i=0; i<r; i++)
    {
        a[i] = new int[c];
    }
    int **b = new int *[r];
    for(int i=0; i<r; i++)
    {
        b[i] = new int[c];
    }

    //getting matrises;
    gettingMatris(a, r, c);
    gettingMatris(b, r, c);

    //for satisfaeing condition we can convert matrises to two bigger and smaller matrises and then check condition of being ascending
    seperating(a, b, r, c);

    //checking the matris being ascending;
    if(isAscending(a, r, c) && isAscending(b, r, c))
    {
        cout << "Possible";
    }else
    {
        cout << "Impossible";
    }

    //printing matrises;
    //printingMatrises(a, r, c);
    //printingMatrises(b, r, c);

    //deleting pointers
    deletingMatris(a, r, c);
    deletingMatris(b, r, c);

    return 0;
}
