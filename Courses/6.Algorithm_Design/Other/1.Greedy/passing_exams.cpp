#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main(){
    int N; cin >> N;
    int D[N], T[N];
    for(int i=0; i<N; i++){
        cin >> D[N];
    }
    for(int i=0; i<N; i++){
        cin >> T[N];
    }

    vector<pair<int, int>> exams;
    for(int i=0; i<N; i++)
        exams.push_back({D[i], T[i]});

    sort(exams.begin(), exams.end());
    priority_queue<int> pq;

    int passed_cnt = 0;
    int curr_day =0, free_days = 0;
    for(pair<int, int> &exam : exams){
        int d = exam.first;
        int t = exam.second;

        free_days += d - curr_day;
        curr_day = d;

        if(free_days < t && !pq.empty() && pq.top() > t){
            free_days += pq.top();
            passed_cnt--;
            pq.pop();
        }

        if(free_days >= t){
            free_days -= t;
            passed_cnt++;
            pq.push(t);
        }
    }
    cout << passed_cnt << endl;


    return 0;
}