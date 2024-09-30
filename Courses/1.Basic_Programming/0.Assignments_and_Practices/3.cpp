#include <iostream>

using namespace std;

int main(){
    printf("enter your number: \n");
    int n;
    cin >> n;

    int max = n;
    int min = n;

    while (n != 0){
        if(n > max){
            max = n;
        }
        else if(n < min){
            min = n;
        }
        cin >> n;
    }
    printf("max: %i \nmin: %i \n", max, min);
}
