#include <iostream>
using namespace std;

int main(){

    cout << "Type a number: ";
    int n;
    cin >> n;

    int sum = 0;
    
    int i = n%10;
    while (n>0){
        if (i%2 != 0){
            sum += i;
        }
        n = (n-i)/10;
        i = n%10;
    }
    printf("%i\n", sum);
    return 0;
}

