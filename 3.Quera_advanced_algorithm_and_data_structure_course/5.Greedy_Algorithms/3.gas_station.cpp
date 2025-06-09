#include <iostream>
using namespace std;

int main(){
    int n, k, l; cin >> n >> k >> l;

    int stations[n];
    for(int i=0; i<n; i++)
        cin >> stations[i];

    string stopped_stations = "";
    int station_cnt=0, location=0, ind=-1;
    while(ind < n-1 && location+k < l){
        if((stations[ind+1] - location) > k){
            station_cnt = -1;
            break;
        }

        while(ind!=n-1 && (stations[ind+1] - location) <= k)
            ind++;

        location = stations[ind];
        stopped_stations += to_string(ind+1) + " ";
        station_cnt++;
    }
    if(location+k < l)
        station_cnt= -1;

    cout << station_cnt << endl;
    if(station_cnt != -1)
        cout << stopped_stations << endl;

    return 0;
}