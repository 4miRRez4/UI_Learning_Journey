#include <iostream>
#include <string>
using namespace std;

int main() {
    int n; cin >> n;
    int A[n];
    for(int i=0; i<n; i++) cin >> A[i];

    char* p = (char*)&A[0];
    char out = 0;
    while(*p != '\0')
    {
        if(*p < 0) out =~*p;
        else out = *p;
        cout << out;
        p++;
    }

    return 0;
}
