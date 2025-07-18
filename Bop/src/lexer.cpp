#include "lexer.hpp"
#include <iostream>

// Protótipos de utils
bool isDigit(const std::string& input);

void lexer::tokenize(const std::string& line, std::vector<Token>& tokens) {
    std::string token;

    for (size_t i = 0; i < line.size(); i++) {
        char c = line[i];

        if (c == ' ' || c == ';') {
            if (!token.empty()) {
                if (token == "return") {
                    tokens.push_back({TokenType::_return, std::nullopt});

                } else if (isDigit(token)) {
                    tokens.push_back({TokenType::int_liter, token});
                }
                token.clear();
            }

            if (c == ';') {
                    tokens.push_back({TokenType::semi, std::nullopt});
            }

        } else {
            token += c;
        }
    }
}