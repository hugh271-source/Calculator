#pragma once
#include <string>

struct ASTNode {
    std::string token;
    ASTNode* left = nullptr;
    ASTNode* right = nullptr;

    ASTNode(const std::string& t, ASTNode* l = nullptr, ASTNode* r = nullptr)
        : token(t), left(l), right(r) {
    }
};
