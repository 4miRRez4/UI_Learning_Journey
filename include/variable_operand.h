#ifndef VARIABLE_OPERAND_H
#define VARIABLE_OPERAND_H

#include "operand.h"
#include <stdexcept>

class VariableOperand : public Operand{
private:
    char name;
    bool initialized;

public:
    VariableOperand(const double val, const char n);

    double getValue() const override;
    char getName() const;

    void setValue(double val);
};

#endif 