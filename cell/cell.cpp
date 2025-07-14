#include "cell.h"
#include <algorithm>
#include <unordered_set>

// Protótipos de utils
void printCell();
std::vector<std::string> formatTokens(const std::vector<std::string> tokens);
std::unordered_set<std::string> showInternalCommands();

// Protótipos de comandos internos
void handleCd(const std::vector<std::string>& tokens);
void handleHelp();
void handleGrita(const std::vector<std::string>& tokens);

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
            handleRedirections(tokens);

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
        perror("Comando inválido");
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
    std::vector<std::string> comandos = formatTokens(tokens);

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
            perror("Comando inválido");
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

void Cell::handleRedirections(const std::vector<std::string>& tokens) {
    std::vector<std::string> comandos;
    std::string entrada, saida;

    for (size_t i = 0; i < tokens.size(); i++) {
        if (tokens[i] == ">") {
            if (i + 1 < tokens.size()) saida = tokens[i+1];

        } else if (tokens[i] == "<") {
            if (i + 1 < tokens.size()) entrada = tokens[i+1];

        } else {
            comandos.push_back(tokens[i]);
        }
    }

    pid_t pid = fork();
    if (pid == 0) {
        // Filho

        // Verifica se os arquivos são iguais
        if (!entrada.empty() && !saida.empty()) {
            if (entrada == saida) {
                std::cerr << "Erro: arquivo de entrada e saida sao o mesmo.\n";
                return;
            }
        }

        // Redireciona entrada
        if (!entrada.empty()) {
            int in = open(entrada.c_str(), O_RDONLY);

            if (in < 0) {
                perror("open entrada");
                exit(EXIT_FAILURE);
            }

            dup2(in, STDIN_FILENO);
            close(in);
        }

        // Redireciona saida
        if (!saida.empty()) {
            // Flags:
            // O_WRONLY: Permite escrita
            // O_CREAT: Cria arquivo quando não existente
            // O_TRUNC: Zera arquivo caso já esteja escrito
            // 0644: Seta permissões para manipular arquivo
            int out = open(saida.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);

            if (out < 0) {
                perror("open saida");
                exit(EXIT_FAILURE);
            }

            dup2(out, STDOUT_FILENO);
            close(out);
        }

        std::vector<char*> argv;
        for (auto& comando : comandos) {
            argv.push_back(const_cast<char*>(comando.c_str()));
        }
        argv.push_back(nullptr);

        execvp(argv[0], argv.data());
        perror("Comando Inválido");
        exit(EXIT_FAILURE);

    } else if (pid > 0) {
        // Pai

        wait(nullptr);
    } else {
        // Erro

        perror("fork");
    }
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
        handleCd(tokens);
        return;
    }

    if (tokens[0] == "cell") {
        printCell();
        return;
    }

    if (tokens[0] == "help") {
        handleHelp();
        return;
    }

    if (tokens[0] == "grita") {
        handleGrita(tokens);
        return;
    }
}

std::vector<std::string> Cell::tokenize(const std::string& input) {
    // istringstream é melhor para criar vetores de string
    std::istringstream iss(input);
    std::string token;
    std::vector<std::string> tokens;

    while (iss >> token) tokens.push_back(token);

    return tokens;
}