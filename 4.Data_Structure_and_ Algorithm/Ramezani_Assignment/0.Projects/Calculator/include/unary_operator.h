#ifndef UNARY_OPERATOR_H
#define UNARY_OPERATOR_H

#include "operator.h"

class UnaryOperator : public Operator{
private:
    double (*unaryFuncPtr) (double);

public:
    UnaryOperator(const string s, const int p, double (*func)(double));

    double apply(double operand1, double operand2=0) const override;
};

#endif