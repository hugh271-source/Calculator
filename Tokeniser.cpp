#include "Tokeniser.h"
#include <cctype>

std::vector<Token> tokenize(const std::string& s) {
    std::vector<Token> out;
    size_t i = 0;

    while (i < s.size()) {
        char c = s[i];

        if (isspace(c)) { i++; continue; }

        if (isdigit(c) || (c == '.' && i + 1 < s.size() && isdigit(s[i + 1]))) {
            std::string num;
            while (i < s.size() && (isdigit(s[i]) || s[i] == '.'))
                num += s[i++];
            out.push_back({ TokenType::Number, num });
            continue;
        }

        if (isalpha(c)) {
            std::string id;
            while (i < s.size() && isalnum(s[i]))
                id += s[i++];
            out.push_back({ TokenType::Identifier, id });
            continue;
        }

        if (c == '(') { out.push_back({ TokenType::LParen, "(" }); i++; continue; }
        if (c == ')') { out.push_back({ TokenType::RParen, ")" }); i++; continue; }
        if (c == ',') { out.push_back({ TokenType::Comma, "," }); i++; continue; }

        out.push_back({ TokenType::Operator, std::string(1, c) });
        i++;
    }

    return out;
}
