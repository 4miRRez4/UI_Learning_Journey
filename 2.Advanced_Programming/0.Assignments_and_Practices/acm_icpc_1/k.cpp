#include <iostream>
#include <vector>
using namespace std;

long long steps(int stairs, vector<int>& calculated)
{
    if(stairs == 1) return 1;
    if(stairs == 2) return 2;
    if(calculated[stairs-1] != 0)
        return calculated[stairs-1];
    long long tmp = steps(stairs-1, calculated) + steps(stairs-2, calculated);
    calculated[stairs-1] = tmp;
    return tmp;

    return tmp;
}


int main()
{
    int stairs; cin >> stairs;
    vector<int> calculated(stairs, 0);
    cout << steps(stairs, calculated);
}