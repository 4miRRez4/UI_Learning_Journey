#ifndef BINARY_OPERATOR_CPP
#define BINARY_OPERATOR_CPP

#include "../include/binary_operator.h"

BinaryOperator::BinaryOperator(const char s, const int p, double (*func)(double, double))
                            : Operator(s, OperatorType::Binary, p), binFuncPtr(func) {};

double BinaryOperator::apply(double operand1, double operand2 = 0) const {
    return binFuncPtr(operand1, operand2);
}

#endif 