#include <Stockfish.h>

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

    } else {
        close(to_engine[0]);
        close(from_engine[1]);

        in = fdopen(to_engine[1], "w");
        out = fdopen(from_engine[0], "r");

        send("uci");
        waitFor("uciok");

        send("isready");
        waitFor("readyok");

        send("ucinewgame");
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

    send("go depth" + std::to_string(depth));

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