#include <iostream>
#include <stack>
using namespace std;

int precedence(char oper){ 
    if(oper == '+' || oper == '-') return 1;
    if(oper == '*' || oper == '/') return 2;
    return 0;
}

int main(){
    stack<char> operator_stack;

    string infix; cin >> infix;
    string postfix="";
    for(int i=0; i<infix.length(); i++){
        if(infix[i] >= 'A' && infix[i] <= 'Z')
            postfix += infix[i];
        else if(infix[i] == '(')
            operator_stack.push(infix[i]);
        else if(infix[i] == ')'){
            while(operator_stack.top() != '('){
                postfix += operator_stack.top();
                operator_stack.pop();
            }
            operator_stack.pop();
        }
        else{ //operator
            if(operator_stack.empty() || precedence(infix[i]) > precedence(operator_stack.top()))
                operator_stack.push(infix[i]);
            else{
                while(!operator_stack.empty() && operator_stack.top() != '(' && precedence(operator_stack.top()) >= precedence(infix[i])){
                    postfix += operator_stack.top();
                    operator_stack.pop();
                }
                operator_stack.push(infix[i]);
            }
        }
    }
    while(!operator_stack.empty()){
        postfix += operator_stack.top();
        operator_stack.pop();
    }

    cout << postfix << endl;

    return 0;
}