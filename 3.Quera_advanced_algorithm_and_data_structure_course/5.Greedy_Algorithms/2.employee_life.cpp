#include <iostream>
#include <algorithm>
using namespace std;


int main(){
    int n; cin >> n;
    int deadlines[n] = {};
    for(int i=0; i<n; i++){
        cin >> deadlines[i]; 
    }

    sort(deadlines, deadlines+n);

    int time = 0, work_done = 0;
    for(int i=0; i<n; i++){
        int closest_word_deadline = deadlines[i];
        if(closest_word_deadline > time){
            work_done++;
            time++;
        }
    }

    cout << work_done << endl;


    return 0;
}