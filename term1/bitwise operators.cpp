#include <iostream>
#include <cstring>
using namespace std;

int main() {
    int a,b;
    cin >> a >> b;

    int c; cin >> c;


    for(int i=0; i<c; i++)
    {
        char command[8];
        cin >> command;

        int out=0;
        if(strcmp(command,"AND") == 0) out = a&b;
        else if(strcmp(command,"OR") == 0) out = a|b;
        else if(strcmp(command,"XOR") == 0) out = a^b;
        else if(strcmp(command,"Shift_L") == 0) out = a<<b;
        else if(strcmp(command,"Shift_R") == 0) out = a>>b;

        cout << out << endl;
    }
    return 0;
}
