#include <iostream>
using namespace std; 

class shitException {};

void h() { cout << 5; throw shitException(); cout << 6; }
void g() { cout << 3; h(); cout << 4; }

int main()
{
    try { cout << 1; g(); cout << 2; } 
    catch (shitException ex) 
    { cout << 7; } 
    cout << 8;

    return 0;
}