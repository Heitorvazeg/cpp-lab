#include "cell.h"
#include <algorithm>

// Protótipo da função printCell de utils
void printCell();

// Protótipos de comandos internos
void handleCd();

void Cell::run() {
    std::string input;

    // Printa celula ao iniciar Cell
    printCell();

    while (true) {
        std::cout << "Cell> ";
        std::getline(std::cin, input);
        if (input.empty()) continue;

        auto tokens = tokenize(input);
        if (tokens.empty()) continue;

        if (tokens[0] == "exit") break;

        if (isInternalCommand(tokens[0])) {
            executeInternalCommand(tokens);

        } else if (std::find(tokens.begin(), tokens.end(), "|") != tokens.end()) {
            handlePipes();

        } else if (std::find(tokens.begin(), tokens.end(), ">" || "<") != tokens.end()) {
            handleRedirections();

        } else {
            executeCommand(tokens);
        }
    }
}

void Cell::executeCommand(const std::vector<std::string>& tokens) {

}

void Cell::handlePipes() {

}

void Cell::handleRedirections() {

}

bool Cell::isInternalCommand(const std::string& command) {
    return command == "cd";
}

void Cell::executeInternalCommand(const std::vector<std::string>& tokens) {

}

std::vector<std::string> Cell::tokenize(const std::string& input) {
    std::istringstream iss(input);
    std::string token;
    std::vector<std::string> tokens;

    while (iss >> token) tokens.push_back(token);

    return tokens;
}