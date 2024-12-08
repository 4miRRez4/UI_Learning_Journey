#include "variable_operand.h"


VariableOperand::VariableOperand()
                                : Operand(OperandType::Variable), name('a'), initialized(false) {}

VariableOperand::VariableOperand(const char n) 
                                : Operand(OperandType::Variable), name(n), initialized(false) {}

double VariableOperand::getValue() const {
    return this->Operand::value;
}

char VariableOperand::getName() const{
    if(!initialized)
        throw std::runtime_error("Variable" + std::to_string(name) + "isn't initialized");
    return this->name;
}

bool VariableOperand::isInitialized() const{
    return initialized;
}

void VariableOperand::setValue(const double val){
    this->Operand::value = val;
    initialized = true;
}
