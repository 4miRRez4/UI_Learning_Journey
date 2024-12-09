#include <iostream>
#include "calculator.h"
using namespace std;

void extractExpression(Calculator& calc, const string equation){
    if(equation.find('=') != string::npos){
        if(equation[1] != '=')
            throw runtime_error("Invalid Format");

        char varName = toupper(equation[0]);
        if(!isalpha(varName))
            throw runtime_error("Invalid Input");


        string expr = equation.substr(2, equation.size());
        calc.initializeVar(varName, expr);
    }
    else{
        cout << calc.computeExpr(equation) << endl;
    }

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
            cerr  << e.what() << endl;
    }



    return 0;
}