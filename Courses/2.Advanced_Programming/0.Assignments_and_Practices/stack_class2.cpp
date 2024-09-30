#include <iostream>
using namespace std;
class Stack{
    public:
    static int objects; 
    Stack(){ top=-1; objects++;}
    ~Stack();

    void push(int x);
    void pop();
    bool isEmpty(){ return (top==-1) ? true:false;}
    bool isFull(){ return (top==4) ? true:false;}
    int count(){ return top+1;}
    int countObjects(){ return objects;}

    private:
    int arr[5];
    int top;   
};
int Stack::objects=0;
Stack::~Stack(){
    top=-1;
    for(int i=0; i<5; i++)
        arr[i] = 0;
    cout << "stack destroyed" << endl;
}
void Stack::pop(){
    if(top == -1)
    {
        cout << "stack is empty!!! try pushing." << endl;
        return;
    }
    cout << "popped this: " << this->arr[top] << endl;
    this->arr[top]=0;
    top--;
}
void Stack::push(int x){
    if(top == 4)
    {
        cout << "stack is full!!! try popping." << endl;
        return;
    }
    arr[++top] = x;
}
int main()
{
    Stack myS;
    myS.push(2);
    myS.push(4);
    myS.push(6);
    myS.pop();
    cout << "number of elements: " << myS.count() << endl;
    cout << ((myS.isEmpty()) ? "it's empty.":"it's not empty.") << endl;
    cout << ((myS.isFull()) ? "it's full." : "it's not full.") << endl;
    cout << "number of objects: " << myS.countObjects() << endl;
    return 0;
}