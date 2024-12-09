#include "custom_operator.h"

CustomOperator::CustomOperator(const string s, const int p, const vector<string> func, int numOfPara) 
                : Operator(s, OperatorType::Custom, p, numOfPara), functionality_postfix(func){}

double CustomOperator::apply(double operand1, double operand2) const{
    vector<string> subtituted = functionality_postfix;
    for(string& part: subtituted){
        if(part == "A")
            part = to_string(operand1);
        if(part == "B")
            part = to_string(operand2);
    }
    
    Calculator defaultCalc;
    return defaultCalc.computePostfix(subtituted);
}