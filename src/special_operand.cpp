#ifndef SPECIAL_OPERAND_CPP
#define SPECIAL_OPERAND_CPP

#include "../include/special_operand.h"

SpecialOperand::SpecialOperand(const std::string n, const double val): Operand(val, OperandType::Special), name(n) {}

double SpecialOperand::getValue() const {
    return this->Operand::value;
}

std::string SpecialOperand::getName() const{
    return this->name;
}

#endif