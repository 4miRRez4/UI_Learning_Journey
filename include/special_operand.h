#ifndef SPECIAL_OPERAND_H
#define SPECIAL_OPERAND_H

#include "operand.h"

class SpecialOperand : public Operand{
private:
    std::string name;

public:
    SpecialOperand(const std::string n);

    double getValue() const override;
    std::string getName() const;    
};

#endif