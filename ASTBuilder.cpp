#include "ASTBuilder.h"
#include <stack>
#include <stdexcept>
#include <string>

static bool isOperator(const std::string& t) 
{
    if (t.empty()) return false;
    if (t.size() == 1) {
        char c = t[0];
        return c == '+' || c == '-' || c == '*' || c == 'x' || c == '/' ||
            c == '^' || c == '%' || c == 'r' || c == '!';
    }
    // multi-character operators/functions
    if (t == "sin" || t == "cos" || t == "tan" || t == "log") return true;
    if (t.size() > 3 && t.substr(0,3) == "log") return true;
    return false;
}

static bool isUnaryPostfix(char c)
{
    return c == '!';
}

static bool isUnaryFunction(const std::string& s)
{
    // include "logN" (e.g. "log2") as unary function
    return s == "sin" || s == "cos" || s == "tan" || (s.size() > 3 && s.substr(0,3) == "log");
}


ASTNode* AbstractTree(const std::vector<std::string>& rpn) 
{
    std::stack<ASTNode*> st;

    for (auto& t : rpn) 
    {
        if (!isOperator(t)) 
        {
            st.push(new ASTNode(t));
        }
        else {
            if (isUnaryFunction(t)) 
            {
                // function is prefix; pop one arg
                if (st.empty()) throw std::runtime_error(std::string("Missing operand for function: ") + t);
                ASTNode* a = st.top(); st.pop();
                st.push(new ASTNode(t, a, nullptr));
            }
            else
            {
                char op = t[0];
                if (isUnaryPostfix(op)) 
                {
                    if (st.empty()) throw std::runtime_error(std::string("Missing operand for operator: ") + t);
                    ASTNode* a = st.top(); st.pop();
                    st.push(new ASTNode(t, a, nullptr));
                }
                else
                {
                    if (st.size() < 2) throw std::runtime_error(std::string("Missing operands for binary operator: ") + t);
                    ASTNode* right = st.top(); st.pop();
                    ASTNode* left = st.top(); st.pop();
                    st.push(new ASTNode(t, left, right));
                }
            }
        }
    }

    return st.empty() ? nullptr : st.top();
}
