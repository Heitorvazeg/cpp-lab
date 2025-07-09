#include "Stockfish.h"

int main() {
    std::string path = "./Stockfish/src/stockfish";

    Stockfish sf(path);

    while (true) {
        std::string comando;
        getline(std::cin, comando);

        if (comando == "a") {
            std::vector<std::string> moves;
            int depth;

        } else if (comando == "e") {


        } else if (comando == "l") {


        } else if (comando == "q") {
            sf.~Stockfish();
            break;
        }
    }
}
