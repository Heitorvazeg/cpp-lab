#include "cell.h"
#include <algorithm>
#include <unordered_set>

// Protótipos de utils
void printCell();
std::vector<std::string> formatForHandlePipes(const std::vector<std::string> tokens);
std::unordered_set<std::string> showInternalCommands();

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
            handlePipes(tokens);

        } else if (std::find(tokens.begin(), tokens.end(), ">") != tokens.end() ||
                    std::find(tokens.begin(), tokens.end(), "<") != tokens.end()) {
            handleRedirections();

        } else {
            executeCommand(tokens);
        }
    }
}

void Cell::executeCommand(const std::vector<std::string>& tokens) {
    pid_t pid;
    pid = fork();

    if (pid == 0) {
        // Filho

        // execvp possui char* de tipo de parâmetro
        std::vector<char*> args;
        for (const auto& token : tokens) {
            args.push_back(const_cast<char*>(token.c_str()));
        }
        // Indica o fim do vetor de char*
        args.push_back(nullptr);

        execvp(args[0], args.data());
        perror("execvp");
        exit(EXIT_FAILURE);

    } else if (pid > 0) {
        // Ṕai

        wait(nullptr);

    } else {
        // Erro

        perror("fork");
    }
}

void Cell::handlePipes(const std::vector<std::string>& tokens) {
    std::vector<std::string> comandos = formatForHandlePipes(tokens);

    // Quantidade de processos
    int s = comandos.size();

    int fd[2];
    int in_fd = 0;

    for (int i = 0; i < s; i++) {
        pipe(fd);

        pid_t pid = fork();
        if (pid == 0) {
            // Filho

            dup2(in_fd, STDIN_FILENO);

            if (i != s-1) {
                dup2(fd[1], STDOUT_FILENO);
            }

            // Processo filho não lê o pipe
            close(fd[0]);
            close(fd[1]);

            // Tokeniza comandos sem pipe
            std::vector<std::string> tokensSemPipe = tokenize(comandos[i]);
            std::vector<char*> argv;

            // execvp possui char* de tipo de parâmetro
            for (auto& token : tokensSemPipe) {
                argv.push_back(const_cast<char*>(token.c_str()));
            }
            argv.push_back(nullptr);

            execvp(argv[0], argv.data());
            perror("execvp");
            exit(EXIT_FAILURE);

        } else if (pid > 0) {
            // Pai

            close(fd[1]);
            in_fd = fd[0];

        } else {
            perror("fork");
        }
    }
}

void Cell::handleRedirections() {

}

bool Cell::isInternalCommand(const std::string& command) {
    auto comandos = showInternalCommands();

    if (comandos.count(command)) {
        return true;
    }

    return false;
}

void Cell::executeInternalCommand(const std::vector<std::string>& tokens) {
    if (tokens[0] == "cd") {
        handleCd();
        return;
    }

    if (tokens[0] == "cell") {
        printCell();
        return;
    }
}

std::vector<std::string> Cell::tokenize(const std::string& input) {
    std::istringstream iss(input);
    std::string token;
    std::vector<std::string> tokens;

    while (iss >> token) tokens.push_back(token);

    return tokens;
}