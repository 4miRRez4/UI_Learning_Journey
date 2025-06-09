#include <iostream>
using namespace std;

long long **storage;

long long Khayyam(int r, int c) {
    //base case
    if (c == 0 || c == r)
        return 1;
    //step
    if (storage[r][c] != 0)//checking if we have calculated this place before;
        return storage[r][c];

    storage[r][c] = Khayyam(r-1, c-1) + Khayyam(r-1,c);
    return storage[r][c];
}

int main() {
   int row;
   cin >> row;
    if (row <= 0){
        cout << "ERROR";
        return 0;
    }

    int column =(row/2)+1; //biggest element in any row is in column middle((row/2)+1);

    // allocating memory dynamicly(there is a pointer with len rows that points to pointers that their len's are number of elements in khayyam triange in that row;
    storage = new long long *[row];
    for(int r=0; r<row; r++) {
        if ((r + 1) < (column))
        {
            storage[r] = new long long[r + 1];
            for (int c = 0; c < r+1; c++) {
                storage[r][c] = 0;
            }
        }
        else
        {
            storage[r] = new long long[column];
            for(int c=0; c<column; c++)
            {
                storage[r][c] = 0;
            }
        }


    }

    long long largest = Khayyam(row-1, column-1);
    cout << largest;

    //deleting memory that is allocated
    for(int r=0; r<row; r++)
    {
        delete [] storage[r];
    }
    delete [] storage;



    return 0;
}
