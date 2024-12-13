#include "special_operand.h"

SpecialOperand::SpecialOperand(const std::string n, const double val)
: Operand(OperandType::Special), name(n) {
    setValue(val);
}

double SpecialOperand::getValue() const {
    return this->Operand::value;
}

std::string SpecialOperand::getName() const{
    return this->name;
}

void SpecialOperand::setValue(double val){
    Operand::value = val;
}
