#include <iostream>
#include <stack>
using namespace std;

class stack_with_queue1{
private:
    stack<int> s1;
    stack<int> s2;
public:
    void enqueue(int val){
        for(int i=0; i<s1.size(); i++){
            s2.push(s1.top());
            s1.pop();
        }
        s2.push(val);
        for(int i=0; i<s2.size(); i++){
            s1.push(s2.top());
            s2.pop();
        }
    }
    int dequeue(){
        if(s1.size() == 0)
            return;
        
        int val = s1.top();
        s1.pop();
        return val;
    }
};

class queue_with_stacks2{
private:
    stack<int> s1;
    stack<int> s2;
public:
    void enqueue(int val){
        s1.push(val);
    }

    int dequeue(){
        if(s1.size() == 0 && s2.size() == 0)
            return -1;

        if(s2.size() == 0)
            for(int i=0; i<s1.size(); i++){
                s2.push(s1.top());
                s1.pop();
            }
        int val = s2.top();
        s2.pop();
        return val;
    }
};
