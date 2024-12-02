#ifndef BINARY_OPERATOR_H
#define BINARY_OPERATOR_H

#include "operator.h"

class BinaryOperator : public Operator{
private:
    double (*binFuncPtr)(double, double);

public:
    BinaryOperator(const char s, const int p, double (*func)(double, double));

    double apply(double operand1, double operand2 = 0) const override;
};

#endif 