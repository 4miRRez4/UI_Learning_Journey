#include <iostream>
#include <vector>
using namespace std;

const int MAX_SIZE = 101;
class Queue{
public:
    int q[MAX_SIZE];
    int front;
    int back;
    int size;

    Queue(): front(0), back(0), size(0){}

    void enqueue(int val){
        q[back] = val;
        back = (back+1) % MAX_SIZE;
        size++;
    }

    int dequeue(){
        int tmp = q[front];
        front = (front+1) % MAX_SIZE;
        size--;
        return tmp;
    }

    int Front(){ return q[front];}

    int Size(){ return size;}
};

int min_distance_bfs(vector<int> neighbors[], int a, int b){
    bool visited[MAX_SIZE] = {};
    int dist[MAX_SIZE];

    Queue to_see;
    to_see.enqueue(a);
    visited[a]=true;
    dist[a]=0;

    while(to_see.Size() != 0){
        int node = to_see.dequeue();

        for(int i =0; i<neighbors[node].size(); i++){
            int neigh = neighbors[node][i];
            if(!visited[neigh]){
                to_see.enqueue(neigh);
                visited[neigh] = true;
                dist[neigh] = dist[node]+1;
            }
            if(neigh == b)
                return dist[neigh];
        }
    }
    return 0;
}

int main(){
    int n, q; cin >> n >> q;
    vector<int> neighbors[MAX_SIZE];
    int a, b;
    for(int i=0; i<n-1; i++){
        cin >> a >> b;
        neighbors[a].push_back(b);
        neighbors[b].push_back(a);
    }

    while(q--){
        cin >> a >> b;
        cout << min_distance_bfs(neighbors, a, b) << endl;
    }




}

