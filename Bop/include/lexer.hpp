#ifndef LEXER_BP
#define LEXER_BP

#include <string>
#include <optional>
#include <vector>

enum class TokenType {
    _return,
    int_liter,
    semi
};

struct Token {
    TokenType Type;
    std::optional<std::string> Value;
};

class lexer {
public:
    // Tokeniza uma linha de texto
    void tokenize(const std::string& line, std::vector<Token>& tokens);
};

#endif