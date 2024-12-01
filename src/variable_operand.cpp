#ifndef VARIABLE_OPERAND_CPP
#define VARIABLE_OPERAND_CPP

#include "../include/variable_operand.h"

VariableOperand::VariableOperand(const double val, const char n) 
                                : Operand(val, OperandType::Variable), name(n), initialized(false) {}

double VariableOperand::getValue() const {
    return this->Operand::value;
}

char VariableOperand::getName() const{
    if(!initialized)
        throw std::runtime_error("Variable" + std::to_string(name) + "isn't initialized");
    return this->name;
}

void VariableOperand::setValue(const double val){
    this->Operand::value = val;
    initialized = true;
}

#endif 