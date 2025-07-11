#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

class Cell {
private:
    // Executa comandos com binários externos
    void executeCommand(const std::vector<std::string>& tokens);

    // Lida com Pipes para comandos sequenciais
    void handlePipes(const std::vector<std::string>& tokens);

    // Lida com redirecionamentos de resultados a arquivos
    void handleRedirections();

    // Confere se o primeiro Token é um comando interno
    bool isInternalCommand(const std::string& command);

    // Executa comandos internos
    void executeInternalCommand(const std::vector<std::string>& tokens);

    // Transforma uma string em um vetor de strings Tokens
    // Cada Token representa uma parte do prompt recebido
    std::vector<std::string> tokenize(const std::string& input);

public:
    // Inicializa o Shell (Cell)
    void run();
};

#endif