#include <iostream>
#include "calculator.h"
using namespace std;

void extractExpression(Calculator& calc, const string equation){
    char varName = toupper(equation[0]);
    if(!isalpha(varName))
        throw runtime_error("Invalid Input");

    if(equation[1] != '=')
        throw runtime_error("Invalid Format");

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
        myCalc.computeAllVariables();
        myCalc.printAllVar();
    }
    catch(const runtime_error& e){
            cerr << e.what() << endl;
    }



    return 0;
}