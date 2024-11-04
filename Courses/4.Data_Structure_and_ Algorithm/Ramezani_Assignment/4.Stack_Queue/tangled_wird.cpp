#include <iostream>
using namespace std;

class Stack{
public:
    char s[350000];
    int top_ind;
    Stack():top_ind(-1){};
    void push(char c){
        top_ind++;
        s[top_ind] = c;
    }

    void pop(){
        if(top_ind >= 0)
            top_ind--;   
    }

    char top(){
        return (top_ind >= 0) ? s[top_ind]:' ';
    }

    bool empty(){
        return (top_ind == -1);
    }
};

int main(){
    Stack s;
    string wires; cin >> wires;
    s.push(wires[0]);
    int l = wires.length();
    for(int i=1; i<l; i++){
        if(s.top() == wires[i])
            s.pop();
        else
            s.push(wires[i]);
    }

    if(s.empty())
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}