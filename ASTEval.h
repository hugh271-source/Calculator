#pragma once
#include "AST.h"
#include "Calc.h"
#include <map>
#include <string>

double RealAbstractTree(ASTNode* node,
    Calculator& c,
    double PI,
    double e,
    double lastResult,
    const std::map<std::string, double>& vars);
