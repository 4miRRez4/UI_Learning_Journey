#include <iostream>
#include "calculator.h"
using namespace std;

void testCalculator(Calculator& calc) {
    std::cout << "\n=== Calculator Test Suite ===\n" << std::endl;

    // Test 1: Basic binary operations
    std::cout << "Test 1: Basic binary operations" << std::endl;
    std::cout << "2 + 3 = " << calc.computeExpr("2 + 3") << std::endl;
    std::cout << "5 * 4 = " << calc.computeExpr("5 * 4") << std::endl;
    std::cout << "10 / 2 = " << calc.computeExpr("10 / 2") << std::endl;
    std::cout << "7 - 5 = " << calc.computeExpr("7 - 5") << std::endl;

    // Test 2: Unary operations
    std::cout << "\nTest 2: Unary operations" << std::endl;
    std::cout << "-3 = " << calc.computeExpr("-3") << std::endl;
    std::cout << "4! = " << calc.computeExpr("4 !") << std::endl;

    // Test 3: Operator precedence and parentheses
    std::cout << "\nTest 3: Operator precedence and parentheses" << std::endl;
    std::cout << "2 + 3 * 4 = " << calc.computeExpr("2 + 3 * 4") << std::endl;
    std::cout << "(2 + 3) * 4 = " << calc.computeExpr("( 2 + 3 ) * 4") << std::endl;
    std::cout << "3 + 4! = " << calc.computeExpr("3 + 4 !") << std::endl;

    // Test 4: Complex expressions
    std::cout << "\nTest 4: Complex expressions" << std::endl;
    std::cout << "5 + 2 * (3 + 4) - 6 / 2 = " << calc.computeExpr("5 + 2 * ( 3 + 4 ) - 6 / 2") << std::endl;
    std::cout << "3 * (2 + (4 - 1)) = " << calc.computeExpr("3 * ( 2 + ( 4 - 1 ) )") << std::endl;

    // Test 5: Variable assignments
    std::cout << "\nTest 5: Variable assignments" << std::endl;
    calc.setVariableValue("X", calc.computeExpr("2 + 3"));
    calc.setVariableValue("Y", calc.computeExpr("x * 4"));
    calc.setVariableValue("Z", calc.computeExpr("( y + x ) / 5"));
    std::cout << "x = 2 + 3 => x = " << calc.getVariableValue("X") << std::endl;
    std::cout << "y = x * 4 => y = " << calc.getVariableValue("Y") << std::endl;
    std::cout << "z = (y + x) / 5 => z = " << calc.getVariableValue("Z") << std::endl;

    // Test 6: Using variables in expressions
    std::cout << "\nTest 6: Using variables in expressions" << std::endl;
    std::cout << "z + y * x = " << calc.computeExpr("z + y * x") << std::endl;
    std::cout << "(x + y) * z = " << calc.computeExpr("( x + y ) * z") << std::endl;

    // Test 7: Edge cases and invalid inputs
    std::cout << "\nTest 7: Edge cases and invalid inputs" << std::endl;
    try {
        std::cout << "Empty expression: " << calc.computeExpr("") << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    try {
        std::cout << "Invalid operator: " << calc.computeExpr("5 # 3") << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    try {
        std::cout << "Division by zero: " << calc.computeExpr("5 / 0") << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    try {
        std::cout << "Mismatched parentheses: " << calc.computeExpr("( 3 + 2") << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "\n=== End of Test Suite ===" << std::endl;
}

int main() {
    try {
        Calculator calc;
        testCalculator(calc);
    } catch (const std::exception& e) {
        std::cerr << "Critical Error: " << e.what() << std::endl;
    }

    return 0;
}