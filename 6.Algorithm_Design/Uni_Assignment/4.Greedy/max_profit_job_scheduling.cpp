#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int n; cin >> n;
    vector<pair<int, int>> jobs(n); // {deadline, profit}
    for(int i=0; i<n; i++){
        cin >> jobs[i].first >> jobs[i].second;
    }

    sort(jobs.begin(), jobs.end(), [](pair<int, int> a, pair<int, int> b){ 
        if (a.second == b.second) {
            return a.first < b.first;
        }
        return a.second > b.second;
    }
    );

    int max_deadline = (*max_element(jobs.begin(), jobs.end())).first;
    pair<int, int> null_pair = {0, 0};
    vector<pair<int, int>> schedule(max_deadline, null_pair);
    
    for(int i=0; i<n; i++){
        pair<int, int> curr_job = jobs[i];

        int idx = curr_job.first - 1;
        while(schedule[idx] != null_pair){
            idx--;
        }

        if(idx >= 0){
            schedule[idx] = curr_job;
        }
    }

    int total_profit = 0;
    for(int i=0; i<max_deadline; i++){
        if(schedule[i] != null_pair){
            int d = schedule[i].first;
            int p = schedule[i].second;

            cout << i+1 << " " << d << " " << p << endl;
            total_profit += p;
        }
    }
    cout << endl << total_profit << endl;
    return 0;
};