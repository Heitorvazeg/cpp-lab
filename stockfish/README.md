Este projeto demonstra como integrar o motor de xadrez Open-Source **Stockfish** com C++ utilizando o protocolo **UCI (Universal Chess Interface)**.

Através da execução do processo Stockfish e comunicação via `stdin`/`stdout`, o programa envia posições e comandos, recebe lances recomendados e interpreta os resultados.

---

## 📌 Funcionalidades

- Inicializa o motor Stockfish via linha de comando
- Define posições com base na notação `startpos` + lances (e.g., `e2e4 e7e5`)
- Solicita o melhor lance até uma profundidade configurável
- Exibe as respostas completas do motor
- Interpreta o `bestmove` retornado

---