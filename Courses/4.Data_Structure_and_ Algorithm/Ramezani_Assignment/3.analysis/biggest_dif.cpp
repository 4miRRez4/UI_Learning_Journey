#include <iostream>
#include <cstdio>
#include <utility>
using namespace std;

int main(){
    pair<int, int> a;
    pair<int, int> b;
    pair<int, int> c;

    int n; scanf("%d\n", &n);
    scanf("%d %d\n", &a.first, &a.second);
    scanf("%d %d\n", &b.first, &b.second);
    int max_dif = abs(a.first - b.first) + abs(a.second - b.second);
    for(int i=2; i<n; i++){
        scanf("%d %d\n", &c.first, &c.second);
        int bc_dif = b.first - c.first + b.second - c.second;
        int ac_dif = max_dif + bc_dif;
    }



    return 0;
}