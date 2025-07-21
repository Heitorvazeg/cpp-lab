#include <string>
#include <sstream>
#include <vector>
#include <iostream>

#include "lexer.hpp"

bool isDigit(const std::string& input) {
    if (input.empty()) return false;

    for (size_t i = 0; i < input.size(); i++) {
        if (!std::isdigit(static_cast<unsigned char>(input[i]))) return false;
    }

    return true;
}

std::string tokensToAsm(const std::vector<Token>& tokens) {
    std::stringstream s;

    s << "  global _start\n";
    s << "    _start:\n";

    for (size_t i = 0; i < tokens.size(); i++) {
        const Token& token = tokens.at(i);

        if (token.Type == TokenType::_return) {
            if (i + 1 < tokens.size() && tokens.at(i+1).Type == TokenType::int_liter)
                if (i + 2 < tokens.size() && tokens.at(i+2).Type == TokenType::semi) {
                    s << "    mov rax, 60\n";
                    s << "    mov rdi, " << tokens[i+1].Value.value() << "\n";
                    s << "    syscall\n";
                }
        }
    }

    return s.str();
}