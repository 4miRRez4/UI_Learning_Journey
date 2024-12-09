#include "calculator.h"
#include <math.h>
#include <charconv>
#include <iostream>
#include <iomanip>


Calculator::Calculator() {
    for(int i=0; i<MAX_OPERANDS; i++)
        operands[i] = VariableOperand('A' + i);

    addEssentialOperators();

    addSpecialOperands();
}

void Calculator::addOperator(Operator* newOp){
    if(operators.count(newOp->getSymbol())){
        throw runtime_error("Operator already exists: " + newOp->getSymbol());
    }
    operators[newOp->getSymbol()] = newOp;
}

void Calculator::addSpecialOperand(SpecialOperand* newOp){
    if(specialOperands.count(newOp->getName())){
        throw runtime_error("Special operand already exists: " + newOp->getName());
    }
    specialOperands[newOp->getName()] = newOp;
}

void Calculator::addEssentialOperators(){
    addOperator(new BinaryOperator("+", 1, [](double a, double b) { return a+b; }));
    addOperator(new BinaryOperator("-", 1, [](double a, double b) { return a-b; }));
    addOperator(new BinaryOperator("*", 2, [](double a, double b) { return a*b; }));

    addOperator(new BinaryOperator("/", 2, [](double a, double b) {
        if (b == 0) throw runtime_error("Arithmatic Error"); //division by zero
        return a / b;
    }));

    addOperator(new BinaryOperator("^", 3, [](double a, double b) { 
        if(a==0 && b<=0)
            throw runtime_error("Arithmatic Error");//0 raised to non-positive power


        if (a < 0 && b != std::floor(b)) { //a is negative and b is fractional        
            double intPart, fracPart;
            fracPart = modf(b, &intPart);
            double divider = 1.0 / abs(fracPart);
            if (floor(divider) == divider && static_cast<int>(divider) % 2 == 1) {
                // Fractional exponent with an odd divider
                return -pow(-a, b);
            } else {
                throw runtime_error("Arithmatic Error"); //negative base raise to fractional even power
            }
        }

        return pow(a,b);
    }));

    addOperator(new UnaryOperator("!", 4, [](double a) {
        if(a < 0) throw runtime_error("Arithmatic Error"); //factoriel of negative number

        double fact = 1;    
        for(int n=1; n<=static_cast<int>(a); n++) fact *= n;

        return fact;        
    }));

}
    
void Calculator::addSpecialOperands(){
    addSpecialOperand(new SpecialOperand("PI", 3.14159));
    addSpecialOperand(new SpecialOperand("EN", 2.71828));
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
        else if (isalpha(ch)) {
            part += toupper(ch);

            // Check if the current part is a special operand
            if (specialOperands.find(part) != specialOperands.end()) {
                parts.push_back(part);
                part = "";
            }
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
    if(part.empty()) 
        return false;

    //variable operand
    if(part.size() == 1 && isalpha(part[0]))
        return true;

    //special operand
    if(specialOperands.find(part) != specialOperands.end())
        return true;

    //numeric operand
    return isNumber(part);
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
            throw runtime_error("Invalid Input");
    }

    while(!operatorStack.isEmpty()){
        if(operatorStack.Top() == "(")
            throw runtime_error("Invalid Format");
            
        postfix[postfix_ind++] = operatorStack.Top();
        operatorStack.pop();
    }

    return postfix;
}

double Calculator::computePostfix(const vector<string> postfix){
    Stack<double> operandStack;

    for(string part: postfix){
        if(isOperand(part)){
            if(isNumber(part)){
                operandStack.push(stod(part));
            }else if(specialOperands.find(part) != specialOperands.end())
                operandStack.push(specialOperands[part]->getValue());
            else if(part.size() == 1 && isalpha(part[0])){
                int ind = part[0] - 'A';
                if(!operands[ind].isInitialized())
                    throw runtime_error("Not Defined Variable");
                
                operandStack.push(operands[ind].getValue());
            }
            else
                throw runtime_error("Invalid Input");
        }
        else if(isOperator(part)){
            Operator* operatorPtr = operators.at(part);
            double result;
            if(operatorPtr->getType() == OperatorType::Binary){
                if(operandStack.Size() < 2) //not enough operand for binary operator
                    throw runtime_error("Invalid Format");

                double operand2 = operandStack.Top();
                operandStack.pop();
                double operand1 = operandStack.Top();
                operandStack.pop();

                result = operatorPtr->apply(operand1, operand2);
                
            }else if(operatorPtr->getType() == OperatorType::Unary){
                if(operandStack.isEmpty()) //not enough operand for unary operator
                    throw runtime_error("Invalid Format");
                    
                double operand1 = operandStack.Top();
                operandStack.pop();

                result = operatorPtr->apply(operand1);

            }else
                throw runtime_error("Invalid Input");

            operandStack.push(result);
        }
    }

    if (operandStack.Size() > 1) {
        throw std::runtime_error("Invalid Input"); //stack size is incorrect
    }

    return operandStack.Top();
}


string Calculator::getVariableExpr(char name) const{
    return operands[name - 'A'].getExpr();
}

double Calculator::getVariableValue(char name) const{
    if(isalpha(name))
        if(operands[name - 'A'].isInitialized())
            return operands[name - 'A'].getValue();
        else
            throw runtime_error("Not Defined Variable");
    else
        throw runtime_error("Invalid Input");
}

void Calculator::setVariableExpr(char name, string expr){
    int varInd = name - 'A';
    //was the variable initialized before?
    if(operands[varInd].isInitialized())
        throw runtime_error("Inconsistency");
    
    //set expression, initialize and update dependencies
    operands[varInd].setExpr(expr);
    operands[varInd].initialize();

    //increment numOfDependencies of dependents of the variable
    vector<string> parts = splitExpr(expr);
    for (string part : parts) {
        if (part.size() == 1 && isalpha(part[0]) && (specialOperands.find(part) == specialOperands.end())) { //variable operand
            int dependencyInd = part[0] - 'A';
            operands[dependencyInd].addDependent(name);
            operands[varInd].incrementNumOfDependencies();
        }
    }
}

void Calculator::computeAndSetVariableValue(char name, string expr){
    if(expr.size() == 0)
        throw runtime_error("Invalid Input");
        
    operands[toupper(name) - 'A'].setValue(computeExpr(expr));
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
        int varInd = toCompute.Front() - 'A';
        VariableOperand* var = &operands[varInd];
        toCompute.dequeue();

        var->setValue(computeExpr(var->getExpr()));

        for(char dependent: var->getDependents()){
            operands[dependent - 'A'].decrementNumOfDependencies();
            if(operands[dependent - 'A'].getNumOfDependencies() == 0)
                toCompute.enqueue(dependent);
        }
    }

    //check for not defined variable
    for(int i=0; i<MAX_OPERANDS; i++)
        if(operands[i].getDependents().size() != 0 && !operands[i].isInitialized())
            throw runtime_error("Not Defined Variable");

    //check for circular dependency
    for(int i=0; i<MAX_OPERANDS; i++)
        if(operands[i].isInitialized() && operands[i].getNumOfDependencies() != 0)
            throw runtime_error("Circular Dependency");
}

void Calculator::printAllVar() const{
    for(int i=0; i<MAX_OPERANDS; i++){
        if(operands[i].isInitialized()){
            char varName = 'A' + i;
            double varVal = operands[i].getValue();

            cout << varName << "=";

            if(floor(varVal) == varVal)
                cout << varVal;
            else
                cout << fixed << setprecision(4) << varVal;

            cout << endl;
        }
    }
}

Calculator::~Calculator(){
    for(auto& pair: operators)
        delete pair.second;
}

