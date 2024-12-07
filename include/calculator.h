#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "variable_operand.h"
#include "operator.h"
#include "binary_operator.h"
#include "unary_operator.h"
#include "stack.h"
#include <unordered_map>
#include <vector>
using namespace std;

const int MAX_OPERANDS = 26;

class Calculator{
private:
    VariableOperand operands[MAX_OPERANDS];
    unordered_map<string, Operator*> operators;

    bool isNumber(const string part);
    bool isOperand(const string part);
    bool isOperator(const string part);
    bool hasOperator(const string symbol);
    int getSymbolPriority(const string part);

    vector<string> splitExpr(const string infixExpr);
    vector<string> infixToPostfix(const vector<string> exprParts);
    double computePostfix(const vector<string> postfix);
public:
    Calculator();
    ~Calculator();

    void setVariableValue(string name, double value);
    double getVariableValue(string name) const;

    void addOperator(Operator* newOp);
    double computeExpr(const string infixExpr);
};


#endif 
