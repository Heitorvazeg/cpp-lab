#include <iostream>
#include <vector>
#include <unordered_set>
#include <unistd.h>
#include <limits.h>

// Printa Célula bonitinha
void printCell() {
    std::cout << "          ~ ~ ~ ~ ~ ~ ~ ~ ~ ~          \n";
    std::cout << "       ~                       ~        \n";
    std::cout << "    ~     *  :  .     .  :  *     ~     \n";
    std::cout << "  ~      :                   :      ~   \n";
    std::cout << " ~       .      @@@@@@@      .       ~  \n";
    std::cout << " ~       :    @@@@@@@@@@@    :       ~  \n";
    std::cout << " ~       :   @@@@     @@@@   :       ~  \n";
    std::cout << " ~       .  @@@         @@@  .       ~  \n";
    std::cout << "  ~      .   @@@       @@@   .      ~   \n";
    std::cout << "    ~    :    @@@@   @@@@    :    ~     \n";
    std::cout << "       ~  .     @@@@@@@     .  ~        \n";
    std::cout << "          ~ ~ ~ ~ ~ ~ ~ ~ ~ ~          \n";
    std::cout << "\n";
}
 
// Formata um vetor de tokens e devolve o vetor de comandos sem pipes
// Usado para descrever a quantidade de processos que serão executados
std::vector<std::string> formatTokens(const std::vector<std::string> tokens) {
    std::vector<std::string> aux;
    std::string comando;
    
    for (const auto& token : tokens) {
        if (token == "|") {
           if (!comando.empty()) aux.push_back(comando);
           comando.clear();

        } else {
            if (!comando.empty()) comando += " ";
            comando += token;
        }
    }

    if (!comando.empty()) aux.push_back(comando);
    
    return aux;
}

std::unordered_set<std::string> comandos;

// Devolve um set com todos os comandos internos
std::unordered_set<std::string> showInternalCommands() {
    if (comandos.empty()) {
        comandos.insert("cd");
        comandos.insert("cell");
        comandos.insert("help");
        comandos.insert("grita");
    }
    
    return comandos;
}

// Printa o diretório atual
void showDirectory() {
    // PATH_MAX é o tamanho máximo de um PATH
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::cout << "Diretório atual: " << cwd << "\n";

    } else {
        perror("getcwd");
    }
}