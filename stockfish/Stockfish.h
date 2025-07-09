#ifndef STOCKFISH_H
#define STOCKFISH_H

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sstream>

// Classe que gerencia a comunicação com a engine Stockfish via UCI 
class Stockfish {
private:
    int to_engine[2], from_engine[2];
    FILE *in, *out;
    pid_t pid;

public:
    // Constructor da Classe Stockfish com Path padrão em "./stockfish"
    explicit Stockfish(const std::string& path = "./stockfish");

    // Finaliza comunicação com a Engine e limpa recursos
    ~Stockfish();

    // Envia comandos para a Engine
    void send(const std::string& cmd);

    // Aguarda até que a Engine envie uma resposta
    void waitFor(const std::string& expected);

    // Analisa a posição atual baseada na sequência de lances
    // depth: Define a profundidade da análise
    // moves: Vetor com todos os lances desde a posição inicial até a atual
    std::string analyse(const std::vector<std::string>& moves, int depth);

    // Avalia a posição em centipawns
    std::string eval(const std::vector<std::string>& moves, int depth);

    // Devolve a sequência de lances das melhores linhas
    // n: Quantidade de linhas para análise
    std::vector<std::string> lines(const std::vector<std::string>& moves, int depth, int n);
};

#endif