#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "operand.h"
#include "variable_operand.h"
#include "special_operand.h"
#include "operator.h"
#include "binary_operator.h"
#include "unary_operator.h"
#include "custom_operator.h"
#include "stack.h"
#include "queue.h"
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

const int MAX_OPERANDS = 26;

class Calculator{
private:
    bool AdvancedMode;
    bool BitwiseMode;
    VariableOperand operands[MAX_OPERANDS];
    unordered_map<string, Operator*> operators;
    unordered_map<string, SpecialOperand*> specialOperands;
    string history;    

    bool isNumber(const string part);
    bool isOperand(const string part);
    bool isOperator(const string part);
    int getSymbolPriority(const string part);

public:

    Calculator();
    ~Calculator();

    string getVariableExpr(char name) const;
    double getVariableValue(char name) const;
    string getHistory() const;
    bool isAdvanced() const;

    void goAdvanced();
    void goBitwise(bool enable);
    void initializeVar(char name, string expr);
    void computeAndSetVariableValue(char name);
    void addOperator(Operator* newOp);
    void addCustomOperator(string equation, int priority);
    void addSpecialOperand(SpecialOperand* newOp);
    void addEssentialOperators();
    void addBitwiseOperators();
    void addSpecialOperands();

    vector<string> splitExpr(const string infixExpr);
    vector<string> infixToPostfix(const vector<string> exprParts);
    string postfixToInfix(const vector<string> parts);
    double computePostfix(char varName, vector<string> postfix);

    double computeExpr(char varName, const vector<string> parts);
    void computeAllVariables();
    void printAllVar() const;
};


#endif 
