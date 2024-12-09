#include <iostream>
#include <algorithm>
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
        cout << calc.computeExpr(' ', calc.splitExpr(equation)) << endl;
    }

}

int main() {
    Calculator myCalc;

    int n; cin >> n;
    string equation;
    try{
        for(int i=0; i<n; i++){
            cin >> equation;
            if(i==0 && equation == "AdvancedMode"){
                myCalc.goAdvanced();
                cout << "Turned on Advanced Mode." << endl;
                i--;
                continue;
            }

            if(myCalc.isAdvanced()){
                if(equation == "NewOperation"){
                    cout << "Enter priority and definition: " << endl;
                    int priority;
                    cin >> priority >> equation;
                    myCalc.addCustomOperator(equation, priority);
                    i--;
                    continue;  
                }   
            }

            remove(equation.begin(), equation.end(), ' ');
            extractExpression(myCalc, equation);
        }

    
        myCalc.computeAllVariables();

        if(!myCalc.isAdvanced())
            myCalc.printAllVar();
        else{
            cout << myCalc.getHistory();  
        }  
    }
    catch(const runtime_error& e){
            cerr  << e.what() << endl;
    }



    return 0;
}