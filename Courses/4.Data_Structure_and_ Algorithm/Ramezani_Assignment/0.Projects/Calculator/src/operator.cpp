#include "operator.h"

Operator::Operator(const string s, const OperatorType t, const int p, const int numOfPara) 
                                    : symbol(s), type(t), priority(p), numOfParameters(numOfPara) {};
                                

string Operator::getSymbol() const{
    return this->symbol;
}

OperatorType Operator::getType() const{
    return this->type;
}

int Operator::getPriority() const{
    return this->priority;
}

int Operator::getNumOfPara() const{
    return this->numOfParameters;
}


Operator::~Operator(){}