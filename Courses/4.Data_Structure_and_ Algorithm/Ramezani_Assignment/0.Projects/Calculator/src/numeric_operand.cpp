#include "numeric_operand.h"

NumericOperand::NumericOperand()
                            : Operand(OperandType::Number) {}

double NumericOperand::getValue() const { 
    return this->Operand::value;
}

