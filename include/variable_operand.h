#ifndef VARIABLE_OPERAND_H
#define VARIABLE_OPERAND_H

#include "operand.h"
#include <string>
#include <vector>
using namespace std;

class VariableOperand : public Operand{
private:
    char name;
    string expression;
    bool initialized;


    vector<char> dependents;
    int numOfDependencies;

public:
    VariableOperand();
    VariableOperand(const char n, const std::string expr="", const int numOfDep=0);

    double getValue() const override;
    char getName() const;
    bool isInitialized() const;
    int getNumOfDependencies() const;
    vector<char> getDependents();
    string getExpr() const;

    void initialize();
    void setValue(double val);
    void setExpr(string expr);
    void addDependent(char dependent);
    void incrementNumOfDependencies();
    void decrementNumOfDependencies();
    
};

#endif 