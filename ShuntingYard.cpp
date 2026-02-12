#include "ShuntingYard.h"
#include <stack>
#include <map>

struct OpInfo {
    int prec;
    bool rightAssoc;
};

static std::map<std::string, OpInfo> ops = {
    {"+", {1, false}},
    {"-", {1, false}},
    {"*", {2, false}},
    {"/", {2, false}},
    {"%", {2, false}},
    {"^", {3, true}}
};

bool isFunction(const Token& t) {
    return t.type == TokenType::Identifier &&
        (t.text == "sin" || t.text == "cos" || t.text == "tan" ||
            t.text == "log" || t.text == "ln");
}

std::vector<Token> toRPN(const std::vector<Token>& tokens) {
    std::vector<Token> out;
    std::stack<Token> st;

    for (auto& t : tokens) {
        if (t.type == TokenType::Number || t.type == TokenType::Identifier) {
            out.push_back(t);
        }
        else if (isFunction(t)) {
            st.push(t);
        }
        else if (t.type == TokenType::Operator) {
            while (!st.empty() && st.top().type == TokenType::Operator) {
                auto& top = st.top();
                auto a = ops[t.text];
                auto b = ops[top.text];

                if ((!a.rightAssoc && a.prec <= b.prec) ||
                    (a.rightAssoc && a.prec < b.prec)) {
                    out.push_back(top);
                    st.pop();
                }
                else break;
            }
            st.push(t);
        }
        else if (t.type == TokenType::LParen) {
            st.push(t);
        }
        else if (t.type == TokenType::RParen) {
            while (!st.empty() && st.top().type != TokenType::LParen) {
                out.push_back(st.top());
                st.pop();
            }
            st.pop();

            if (!st.empty() && isFunction(st.top())) {
                out.push_back(st.top());
                st.pop();
            }
        }
        else if (t.type == TokenType::Comma) {
            while (!st.empty() && st.top().type != TokenType::LParen) {
                out.push_back(st.top());
                st.pop();
            }
        }
    }

    while (!st.empty()) {
        out.push_back(st.top());
        st.pop();
    }

    return out;
}
