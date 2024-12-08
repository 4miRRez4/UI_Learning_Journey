#include "unary_operator.h"

UnaryOperator::UnaryOperator(const string s, const int p, double (*func)(double))
                            : Operator(s, OperatorType::Unary, p), unaryFuncPtr(func) {};

double UnaryOperator::apply(double operand1, double operand2) const {
    (void)operand2;
    return unaryFuncPtr(operand1);
}