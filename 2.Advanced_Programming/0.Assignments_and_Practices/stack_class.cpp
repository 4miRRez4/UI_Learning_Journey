#include <iostream>
using namespace std;

class Stack
{
    public:
    Stack() { top = 0;}
    void push();
    void pop();

    private:
    int nums[5];
    int top;
};
void Stack::push()
{
    if(top == 5)
    {
        cout << "stack is full!!! try popping." << endl;
        return;
    }
    cout << "plz enter number you want to push: " << endl;
    int n; cin >> n;
    this->nums[top] = n;
    top++;
}

void Stack::pop()
{
    if(top == 0)
    {
        cout << "Stack is empty!!! try pushing." << endl;
        return;
    }
    top--;
    cout << this->nums[top] << endl;
    this->nums[top] =0;

}

int main()
{
    Stack myStk;
    myStk.push();
    myStk.pop();

    return 0;
}