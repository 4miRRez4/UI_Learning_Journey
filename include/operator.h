#ifndef OPERATOR_H
#define OPERATOR_H

#include <string>
using namespace std;

enum OperatorType { Binary, Unary, Paranthesis};

class Operator{
protected:
    string symbol;
    OperatorType type;
    int priority;

public:
    Operator(const string s, const OperatorType t, const int p);

    string getSymbol() const;
    OperatorType getType() const;
    int getPriority() const;

    virtual double apply(double operand1, double operand2 = 0) const = 0;
};

#endif