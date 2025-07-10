# 🦠 Cell - Um Shell Personalizado em C++

Este projeto é uma implementação de um shell funcional e personalizado em C++,
 capaz de interpretar e executar comandos do usuário com suporte a:

- Comandos internos (`cd`, `exit`)
- Execução de comandos externos (`ls`, `echo`, etc.)
- Redirecionamento de entrada/saída (`<`, `>`)
- Operadores de pipe (`|`)
- Controle de processos com `fork`, `execvp` e `wait`

---

## 🔁 Ciclo de Execução: REPL

O funcionamento do shell segue o modelo clássico de interpretação de comandos conhecido como **REPL**:

> **Read → Evaluate → Print → Loop**

Esse ciclo define como um interpretador (ou shell) interage com o usuário:

1. **Read**  
   Lê a entrada do usuário, normalmente uma linha de comando.
   
2. **Evaluate**  
   Analisa e interpreta o comando, verifica se é interno (`cd`, `exit`) ou externo (`ls`, `echo`), lida com pipes/redirecionamentos e executa o comando via `fork` + `execvp`.

3. **Print**  
   Exibe a saída do comando no terminal, seja diretamente (como `ls`) ou com mensagens de erro.

4. **Loop**  
   Retorna ao início do processo, exibindo novamente o prompt para aceitar o próximo comando.

---