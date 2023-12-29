#include <iostream>

using namespace std;


int main(){
    printf("Enter your number: \n");
    int n;
    cin >> n;

    for (int i=1; i<n; i++) {
        if (i%2 == 0){
            printf("%i \n", i);
        }
    }
}
