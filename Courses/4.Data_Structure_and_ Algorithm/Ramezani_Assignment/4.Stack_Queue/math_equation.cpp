#include <iostream>
using namespace std;

template<typename T>
struct Node{
    T data;
    Node* next;
    Node(T d): data(d), next(nullptr){}
};

template<typename T>
class Stack{
public:
    Node<T>* top;

    Stack(): top(nullptr){};
    void push(T val){
        Node<T>* newNode = new Node(val);
        if(top == nullptr)
            top = newNode;
        else{
            newNode->next = top;
            top = newNode;
        }
    }

    void pop(){
        Node<T>* tmp = top;
        top = top->next;
        delete tmp;
    }

    T Top(){
        return top->data;
    }
};

int main(){
    string equation; cin >> equation;

    Stack<int>* s = new Stack<int>();
    for(int i=0; i<equation.length(); i++){
        if(equation[i] <= '9' and equation[i] >= '0')
            s->push(equation[i]-'0');
        else{
            int operand2 = s->Top();
            s->pop();
            int operand1 = s->Top();
            s->pop();
            switch(equation[i]){
                case '+':
                    s->push(operand1 + operand2);
                    break;
                case '-':
                    s->push(operand1 - operand2);
                    break;
                case '*':
                    s->push(operand1 * operand2);
                    break;
                case '/':
                    s->push(operand1 / operand2);
                    break;
            }
        }
    }
    cout << s->Top() << endl;

    return 0;
}