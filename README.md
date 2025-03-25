# Minishell 🐚  
**A Lightweight Unix Shell Built in C**

Minishell is a simplified Unix shell developed as part of the 42 curriculum. It replicates core features of standard shells like `bash`, `zsh`, and `sh`, with custom implementation of process control, piping, signal handling, and redirections.

The goal of the project was to deepen understanding of low-level UNIX system calls, process management, and terminal behavior in C.

### ✨ Key Features

- Built-in commands: `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`
- Support for command pipelines (`|`)  
- Input/output redirections (`>`, `>>`, `<`) and heredocs (`<<`)  
- Signal handling (e.g. `Ctrl+C`, `Ctrl+\`)  
- Environment variable parsing and expansion  
- Forking and execve for external binaries  
- Exit code handling and shell loop management

---

## 🛠 Tech Stack

**Language & Libraries**
- C (C89 / C99)  
- POSIX standard libraries (unistd.h, stdlib.h, signal.h, etc.)

**Concepts**
- Process creation (`fork`, `execve`, `waitpid`)  
- Signal management (`SIGINT`, `SIGQUIT`, etc.)  
- File descriptors and redirections  
- Environment variable manipulation  
- Parsing and tokenization (minimal shell grammar)  

## 📬 Contact

Built and maintainced by [@lulubas](https://github.com/lulubas)
