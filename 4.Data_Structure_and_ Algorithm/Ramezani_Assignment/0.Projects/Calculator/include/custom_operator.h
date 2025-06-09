#ifndef CUSTOM_OPERATOR_H
#define CUSTOM_OPERATOR_H

#include "operator.h"
#include "calculator.h"

class CustomOperator : public Operator{
private:
    vector<string> functionality_postfix;

public:
    CustomOperator(const string s, const int p, const vector<string> func, int numOfPara);

    double apply(double operand1, double operand2=0) const override;
};

#endif 