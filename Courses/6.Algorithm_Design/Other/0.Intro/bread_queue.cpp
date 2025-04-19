#include <iostream>
#include <set>
#include <queue>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q, k; cin >> q >> k;

    queue<int> queues[k+1];
    set<pair<int, int>, greater<pair<int, int>>> head_of_queues;

    while(q--){
        char op; cin >> op;

        switch(op){
            case '+':{
                int patience, queue; cin >> patience >> queue;

                if(queues[queue].empty()){
                    head_of_queues.insert({patience, queue});
                }
                queues[queue].push(patience);
                
                break;
            }
            case '?':{
                if(head_of_queues.empty()){
                    cout << "all empty" << endl;
                    continue;
                }

                pair<int, int> min_patience = *head_of_queues.begin();
                cout << min_patience.first << endl;

                head_of_queues.erase(head_of_queues.begin());
                queues[min_patience.second].pop();

                if(!queues[min_patience.second].empty()){
                    head_of_queues.insert({queues[min_patience.second].front(), min_patience.second});
                }
                break;
            }
        }
    }

    return 0;
}