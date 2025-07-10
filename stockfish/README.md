Este projeto demonstra como integrar o motor de xadrez Open-Source **Stockfish** com C++ utilizando o protocolo **UCI (Universal Chess Interface)**.

Através da execução do processo Stockfish e comunicação via `stdin`/`stdout`, o programa envia posições e comandos, recebe lances recomendados e interpreta os resultados.

---

## 📌 Funcionalidades

-Inserção interativa de lances em formato UCI via linha de comando;
-Análise do melhor lance a partir de uma posição (go depth);
-Avaliação numérica da posição (score em centipawns ou mate);
-Extração das principais linhas de análise com MultiPV;
-Comunicação direta com a engine Stockfish via fork(), pipe() e dup2()

---