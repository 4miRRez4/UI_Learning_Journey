//https://en.wikipedia.org/wiki/Tower_of_Hanoi
#include <iostream>
using namespace std;

void Hanoi_Tower(int n, char from, char to, char aux, long long *cnt){
    if(n == 1){
        (*cnt)++;
        cout << to_string(*cnt) << " " << from << " " << to << endl;
    }
    else{
        Hanoi_Tower(n-1, from, aux, to, cnt);
        (*cnt)++;
        cout << to_string(*cnt) << " " << from << " " << to << endl;
        Hanoi_Tower(n-1, aux, to, from, cnt);
    }
}

int main(){
    int n; cin >> n;
    long long tmp = 0;
    Hanoi_Tower(n, 'A', 'B', 'C', &tmp);

    return 0;
}