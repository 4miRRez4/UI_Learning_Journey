#include <iostream>
#include <cstring>
using namespace std;



int str_cmp(const char* command,const char* suspect)
{
    while (*command != '\0' && *command == *suspect) {
        ++command;
        ++suspect;
    }

    return (*command > *suspect) - (*command < *suspect);
}

int main() {
    int a,b;
    cin >> a >> b;

    int c; cin >> c;


    for(int i=0; i<c; i++)
    {
        char* command;
        cin >> command;

        int out=0;
        if(str_cmp(command,"AND") == 0) out = a&b;
        else if(str_cmp(command,"OR") == 0) out = a|b;
        else if(str_cmp(command,"XOR") == 0) out = a^b;
        else if(str_cmp(command,"Shift_L") == 0) out = a<<b;
        else if(str_cmp(command,"Shift_R") == 0) out = a>>b;

        cout << out << endl;
    }
    return 0;
}
