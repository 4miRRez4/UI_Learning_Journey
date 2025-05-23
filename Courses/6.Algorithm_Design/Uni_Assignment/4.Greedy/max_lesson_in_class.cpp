/*
We always select the lesson that finishes earliest among the available ones.
This ensures that the remaining time is maximized for scheduling other non-overlapping lessons.
Assume there's an optimal schedule different from the greedy one.
Let’s say the first lesson in the optimal schedule ends later than the first lesson in the greedy schedule.
Then we can replace it with the greedy choice (which ends earlier), allowing more room for future lessons without reducing the total number of lessons.
By repeating this, we can transform the optimal schedule into the greedy schedule.
*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct lesson_time{
    int start;
    int end;
    lesson_time(int s, int e): start(s), end(e) {};
};

int main(){
    int n; cin >> n;

    vector<lesson_time> lessons;
    for(int i=0; i<n; i++){
        int s, e; cin >> s >> e;
        lesson_time new_lesson = lesson_time(s, e);
        lessons.push_back(new_lesson);
    }

    sort(lessons.begin(), lessons.end(), [](lesson_time x, lesson_time y){ return x.end < y.end;});

    vector<lesson_time> non_conflicting_lessons;
    int i=0;
    while(i < n){
        non_conflicting_lessons.push_back(lessons[i]);

        int j = i + 1;
        while(j < n && lessons[j].start < lessons[i].end)
            j += 1;
        
        i = j;
    }

    int len = non_conflicting_lessons.size();
    cout << len << endl;
    for(int i=0; i<len; i++){
        cout << non_conflicting_lessons[i].start << " ";
        cout << non_conflicting_lessons[i].end << endl;
    }

    return 0;
}