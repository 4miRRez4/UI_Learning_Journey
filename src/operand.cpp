#ifndef OPERANDS_CPP
#define OPERANDS_CPP

#include "../include/operand.h"
#include "operand.h"

Operand::Operand (double val, OperandType t) : value(val), type(t){}

OperandType Operand::getType() { return this->type;}



#endif