#ifndef BOP_COMP
#define BOP_COMP

#include "lexer.hpp"

class Bop {
private:
    lexer l;

public:
    Bop() = default;
    ~Bop() = default;

    // Tokenize de lexer
    void tokenize(const std::string& line, std::vector<Token>& tokens) {
        return l.tokenize(line, tokens);
    }
};

#endif