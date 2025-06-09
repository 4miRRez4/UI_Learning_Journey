#include <iostream>
using namespace std;

const int MAX_SIZE = 20000;

struct Node{
    int val;
    int numOfChildren;
    Node* father;
    Node* children[MAX_SIZE];

    Node(int v): val(v), numOfChildren(0), father(nullptr){};
    void add_child(Node* child){
        children[numOfChildren] = child;
        numOfChildren++;
    }
};

int main(){
    int n, m; cin >> n >> m;
    Node* all_nodes[n] = {};
    for(int i=0; i<n; i++){
        Node* newNode = new Node(i);
        all_nodes[i] = newNode;
    }

    int a, b;
    for(int i=0; i<m; i++){
        cin >> a >> b;
        all_nodes[a]->add_child(all_nodes[b]);
        all_nodes[b]->father = all_nodes[a];
    }

    int p1, p2; cin >> p1 >> p2;
    Node* pacient = all_nodes[p2];
    bool is = false;
    while(pacient->father){
        if(pacient->father->val == p1){
            cout << "Yes" << endl;
            is = true;
            break;
        }
        pacient = pacient->father;
    }
    if(is == false)
        cout << "No" << endl;

    return 0;
}