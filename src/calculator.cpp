#include "calculator.h"
#include <math.h>
#include <charconv>



Calculator::Calculator() {
    for(int i=0; i<MAX_OPERANDS; i++)
        operands[i] = VariableOperand('A' + i);

    //add essential operators
    addOperator(new BinaryOperator("+", 1, [](double a, double b) { return a+b; }));
    addOperator(new BinaryOperator("-", 1, [](double a, double b) { return a-b; }));
    addOperator(new BinaryOperator("*", 2, [](double a, double b) { return a*b; }));
    addOperator(new BinaryOperator("/", 2, [](double a, double b) {
        if (b == 0) throw runtime_error("Division by zero!");
        return a / b;
    }));
    addOperator(new BinaryOperator("^", 3, [](double a, double b) { return pow(a, b); }));
    addOperator(new UnaryOperator("!", 4, [](double a) {
        if(a < 0) throw runtime_error("Factoriel of negative number!");

        double fact = 1;    
        for(int n=1; n<=static_cast<int>(a); n++) fact *= n;

        return fact;        
    }));
}

void Calculator::addOperator(Operator* newOp){
    if(operators.count(newOp->getSymbol())){
        throw runtime_error("Operator already exists: " + newOp->getSymbol());
    }
    operators[newOp->getSymbol()] = newOp;
}

vector<string> Calculator::splitExpr(const string infixExpr){
    vector<string> parts;
    string part = "";
    for(char ch: infixExpr){
        if(ch == ' ')
            continue;

        if((ch >= '0' && ch <= '9') || ch == '.'){
            part += ch;
        }
        else{
            if(part != ""){
                parts.push_back(part);
                part = "";
            }

            //negative number
            if(ch == '-' && (parts.empty() || parts.back() == "(" || isOperator(parts.back())))
                part += ch;
            else
                parts.push_back(string(1,toupper(ch)));
        }
    }

    if(part != "")
        parts.push_back(part);

    return parts;
}

bool Calculator::isNumber(const string part){
    double val;
    auto result = from_chars(part.data(), part.data() + part.size(), val);
    return result.ec == errc();
}

bool Calculator::isOperand(const string part){
    if(part.size() == 1 && (part[0] >= 'A' && part[0] <= 'Z')){
        return true;
    }
    return !part.empty() && isNumber(part);
}

bool Calculator::isOperator(const string part){
    return operators.count(part);
}

bool Calculator::hasOperator(const string symbol){
    return operators.find(symbol) != operators.end();
}

int Calculator::getSymbolPriority(const string part){
    if(!hasOperator(part)) throw runtime_error("Unknown operator: " + part);
    return operators.at(part)->getPriority();
}

vector<string> Calculator::infixToPostfix(const vector<string> exprParts){
    Stack<string> operatorStack;
    vector<string> postfix(exprParts.size());
    int postfix_ind = 0;

    for(string part: exprParts){
        if(isOperand(part)){
            postfix[postfix_ind++] = part;
        }
        else if(isOperator(part)){
            while(!operatorStack.isEmpty() && operatorStack.Top() != "(" && getSymbolPriority(operatorStack.Top()) > getSymbolPriority(part)){
                postfix[postfix_ind++] = operatorStack.Top();
                operatorStack.pop();
            }
            operatorStack.push(part);
        }
        else if(part == "(")
            operatorStack.push(part);
        else if(part == ")"){
            while(!operatorStack.isEmpty() && operatorStack.Top() != "("){
                postfix[postfix_ind++] = operatorStack.Top();
                operatorStack.pop();
            }
            operatorStack.pop(); //Pop the "("
        }
        else
            throw runtime_error("Invalid part: " + part);
    }

    while(!operatorStack.isEmpty()){
        if(operatorStack.Top() == "(")
            throw runtime_error("Mismatch paranthesis");
            
        postfix[postfix_ind++] = operatorStack.Top();
        operatorStack.pop();
    }

    return postfix;
}

double Calculator::computePostfix(const vector<string> postfix){
    Stack<double> operandStack;

    for(string part: postfix){
        if(isOperand(part)){
            if(isNumber(part))
                operandStack.push(stod(part));
            else if(part[0] >= 'A' && part[0] <= 'Z'){
                int ind = part[0] - 'A';
                if(!operands[ind].isInitialized())
                    throw runtime_error("Uninitialized variable: " + part[0]);
                
                operandStack.push(operands[ind].getValue());
            }

        }
        else if(isOperator(part)){
            Operator* operatorPtr = operators.at(part);
            double result;
            if(operatorPtr->getType() == OperatorType::Binary){
                if(operandStack.Size() < 2)
                    throw runtime_error("Not enough operands for binary operator: " + part);

                double operand2 = operandStack.Top();
                operandStack.pop();
                double operand1 = operandStack.Top();
                operandStack.pop();

                result = operatorPtr->apply(operand1, operand2);
                
            }else if(operatorPtr->getType() == OperatorType::Unary){
                if(operandStack.isEmpty())
                    throw runtime_error("Not enough operands for unary operator: " + part);
                    
                double operand1 = operandStack.Top();
                operandStack.pop();

                result = operatorPtr->apply(operand1);

            }else
                throw runtime_error("Unsupported operator: " + part);

            operandStack.push(result);
        }
    }

    if (operandStack.Size() > 1) {
        throw std::runtime_error("Error in computePostfix: stack size is incorrect");
    }

    return operandStack.Top();
}

void Calculator::setVariableValue(string name, double value){
    if(name.size() == 1 && name >= "A" && name <= "Z")
        operands[name[0] - 'A'].setValue(value);
    else
        throw runtime_error("Invalid variable name: " + name);
}

double Calculator::getVariableValue(string name) const{
    if(name.size() == 1 && name >= "A" && name <= "Z")
        return operands[name[0] - 'A'].getValue();
        
    throw runtime_error("Invalid variable name: " + name);
}

double Calculator::computeExpr(const string infixExpr){
    vector<string> parts = splitExpr(infixExpr);
    vector<string> postfix = infixToPostfix(parts);
    return computePostfix(postfix);
}


void Calculator::computeAllVariables(){
    Queue<char> toCompute;

    //Add independent variables
    for(int i=0; i<MAX_OPERANDS; i++){
        if(operands[i].isInitialized() && operands[i].getNumOfDependencies() == 0)
            toCompute.enqueue('A' + i);
    }

    while(!toCompute.isEmpty()){
        VariableOperand* frontVar = &operands[toCompute.Front() - 'A'];
        toCompute.dequeue();

        frontVar->setValue(computeExpr(frontVar->getExpr()));

        for(char dependent: frontVar->getDependents()){
            operands[dependent - 'A'].decrementNumOfDependencies();
            if(operands[dependent - 'A'].getNumOfDependencies() == 0)
                toCompute.enqueue(dependent);
        }
    }

    //check for circular dependency
    for(int i=0; i<MAX_OPERANDS; i++)
        if(operands[i].getNumOfDependencies() != 0)
            throw runtime_error("Circular dependency");
}

Calculator::~Calculator(){
    for(auto& pair: operators)
        delete pair.second;
}


