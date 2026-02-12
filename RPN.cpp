#include "RPN.h"
#include <stack>
#include <map>
#include <string>

static bool isOperator(const std::string& t) {
    if (t.empty()) return false;
    if (t.size() == 1) {
        char c = t[0];
        return c == '+' || c == '-' || c == '*' || c == 'x' || c == '/' ||
            c == '^' || c == '%' || c == 'r' || c == '!';
    }
    // multi-char operators: "sin", "cos", "tan", "log", or "logN" (like "log2")
    if (t == "sin" || t == "cos" || t == "tan" || t == "log") return true;
    if (t.size() > 3 && t.substr(0, 3) == "log") return true;
    return false;
}

// postfix unary ops: s, c, t, !
// unary functions are prefix now: "sin", "cos", "tan", "!"
static bool isUnaryPostfix(char c) {
    return c == '!';
}

static bool isUnaryFunction(const std::string& s) {
    // include "logN" (like "log2") as a unary function (but not plain "log" which is binary)
    return s == "sin" || s == "cos" || s == "tan" || (s.size() > 3 && s.substr(0,3) == "log");
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
        // if a function is on top of the stack after popping '(', pop it to output
        // pop any functions that are on the stack (e.g. sin, cos, tan, log, logN)
        while (!st.empty()) {
            std::string top = st.top();
            if (top == "sin" || top == "cos" || top == "tan" || top == "log" || (top.size() > 3 && top.substr(0,3) == "log")) {
                out.push_back(top);
                st.pop();
                continue;
            }
            break;
        }
        }
        else if (isOperator(t)) {
            // functions (sin, cos, tan, log...) are pushed as operators with highest precedence
            if (isUnaryFunction(t)) {
                st.push(t);
                continue;
            }

            // log with base e.g. "log2" treat as operator too (handled above by isUnaryFunction, but keep safe)
            if (t.size() > 3 && t.substr(0, 3) == "log") {
                st.push(t);
                continue;
            }

            char op = t[0];
            int p = precedence(op);
            bool right = isRightAssoc(op);

            while (!st.empty() && isOperator(st.top())) {
                std::string top = st.top();
                // functions on stack should be popped first
                if (isUnaryFunction(top) || (top.size() > 3 && top.substr(0,3) == "log")) {
                    out.push_back(top);
                    st.pop();
                    continue;
                }

                char topOp = top[0];
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
