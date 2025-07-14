#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>
#include <algorithm>

// Protótipo de Utils"\n"
void showDirectory();

void handleCd(const std::vector<std::string>& tokens) {
    const char* path = nullptr;

    // Vai para Home quando sem argumento
    if (tokens.size() < 2) {
        path = getenv("HOME");

        if (!path) {
            std::cerr << "Erro: Home não localizado\n";
            return;

        }
    } else {
        path = tokens[1].c_str();
    }

    // Chama "cd"
    if (chdir(path) != 0) {
        perror("cd");

    } else {
        // Mostra diretório após chamar "cd"
        showDirectory();
    }
}

// Printa comandos
void handleHelp() {
    std::cout << "  Bem-vindo ao Cell Shell  \n\n";
    std::cout << "      Comandos disponíveis:\n";
    std::cout << "- Comandos binários do sistema (como ls, echo, grep, cat...)\n";
    std::cout << "- Redirecionamento: `>` para saída, `<` para entrada\n";
    std::cout << "- Navegação: `cd` para mudar de diretório\n";
    std::cout << "      Comandos personalizados:\n";
    std::cout << "  • `grita`: converte texto para caixa alta\n";
    std::cout << "  • `cell`: comando estético ou institucional (personalizável)\n\n";
};

// Repete oque foi digitado tudo maiúsculo
void handleGrita(const std::vector<std::string>& tokens) {
    for (size_t i = 1; i < tokens.size(); i++) {
        std::string palavra = tokens[i];
        std::transform(palavra.begin(), palavra.end(), palavra.begin(), ::toupper);
        std::cout << palavra << " ";
    }

    std::cout << "\n";
}