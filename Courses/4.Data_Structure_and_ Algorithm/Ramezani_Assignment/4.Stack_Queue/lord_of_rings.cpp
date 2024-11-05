#include <iostream>
#include <queue>
using namespace std;

int main(){
    queue<int> q;
    int n; cin >> n;
    for(int i=1; i<=n; i++){
        q.push(i);
    }

    int k; cin >> k;
    while(q.size() != 1){
        for(int i=0; i<k-1; i++){
            int tmp = q.front();
            q.pop();
            q.push(tmp);            
        }
        q.pop();
    }
    cout << q.front() << endl;

    return 0;
}