#include "ASTBuilder.h"
#include <stack>

static bool isOperator(const std::string& t) {
    if (t.size() != 1) return false;
    char c = t[0];
    return c == '+' || c == '-' || c == '*' || c == 'x' || c == '/' ||
        c == '^' || c == '%' || c == 'r' || c == 'l' ||
        c == 's' || c == 'c' || c == 't' || c == '!';
}

static bool isUnaryPostfix(char c) {
    return c == 's' || c == 'c' || c == 't' || c == '!';
}

ASTNode* AbstractTree(const std::vector<std::string>& rpn) {
    std::stack<ASTNode*> st;

    for (auto& t : rpn) {
        if (!isOperator(t)) {
            st.push(new ASTNode(t));
        }
        else {
            char op = t[0];
            if (isUnaryPostfix(op)) {
                ASTNode* a = st.top(); st.pop();
                st.push(new ASTNode(t, a, nullptr));
            }
            else {
                ASTNode* right = st.top(); st.pop();
                ASTNode* left = st.top(); st.pop();
                st.push(new ASTNode(t, left, right));
            }
        }
    }

    return st.empty() ? nullptr : st.top();
}
