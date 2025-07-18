#include <iostream>
#include <fstream>
#include <sstream>

#include "Bop.hpp"

int main(int argc, char* argv[]) {
    // Verifica a quantidade de argumentos em argv
    if (argc < 2) {
        std::cerr << "Uso indevido! " << "E: arquivo.bp" << "\n";
        return EXIT_FAILURE;
    }

    // Inicializa o file de acordo com o path argv[1]
    std::string filename = argv[1];
    std::fstream file(filename, std::ios::in);

    // Verifica se o path encontra algum arquivo
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir arquivo " << "E: path" << "\n";
        return EXIT_FAILURE;
    }

    // Verifica a extensão do arquivo
    if (!filename.find(".bp")) {
        std::cerr << "Extensão indevida! " << "E: arquivo<.bp>" << "\n";
        return EXIT_FAILURE;
    }

    std::stringstream contents_stream;
    contents_stream << file.rdbuf();
    file.close();

    // Instancia a classe centralizada Bop
    Bop b;
    std::string line;
    std::vector<Token> Tokens;

    // Tokeniza linha por linha
    while (std::getline(contents_stream, line)) {
        b.tokenize(line, Tokens);
    }

    for (auto t : Tokens) {
        if (t.Value.has_value()) {
            std::cout << t.Value.value();
        }
    }

    return EXIT_SUCCESS;
}