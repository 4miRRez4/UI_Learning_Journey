#include <iostream>
#include <queue>
using namespace std;

int main() {
    int q, k, w, done = 0; cin >> q;

    priority_queue<int, vector<int>, greater<int>> deadlines;

    for (int day=1; day<=q; day++) {
        cin >> k;
        for (int j = 0; j < k; j++) {
            cin >> w;
            deadlines.push(w + day - 1);
        }

        while (!deadlines.empty() && deadlines.top() < day) {
            deadlines.pop();
        }

        if(!deadlines.empty()){
            deadlines.pop();
            done++;
        }
    }

    cout << done << endl;

    return 0;
}