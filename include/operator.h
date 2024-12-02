#ifndef OPERATOR_H
#define OPERATOR_H

enum OperatorType { Binary, Unary, Paranthesis};

class Operator{
protected:
    char symbol;
    OperatorType type;
    int priority;

public:
    Operator(const char s, const OperatorType t, const int p);

    char getSymbol() const;
    OperatorType getType() const;
    int getPriority() const;

    virtual double apply(double operand1, double operand2 = 0) const = 0;
};

#endif