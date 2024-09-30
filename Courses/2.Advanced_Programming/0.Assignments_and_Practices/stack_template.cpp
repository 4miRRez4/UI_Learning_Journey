#include <iostream>
using namespace std;

class size_problem{};
template<typename T>
class Stack{
    private:
    T arr[5];
    int topInd;
    public:
    Stack() : topInd(-1) {} 
    void push(const T& newElement);
    void pop();
    T& top();
    bool isEmpty();
    bool isFull();
    int size();
    void printStack();
};
template <typename T>
void Stack<T>::push(const T& newElement){
    if(topInd >= 4){
        cout << "stack is full!!!" << endl;
        return;
    }
    arr[++topInd] = newElement;
}
template <typename T>
void Stack<T>::pop(){
    if(topInd < 0){
        cout << "stack is emply!!!" << endl;
        return;
    }
    --topInd;
}
template <typename T>
T& Stack<T>::top(){
    if(topInd < 0){
        cout << "stack is empty!!!" << endl;
        throw size_problem();
    }
    return arr[topInd];
}
template <typename T>
bool Stack<T>::isEmpty(){
    return topInd < 0;
}
template <typename T>
bool Stack<T>::isFull(){
    return topInd >= 4;
}
template <typename T>
int Stack<T>::size(){
    return topInd+1;
}
template <typename T>
void Stack<T>::printStack(){
    for(int i=0; i<=topInd; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main(){
    Stack<int> myStack;
    myStack.push(1);
    myStack.push(2);
    myStack.printStack();
    try{
        cout << myStack.top() << endl;
    }catch(size_problem sp){
        cout << "consider size. " << endl;
    }
    myStack.pop();
    cout << myStack.size() << endl;
    cout << myStack.isEmpty() << endl;
    cout << myStack.isFull() << endl;

    return 0;
}