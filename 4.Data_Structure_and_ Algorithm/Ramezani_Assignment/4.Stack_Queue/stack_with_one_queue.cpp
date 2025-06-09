#include <iostream>
#include <queue>
using namespace std;

class stack_with_queue{
private:
    queue<int> s;
public:
    void push(int val){
        s.push(val);
        for(int i=0; i<s.size()-1; i++){
            s.push(s.front());
            s.pop();
        }
    }

    void pop(){
        if(s.size() != 0)
            s.pop();
    }

    int top(){
        return (s.size() == 0) ? -1:s.front();
    }
};