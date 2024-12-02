#ifndef UNARY_OPERATOR_CPP
#define UNARY_OPERATOR_CPP

#include "../include/unary_operator.h"

UnaryOperator::UnaryOperator(const char s, const OperatorType t, const int p, double (*func)(double))
                            : Operator(s, t, p), unaryFuncPtr(func) {};

double UnaryOperator::apply(double operand1, double operand2=0) const {
    return unaryFuncPtr(operand1);
}

#endif