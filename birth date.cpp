#include <iostream>
using namespace std;

int main() {
    char in[5];
    fgets(in,5,stdin);

    char saal[2];
    saal[0] = in[0];
    saal[1] = in[1];

    char maah[2];
    maah[0] = in[2];
    maah[1] = in[3];

    cout << "saal:" << saal[0] << saal[1] << endl;
    cout << "maah:" << maah[0] << maah[1] << endl;

}
