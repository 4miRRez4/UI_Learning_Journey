#ifndef OPERANDS_H
#define OPERANDS_H

#include <string>

enum OperandType{ Number, Variable, Special};

class Operand{
protected:
    double value;
    OperandType type;

public:
    Operand(const double value, const OperandType type);

    OperandType getType();

    virtual double getValue() const = 0;
};

#endif