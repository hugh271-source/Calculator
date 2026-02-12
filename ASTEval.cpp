#include "ASTEval.h"
#include <stdexcept>
#include <string>

// forward declaration from your existing file:
double parseValue(const std::string& token,
    double PI, double e, double lastResult,
    const std::map<std::string, double>& vars,
    bool& ok);

static bool isUnaryPostfix(char c)
{
    return c == '!';
}

static bool isUnaryFunction(const std::string& s) 
{
    // include "logN" (e.g. "log2") as unary function
    return s == "sin" || s == "cos" || s == "tan" || (s.size() > 3 && s.substr(0,3) == "log");
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

    // if this node is a unary function like sin, cos, tan, or logN
    if (isUnaryFunction(node->token)) {
        // handle logN specially: token like "log2", "log10"
        if (node->token.size() > 3 && node->token.substr(0,3) == "log") {
            std::string baseStr = node->token.substr(3);
            if (baseStr.empty()) throw std::runtime_error("Missing log base in token: " + node->token);
            double base = 0.0;
            try {
                base = std::stod(baseStr);
            } catch (...) {
                throw std::runtime_error("Invalid log base: " + baseStr);
            }
            double val = RealAbstractTree(node->left, c, PI, e, lastResult, vars);
            // Calculator::Calculate expects (x, "log", y) where x is base, y is value
            return c.Calculate(base, std::string("log"), val);
        }

        double x = RealAbstractTree(node->left, c, PI, e, lastResult, vars);
        return c.Calculate(x, node->token, 0.0);
    }

    // postfix unary (!)
    if (node->token.size() == 1 && isUnaryPostfix(node->token[0])) {
        double x = RealAbstractTree(node->left, c, PI, e, lastResult, vars);
        return c.Calculate(x, node->token, 0.0);
    }

    // binary operator: use FULL token ("log", "^", "r", etc.)
    double x = RealAbstractTree(node->left, c, PI, e, lastResult, vars);
    double y = RealAbstractTree(node->right, c, PI, e, lastResult, vars);
    return c.Calculate(x, node->token, y);

}
