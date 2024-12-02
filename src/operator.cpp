#ifndef OPERATOR_CPP
#define OPERATOR_CPP

#include "../include/operator.h"

Operator::Operator(const char s, const OperatorType t, const int p) 
                                    : symbol(s), type(t), priority(p) {};
                                

char Operator::getSymbol() const{
    return this->symbol;
}

OperatorType Operator::getType() const{
    return this->type;
}

int Operator::getPriority() const{
    return this->priority;
}

#endif 

