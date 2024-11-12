#include <iostream>
using namespace std;

const int MAX_SIZE = 100;

struct Node{
    int val;
    int depth;
    int numOfChildren;
    Node* father;
    Node* children[MAX_SIZE];

    Node(int v): val(v), numOfChildren(0), father(nullptr), depth(0){};
    void add_child(Node* child){
        children[numOfChildren] = child;
        numOfChildren++;
    }
};

void calculate_depth(Node* node, int depth=0){
    node->depth = depth;
    depth++;
    for(int i=0; i<node->numOfChildren; i++){
        calculate_depth(node->children[i], depth);
    }
}

int min_distance(Node* a, Node* b){
    int d=0;

    int depth_diff = a->depth - b->depth;
    d += abs(depth_diff);
    if(depth_diff > 0)
        for(int i=0; i<abs(depth_diff); i++){
            a = a->father;
        }
    else if(depth_diff < 0)
        for(int i=0; i<abs(depth_diff); i++){
            b = b->father;
        }

    while(a != b){
        d+=2;
        a = a->father;
        b = b->father;
    }

    return d;
}

int main(){
    int n, q; cin >> n >> q;
    Node* all_nodes[MAX_SIZE] = {};
    for(int i=1; i<=n; i++){
        Node* newNode = new Node(i);
        all_nodes[i-1] = newNode;
    }

    int a, b;
    for(int i=0; i<n-1; i++){
        cin >> a >> b;
        all_nodes[a-1]->add_child(all_nodes[b-1]);
        all_nodes[b-1]->father = all_nodes[a-1];
    }

    calculate_depth(all_nodes[0]);

    for(int i=0; i<q; i++){
        cin >> a >> b;
        cout << min_distance(all_nodes[a-1], all_nodes[b-1]) << endl;;
    }
    return 0;
}