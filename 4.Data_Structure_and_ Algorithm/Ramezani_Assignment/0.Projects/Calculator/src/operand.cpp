#include "operand.h"

Operand::Operand (OperandType t) : type(t){}

OperandType Operand::getType() { return this->type;}
