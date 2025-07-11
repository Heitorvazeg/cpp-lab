#include "Stockfish.h"
#include <iomanip>

Stockfish::Stockfish(const std::string& path) {
    pipe(to_engine);
    pipe(from_engine);
    pid = fork();

    if (pid == 0) {
        dup2(to_engine[0], STDIN_FILENO);
        dup2(from_engine[1], STDOUT_FILENO);
        close(to_engine[1]);
        close(from_engine[1]);

        execlp(path.c_str(), path.c_str(), nullptr);
        perror("Erro ao executar Stockfish");
        exit(1);

    } else if (pid > 0) {
        close(to_engine[0]);
        close(from_engine[1]);

        in = fdopen(to_engine[1], "w");
        out = fdopen(from_engine[0], "r");

        send("uci");
        waitFor("uciok");

        send("isready");
        waitFor("readyok");

        send("ucinewgame");

    } else {
        perror("fork");
    }
}

Stockfish::~Stockfish() {
    send("quit");
    fclose(in);
    fclose(out);
    wait(nullptr);
}

void Stockfish::send(const std::string& cmd) {
    fprintf(in, "%s\n", cmd.c_str());
    fflush(in);
}

void Stockfish::waitFor(const std::string& expected) {
    char buffer[512];
    
    while(fgets(buffer, sizeof(buffer), out)) {
        std::string line(buffer);
        std::cout << ">> " << line;

        if (line.find(expected) != std::string::npos) break;
    }
}

std::string Stockfish::analyse(const std::vector<std::string>& moves, int depth) {
    std::stringstream cmd;
    cmd << "position startpos moves";

    for (const auto& move : moves) {
        cmd << " " << move;
    }

    send(cmd.str());

    send("go depth " + std::to_string(depth));

    std::string bestmove;
    char buffer[512];
    while (fgets(buffer, sizeof(buffer), out)) {
        std::string line(buffer);
        std::cout << ">> " << line;

        if (line.find("bestmove") != std::string::npos) {
            bestmove = line;
            break;
        }
    }
    return bestmove;
}

std::string Stockfish::eval(const std::vector<std::string>& moves, int depth) {
    std::stringstream cmd;
    cmd << "position startpos moves";

    for (const auto& move : moves) {
        cmd << " " << move;
    }

    send(cmd.str());
    send("go depth " + std::to_string(depth));

    std::string val;
    char buffer[512];
    while(fgets(buffer, sizeof(buffer), out)) {
        std::string line(buffer);
        std::cout << ">> " << line;

        if (line.find("score cp") != std::string::npos || line.find("score mate") != std::string::npos) {
            val = line;

        } else if (line.find("bestmove") != std::string::npos) {
            break;
        }
    }

    int s = val.size();
    std::vector<std::string> valV;
    std::string palavra = "";
    for (int i = 0; i < s; i++) {
        if (val[i] == ' ') {
            if (!palavra.empty()) {
                valV.push_back(palavra);
                palavra = "";
            }
            continue;
        }
        palavra += val[i];
    }

    std::stringstream result;
    if (valV[8] == "mate") {
        result << valV[8] << " " << valV[9];
        return result.str();

    } else {
        result << valV[8] << " " << std::fixed << std::setprecision(2) << std::stoi(valV[9]) / 100.0;
    }
    
    return result.str();
}

std::vector<std::string> Stockfish::lines(const std::vector<std::string>& moves, int depth, int n) {
    send("setoption name MultiPV value " + std::to_string(n));
    
    std::stringstream cmd;
    cmd << "position startpos moves";
    for (const auto& move : moves) {
        cmd << " " << move;
    }
    send(cmd.str());


    send("go depth " + std::to_string(depth));
    
    std::vector<std::string> results;
    char buffer[512];
    while(fgets(buffer, sizeof(buffer), out)) {
        std::string line(buffer);

        for (int i = 1; i <= n; i++) {
            if (line.find("multipv "+std::to_string(i)) != std::string::npos) {
                results.push_back(line);
            }
        }
        if (line.find("bestmove") != std::string::npos) {
            break;
        }
    }

    return results;
}
