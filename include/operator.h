#ifndef OPERATOR_H
#define OPERATOR_H

#include <string>
#include <stdexcept>
using namespace std;

enum OperatorType { Binary, Unary};

class Operator{
protected:
    string symbol;
    OperatorType type;
    int priority;

public:
    Operator(const string s, const OperatorType t, const int p);
    virtual ~Operator();

    string getSymbol() const;
    OperatorType getType() const;
    int getPriority() const;

    virtual double apply(double operand1, double operand2 = 0) const = 0;
};

#endif