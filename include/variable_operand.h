#ifndef VARIABLE_OPERAND_H
#define VARIABLE_OPERAND_H

#include "operand.h"

class VariableOperand : public Operand{
private:
    char name;
    bool initialized;

public:
    VariableOperand();
    VariableOperand(const char n);

    double getValue() const override;
    char getName() const;
    bool isInitialized() const;

    void setValue(double val);
};

#endif 