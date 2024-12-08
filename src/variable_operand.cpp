#include "variable_operand.h"


VariableOperand::VariableOperand()
                    : Operand(OperandType::Variable), name('a'), expression(""), initialized(false), numOfDependencies(0) {}


VariableOperand::VariableOperand(const char n, const std::string expr, const int numOfDep) 
                    : Operand(OperandType::Variable), name(n), expression(expr), initialized(false), numOfDependencies(numOfDep) {}

double VariableOperand::getValue() const {
    return this->Operand::value;
}

char VariableOperand::getName() const{
    if(!initialized)
        throw std::runtime_error("Variable" + std::to_string(name) + "isn't initialized");
    return this->name;
}

string VariableOperand::getExpr() const{
    return this->expression;
}

int VariableOperand::getNumOfDependencies() const{
    return numOfDependencies;
}

vector<char> VariableOperand::getDependents(){
    return this->dependents;
}

bool VariableOperand::isInitialized() const{
    return initialized;
}

void VariableOperand::setValue(const double val){
    this->Operand::value = val;
}

void VariableOperand::initialize(){
    this->initialized = true;
}

void VariableOperand::setExpr(string expr){
    this->expression = expr;
}

void VariableOperand::addDependent(char dependent){
    dependents.push_back(dependent);
}

void VariableOperand::incrementNumOfDependencies(){
    numOfDependencies++;
}

void VariableOperand::decrementNumOfDependencies(){
    if(numOfDependencies > 0)
        numOfDependencies--;
}

