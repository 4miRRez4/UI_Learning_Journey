#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    int n; cin >> n;

    int k; cin >> k;
    cin.ignore();

    //allocating space for array;
    int *p = (int*) calloc(n, sizeof(int));

    //getting numbers from input using pointers;
    for(int i=0; i<n; i++)
    {
        cin >> *(p+i);
    }
    //for(int i=0; i<n; i++) cout << *(p+i) << ' ';

    //counting uprising teams;
    int counter = 0;
    int selected = *(p+k-1);
    for(int j=0; j<n; j++)
    {
        if(*(p+j) <= 0) continue;
        if(*(p+j) >= selected) counter++;
    }

    cout << counter;

    free(p);
    return 0;
}
