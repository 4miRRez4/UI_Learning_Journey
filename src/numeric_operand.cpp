#ifndef NUMERIC_OPERAND_CPP
#define NUMERIC_OPERAND_CPP

#include "../include/numeric_operand.h"

NumericOperand::NumericOperand(const double val)
                            : Operand(val, OperandType::Number) {}

double NumericOperand::getValue() const { 
    return this->Operand::value;
}

#endif 