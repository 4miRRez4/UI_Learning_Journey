#include "binary_operator.h"

BinaryOperator::BinaryOperator(const string s, const int p, double (*func)(double, double))
                            : Operator(s, OperatorType::Binary, p), binFuncPtr(func) {};

double BinaryOperator::apply(double operand1, double operand2) const {
    return binFuncPtr(operand1, operand2);
}
