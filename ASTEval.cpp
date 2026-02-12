#include "ASTEval.h"
#include <stdexcept>

// forward declaration from your existing file:
double parseValue(const std::string& token,
    double PI, double e, double lastResult,
    const std::map<std::string, double>& vars,
    bool& ok);

static bool isUnaryPostfix(char c) {
    return c == 's' || c == 'c' || c == 't' || c == '!';
}

double RealAbstractTree(ASTNode* node,
    Calculator& c,
    double PI,
    double e,
    double lastResult,
    const std::map<std::string, double>& vars)
{
    if (!node)
        throw std::runtime_error("Empty AST");

    // leaf: number / variable / pi / e / n
    if (!node->left && !node->right) {
        bool ok = false;
        double v = parseValue(node->token, PI, e, lastResult, vars, ok);
        if (!ok)
            throw std::runtime_error("Invalid value: " + node->token);
        return v;
    }

    char op = node->token[0];

    if (isUnaryPostfix(op)) {
        double x = RealAbstractTree(node->left, c, PI, e, lastResult, vars);
        return c.Calculate(x, op, 0.0);
    }
    else {
        double x = RealAbstractTree(node->left, c, PI, e, lastResult, vars);
        double y = RealAbstractTree(node->right, c, PI, e, lastResult, vars);
        return c.Calculate(x, op, y);
    }
}
