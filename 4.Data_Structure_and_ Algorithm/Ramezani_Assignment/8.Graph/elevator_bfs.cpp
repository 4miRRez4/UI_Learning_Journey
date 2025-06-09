#include <iostream>
#include <queue>
using namespace std;


int main(){
    int f, s, g, u, d; 
    cin >> f >> s >> g >> u >> d;

    if(s == g){
        cout << 0 << endl;
        return 0;
    }

    
    //BFS
    bool visited[f+1] = {};

    queue<pair<int ,int>> q; // floor, numOfPresses

    q.push({s, 0});
    visited[s] = true;

    while(!q.empty()){
        int curr_floor = q.front().first;
        int numOfPresses = q.front().second;
        q.pop();

        //up button
        if(curr_floor + u < f+1 && !visited[curr_floor + u]){
            if(curr_floor + u == g){
                cout << numOfPresses+1 << endl;
                return 0;
            }
            q.push({curr_floor + u, numOfPresses + 1});
            visited[curr_floor + u] = true;
        }

        //down button 
        if (curr_floor - d >= 0 && !visited[curr_floor - d]) {
            if (curr_floor - d == g) {
                cout << numOfPresses+1 << endl;
                return 0;
            }
            q.push({curr_floor - d, numOfPresses + 1});
            visited[curr_floor - d] = true;
        }
    }
    
    cout << "use the stairs" << endl;

    return 0;
}