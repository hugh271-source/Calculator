#pragma once
#include <string>

enum class TokenType {
    Number,
    Identifier,
    Operator,
    LParen,
    RParen,
    Comma
};

struct Token {
    TokenType type;
    std::string text;
};
