#include "calculator.h"
#include <math.h>
#include <charconv>
#include <iostream>
#include <iomanip>
#include <sstream>



Calculator::Calculator() {
    for(int i=0; i<MAX_OPERANDS; i++)
        operands[i] = VariableOperand('A' + i);

    addEssentialOperators();

    addSpecialOperands();

    AdvancedMode = false;
    history = "";
}

void Calculator::goAdvanced(){
    AdvancedMode = true;
}

void Calculator::goBitwise(bool enable){
    BitwiseMode = enable;
    if (enable) {
            addBitwiseOperators();
            cout << "Bitwise mode enabled. Only integer inputs." << endl;
        }
        else {
            cout << "Bitwise mode disabled." << endl;
        }
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
        if (b == 0) throw runtime_error("Arithmetic Error"); //division by zero
        return a / b;
    }));

    addOperator(new BinaryOperator("^", 3, [](double a, double b) { 
        if(a==0 && b<=0)
            throw runtime_error("Arithmetic Error");//0 raised to non-positive power


        if (a < 0 && b != std::floor(b)) { //a is negative and b is fractional        
            double intPart, fracPart;
            fracPart = modf(b, &intPart);
            double divider = 1.0 / abs(fracPart);
            if (floor(divider) == divider && static_cast<int>(divider) % 2 == 1) {
                // Fractional exponent with an odd divider
                return -pow(-a, b);
            } else {
                throw runtime_error("Arithmetic Error"); //negative base raise to fractional even power
            }
        }

        return pow(a,b);
    }));

    addOperator(new UnaryOperator("!", 4, [](double a) {
        if(a < 0) throw runtime_error("Arithmetic Error"); //factoriel of negative number

        double fact = 1;    
        for(int n=1; n<=static_cast<int>(a); n++) fact *= n;

        return fact;        
    }));

}

void Calculator::addBitwiseOperators() {
    addOperator(new BinaryOperator("|", 1, [](double a, double b) { return static_cast<double>(static_cast<int>(a) | static_cast<int>(b)); }));
    addOperator(new BinaryOperator("&", 2, [](double a, double b) { return static_cast<double>(static_cast<int>(a) & static_cast<int>(b)); }));
    addOperator(new UnaryOperator("~", 3, [](double a) { return static_cast<double>(~static_cast<int>(a)); }));
}

void Calculator::addCustomOperator(string equation, int priority){
    size_t assignInd = equation.find('=');
    if(assignInd != string::npos && (assignInd == 2 || assignInd == 3)){ //valid positions of =
        string symbol = string(1,equation[1]);
        if(isalpha(symbol[0])) 
                    throw runtime_error("Invalid Input");

        vector<string> postfixExpr = infixToPostfix(splitExpr(equation.substr(assignInd+1)));//functionali_postfix

        addOperator(new CustomOperator(symbol, priority, postfixExpr, assignInd-1));// 1 or 2 numOfParameters

        cout << "Operation defined successfully." << endl;
    }
    else
        throw runtime_error("Invalid Input");
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

        if((ch >= '0' && ch <= '9') || ch == '.'){ //integral and fractional numbers
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
            if(part != ""){//multi character number and character
                parts.push_back(part);
                part = "";
            }

            //negative number
            if(ch == '-' && (parts.empty() || parts.back() == "(" || isOperator(parts.back())))
                part += ch;
            else if(ch == '(' || ch == ')')
                parts.push_back(string(1,ch));
            else{//operator
                if(isOperator(string(1,ch)))
                    parts.push_back(string(1,ch));
                else
                    throw runtime_error("Invalid Input");//unknown operator
            }
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

bool Calculator::isAdvanced() const{
    return this->AdvancedMode;
}

int Calculator::getSymbolPriority(const string part){
    if(!isOperator(part)) throw runtime_error("Invalid Input"); //unknown operator
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

string Calculator::postfixToInfix(const vector<string> parts){
    Stack<string> operandStack;

    for(string part: parts){
        if(part == "") continue;//trash at end of postfix that is place for paranthesis
        
        if(isOperand(part)){
            operandStack.push(part);
        }
        else if(isOperator(part)){
            Operator* operatorPtr = operators.at(part);
            if(static_cast<int> (operandStack.Size()) < operatorPtr->getNumOfPara())//not enough operand for operator
                throw runtime_error("Invalid Format");

            string formated = "";
            if(operatorPtr->getNumOfPara() == 2){ //binary operators
                string operand2 = operandStack.Top();
                operandStack.pop();
                string operand1 = operandStack.Top();
                operandStack.pop();

                formated = "(" + operand1 + operatorPtr->getSymbol() + operand2 + ")";
            }
            else if(operatorPtr->getNumOfPara() == 1){// unary opeators
                string operand1 = operandStack.Top();
                operandStack.pop();

                formated = "(" + operand1 + operatorPtr->getSymbol() + ")";
            }
            else
                throw runtime_error("Invalid Input");

            operandStack.push(formated);
        }
        else
            throw runtime_error("Invalid Input");
    }

    return operandStack.Top();
}

double Calculator::computePostfix(char varName, vector<string> postfix){
    Stack<double> operandStack;

    for(int i=0; i < static_cast<int>(postfix.size()); i++){
        string part = postfix[i];
        if(part == "")  continue; //trash at end of postfix that is place for paranthesis

        int numOfArg = 0;
        if(isOperand(part)){// add its value to stack
            if(isNumber(part)){
                operandStack.push(stod(part));
            }
            else if(specialOperands.find(part) != specialOperands.end()){
                operandStack.push(specialOperands[part]->getValue());
            }
            else if(part.size() == 1 && isalpha(part[0])){
                int ind = part[0] - 'A';
                if(!operands[ind].isInitialized())
                    throw runtime_error("Not Defined Variable");
                
                operandStack.push(operands[ind].getValue());
            }
            else
                throw runtime_error("Invalid Input");
        }
        else if(isOperator(part)){ //handle operators
            Operator* operatorPtr = operators.at(part);
            numOfArg = operatorPtr->getNumOfPara();
            if(static_cast<int> (operandStack.Size()) < numOfArg)//not enough operand for operator
                throw runtime_error("Invalid Format");

            double result;
            if(numOfArg == 2){ //binary operators
                double operand2 = operandStack.Top();
                operandStack.pop();
                double operand1 = operandStack.Top();
                operandStack.pop();

                result = operatorPtr->apply(operand1, operand2);
            }
            else if(numOfArg == 1){// unary opeators
                double operand1 = operandStack.Top();
                operandStack.pop();

                result = operatorPtr->apply(operand1);
            }
            else
                throw runtime_error("Invalid Input");

            operandStack.push(result);

            if(isAdvanced()){
                ostringstream ss; //for converting double to string
                ss << result;
                // update the postfix expression
                postfix.erase(postfix.begin() + i - numOfArg, postfix.begin() + i + 1); // remove operands and operator
                postfix.insert(postfix.begin() + i - numOfArg, ss.str()); // insert the result
                i -= numOfArg; 

                //add to history
                history += string(1,varName) + "=" + postfixToInfix(postfix) + "\n";
            }
        }
    }

    if (operandStack.Size() > 1) {
        throw std::runtime_error("Invalid Input"); //stack size is incorrect
    }
    history += '\n';
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

string Calculator::getHistory() const{
    return this->history;
}

void Calculator::initializeVar(char name, string expr){
    int varInd = name - 'A';
    //was the variable initialized before?
    if(operands[varInd].isInitialized())
        throw runtime_error("Inconsistency");
    
    //set expression, parts, initialize and update dependencies
    operands[varInd].setExpr(expr);
    operands[varInd].initialize();

    //set splited expression
    operands[varInd].setExprParts(splitExpr(expr));

    //increment numOfDependencies of dependents of the variable
    for (string part : operands[varInd].getExprParts()) {
        if (part.size() == 1 && isalpha(part[0]) && (specialOperands.find(part) == specialOperands.end())) { //variable operand
            int dependencyInd = part[0] - 'A';
            operands[dependencyInd].addDependent(name);
            operands[varInd].incrementNumOfDependencies();
        }
    }
}

void Calculator::computeAndSetVariableValue(char name){
    vector<string> expr = operands[toupper(name) - 'A'].getExprParts();

    if(expr.size() != 0)
        throw runtime_error("Invalid Input");//empty expression

    operands[toupper(name) - 'A'].setValue(computeExpr(toupper(name), expr));
}

double Calculator::computeExpr(char varName, const vector<string> parts){
    vector<string> postfix = infixToPostfix(parts);
    return computePostfix(varName, postfix);
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

        var->setValue(computeExpr(var->getName(), var->getExprParts()));

        for(char dependent: var->getDependents()){
            operands[dependent - 'A'].decrementNumOfDependencies();
            if(operands[dependent - 'A'].getNumOfDependencies() == 0) //if operand has no unsolved dependency
                toCompute.enqueue(dependent);
        }
    }

    //check for not defined variable(there are some dependent of var but its not initialized)
    for(int i=0; i<MAX_OPERANDS; i++)
        if(operands[i].getDependents().size() != 0 && !operands[i].isInitialized())
            throw runtime_error("Not Defined Variable");

    //check for circular dependency(var was initialized but still has unsolved dependencies)
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
                cout << fixed << setprecision(0) << varVal;
            else //fractional
                cout << fixed << setprecision(4) << varVal;

            cout << endl;
        }
    }
}

Calculator::~Calculator(){
    for(auto& pair: operators)
        delete pair.second;
}

