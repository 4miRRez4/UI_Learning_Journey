#include <iostream>
#include "iostream"
using namespace std;

int main() {
    char x[10000];
    int i, n, j;
    cin.getline(x,1000);
    for(i = 0; i < 10000; i++){
        if(x[i] == '\0') break;
    }
    n = (i + 3) / 4;

    int arr[n] = {0};
    for(i = 0; i < n; i++) {
        for(j = 0; j < 4; j++) {
            if(4 * i + j < i) {
                arr[i] = arr[i] << 8 | x[4 * i + j];
            } else {
                arr[i] = arr[i] << 8 | 0;
            }
        }
    }
    for(i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

}

