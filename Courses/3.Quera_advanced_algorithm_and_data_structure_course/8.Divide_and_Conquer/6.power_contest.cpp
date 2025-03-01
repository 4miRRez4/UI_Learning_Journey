#include <iostream>
#include <cmath>
using namespace std;

void prizes(int powers[], float& avg, int& ifChosed, int& ifNotChosed, int l, int r){
    if(r <= l){
        avg = ifChosed = ifNotChosed = powers[l];
        return;
    }

    int mid = l + (r-l)/2;
    float avg1 = 0,avg2=0;
    int ifCh1=0, ifCh2=0, ifNCh1=0, ifNCh2=0;
    prizes(powers, avg1, ifCh1, ifNCh1, l, mid);
    prizes(powers, avg2, ifCh2, ifNCh2, mid+1, r);

    //choose
    if(avg1 > avg2){
        ifChosed = ifCh1 + ifNCh2;
    }else{
        ifChosed = ifCh2 + ifNCh1;
    }
    ifNotChosed = max(ifNCh1, ifNCh2);
}

int main(){
    int n; cin >> n;
    int numOfTeams = pow(2, n);
    int powers[numOfTeams];
    for(int i=0; i<numOfTeams; i++)
        cin >> powers[i];

    float avg=0;
    int ifCh=0, ifNCh=0;
    prizes(powers, avg, ifCh, ifNCh, 0, numOfTeams-1);

    cout << ifCh << endl;

    return 0;
}