#include "operator.h"

Operator::Operator(const string s, const OperatorType t, const int p) 
                                    : symbol(s), type(t), priority(p) {};
                                

string Operator::getSymbol() const{
    return this->symbol;
}

OperatorType Operator::getType() const{
    return this->type;
}

int Operator::getPriority() const{
    return this->priority;
}


Operator::~Operator(){}