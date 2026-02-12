#include "RPN.h"
#include <stack>
#include <map>
#include <string>

static bool isOperator(const std::string& t) {
    if (t.size() != 1) return false;
    char c = t[0];
    return c == '+' || c == '-' || c == '*' || c == 'x' || c == '/' ||
        c == '^' || c == '%' || c == 'r' || c == 'l' ||
        c == 's' || c == 'c' || c == 't' || c == '!';
}

// postfix unary ops: s, c, t, !
static bool isUnaryPostfix(char c) {
    return c == 's' || c == 'c' || c == 't' || c == '!';
}

static int precedence(char op) {
    switch (op) {
    case 's': case 'c': case 't': case '!':
        return 4; // highest
    case '^':
        return 3;
    case '*': case 'x': case '/': case '%': case 'r': case 'l':
        return 2;
    case '+': case '-':
        return 1;
    default:
        return 0;
    }
}

static bool isRightAssoc(char op) {
    return op == '^';
}

std::vector<std::string> ReversedPoland(const std::vector<std::string>& tokens) {
    std::vector<std::string> out;
    std::stack<std::string> st;

    for (auto& t : tokens) {
        if (!isOperator(t) && t != "(" && t != ")" && t != ",") {
            // number, variable, etc.
            out.push_back(t);
        }
        else if (t == "(") {
            st.push(t);
        }
        else if (t == ")") {
            while (!st.empty() && st.top() != "(") {
                out.push_back(st.top());
                st.pop();
            }
            if (!st.empty() && st.top() == "(")
                st.pop();
        }
        else if (isOperator(t)) {
            char op = t[0];
            int p = precedence(op);
            bool right = isRightAssoc(op);

            while (!st.empty() && isOperator(st.top())) {
                char topOp = st.top()[0];
                int p2 = precedence(topOp);

                if ((!right && p <= p2) || (right && p < p2)) {
                    out.push_back(st.top());
                    st.pop();
                }
                else break;
            }
            st.push(t);
        }

    }

    while (!st.empty()) {
        out.push_back(st.top());
        st.pop();
    }

    return out;
}
