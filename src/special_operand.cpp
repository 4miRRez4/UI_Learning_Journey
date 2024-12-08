#include "special_operand.h"

SpecialOperand::SpecialOperand(const std::string n): Operand(OperandType::Special), name(n) {}

double SpecialOperand::getValue() const {
    return this->Operand::value;
}

std::string SpecialOperand::getName() const{
    return this->name;
}
