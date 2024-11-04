#include <iostream>
#include <stack>
using namespace std;

int main(){
    string equation; cin >> equation;

    stack<int> s;
    for(int i=0; i<equation.length(); i++){
        if(equation[i] <= '9' and equation[i] >= '0')
            s.push(equation[i]-'0');
        else{
            int operand2 = s.top();
            s.pop();
            int operand1 = s.top();
            s.pop();
            switch(equation[i]){
                case '+':
                    s.push(operand1 + operand2);
                    break;
                case '-':
                    s.push(operand1 - operand2);
                    break;
                case '*':
                    s.push(operand1 * operand2);
                    break;
                case '/':
                    s.push(operand1 / operand2);
                    break;
            }
        }
    }
    cout << s.top() << endl;

    return 0;
}