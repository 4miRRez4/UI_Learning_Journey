#ifndef OPERANDS_CPP
#define OPERANDS_CPP

#include "../include/operand.h"
#include "operand.h"

Operand::Operand (OperandType t) : type(t){}

OperandType Operand::getType() { return this->type;}


#endif