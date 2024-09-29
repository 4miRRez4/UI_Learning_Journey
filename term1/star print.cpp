#include <iostream>
using namespace std;


int main() {
    int height; cin >> height;

    for(int h=height; h>0; h--)//iterating for each line
    {
        //printing fist spaces;
        for(int i=0; i<(height-h); i++) cout << ' ';

        //printing stars;
        for(int i=0; i<((2*h)-1); i++) cout << '*';

        //printing last spaces;
        for(int i=0; i<(height-h); i++) cout << ' ';

        cout << endl;
    }


    return 0;
}
