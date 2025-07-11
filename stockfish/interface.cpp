#include "Stockfish.h"

// Lê os movimentos do jogador para enviar à Engine
std::vector<std::string> readMoves() {
    std::vector<std::string> moves;
    std::cout << "Digite os lances (Ex: e2e4 g1f3): \n";
    
    std::string movesS;
    std::getline(std::cin, movesS);
    
    int s = movesS.size();
    for (int i = 0; i < s; i+=5) {
        moves.push_back(movesS.substr(i, 4));
    }

    return moves;
}

// Lê um valor inteiro auxiliar N ou Depth
int readInt(const std::string& prompt) {
    int val;
    std::cout << prompt;
    std::cin >> val;
    std::cin.ignore();
    return val;
}

// Printa os comandos na tela
void printComandos() {
    std::cout << "Comandos:\n"
        << "  a  -> analyse: melhor lance\n"
        << "  e  -> eval: avaliação estática\n"
        << "  l  -> lines: múltiplas linhas\n"
        << "  q  -> sair\n";
}

int main() {
    std::string path = "./Stockfish/src/stockfish";

    Stockfish sf(path);

    printComandos();

    while (true) {
        std::cout << "Comando > ";
        std::string comando;
        getline(std::cin, comando);

        if (comando == "a") {
            auto moves = readMoves();
            int depth = readInt("Profundidade: ");
            std::string best = sf.analyse(moves, depth);

            std::cout << "Melhor lance sugerido: " << best << "\n";

            printComandos();

        } else if (comando == "e") {
            auto moves = readMoves();
            int depth = readInt("Profundidade: ");
            std::string val = sf.eval(moves, depth);

            std::cout << "Avaliação: " << val << "\n";

            printComandos();

        } else if (comando == "l") {
            auto moves = readMoves();
            int depth = readInt("Profundidade: ");
            int n = readInt("Quantidade linhas (n): ");
            
            auto lines = sf.lines(moves, depth, n);
            std::cout << "Principais " << n << " linhas:\n";

            for (auto line : lines) {
                std::cout << line;
            }

            printComandos();

        } else if (comando == "q") {
            sf.~Stockfish();
            break;

        } else {
            std::cout << "Comando inválido!\n";

            printComandos();
        }
    }
}