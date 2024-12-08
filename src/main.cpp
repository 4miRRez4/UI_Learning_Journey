#include <iostream>
#include "calculator.h"
using namespace std;

void extractExpression(Calculator& calc, const string equation){
    char varName = toupper(equation[0]);
    if(!isalpha(varName))
        throw runtime_error("Invalid variable name");

    if(equation[1] != '=')
        throw runtime_error("Invalid input format");

    string expr = equation.substr(2, equation.size());
    calc.setVariableExpr(varName, expr);
}

int main() {
    Calculator myCalc;

    int n; cin >> n;
    string equation;
    try{
        for(int i=0; i<n; i++){
            cin >> equation;
            extractExpression(myCalc, equation);
    }
    }catch(const exception& e){
            cout << e.what() << endl;
            return -1;
    }

    myCalc.computeAllVariables();
    myCalc.printAllVar();

    return 0;
}