#pragma once

#ifndef EMBEDDED_C__CLASS_WITH_CONSTANT_HPP
#define EMBEDDED_C__CLASS_WITH_CONSTANT_HPP

#include <cstdint>
#include <cstdlib>

// Global constants
static constexpr uint32_t kGlobalConstantExpr = 1;
static const uint32_t kGlobalConstant = rand();

class ClassWithConstant {
public:
    static constexpr uint32_t kConstantExpr = 2;
    static const uint32_t kConstant;
};
// Initialization of kConstant
const uint32_t ClassWithConstant::kConstant = kGlobalConstant * 2;

#endif //EMBEDDED_C__CLASS_WITH_CONSTANT_HPP
