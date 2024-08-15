#include <iostream>
#include "class_with_constant.hpp"

int main() {
    std::cout << "Global const expr: " << kGlobalConstantExpr << std::endl;
    std::cout << "Global random const: " << kGlobalConstant << std::endl;

    std::cout << "Const expr: " << ClassWithConstant::kConstantExpr << std::endl;
    std::cout << "Random const: " << ClassWithConstant::kConstant << std::endl;

    return 0;
}