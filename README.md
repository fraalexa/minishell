*This project has been created as part of the 42 curriculum by fraalexa and rdeimaos.*

# Minishell — simplified POSIX-style shell implementation

## Description

Minishell is a compact shell program designed to mimic the behavior of a standard UNIX shell as closely as possible. The project involves handling tasks such as tokenization, command parsing, pipelines, input/output redirections (including heredocs), built-in commands, environment variables, and basic signal handling. Created as part of the 42 curriculum, Minishell provides practical experience with process management, file descriptors, signals, and the inner workings of shell command interpretation.

## Features

- Basic Bash-compatible input parsing and syntax.
- Command history (up and down arrows).
- Environment variable expansion.
- Pipes: `cmd1 | cmd2 | cmd3`.
- Redirections:
  - Output: `>` and `>>`
  - Input: `<`
  - Heredoc: `<<`
- Builtin commands :
  - `echo` (and option `-n`)
  - `cd` (with only a relative or absolute path)
  - `pwd` (no options)
  - `export` (no options)
  - `unset` (no options)
  - `env` (no options or arguments)
  - `exit` (with exit number but no other options) 
- Signal handling comparable to interactive Bash (`SIGINT`/Ctrl-C behavior, ignoring `SIGQUIT` in interactive mode, etc.).
- Command execution pipeline implemented with `fork`, `execve`, `dup2`, and `pipe`.
- Error handling for syntax errors, command-not-found, access/permission errors.

## Instructions

1. Clone the repository:

```bash
git clone
cd minishell
```

2. Compile the project:

```bash
make
```

3. Run the shell:

```bash
./minishell
```

## Architecture (short overview)

```
minishell/
├── src/
│   ├── lexer/       # Tokenizing input → tokens
│   ├── parser/      # Build AST, check syntax
│   ├── executor/    # AST, Pipelines, redirections, FD management
│   ├── builtins/    # cd, echo, export, ...
│   └──── main/
├── lib/             # libft
├── includes/        # Headers (data structures)
├── Makefile
├── utils/
└── obj/
```

### Core concepts

- **Tokenizer**  
  Splits the input into meaningful components such as commands, pipes, redirections, and quoted strings.

- **Parser / AST**  
  Builds an internal representation of the command chain, validates syntax, and prepares structures for execution.

- **Executor**  
  Sets up pipelines, spawns child processes, manages file descriptors using `dup2`, handles input/output redirections, and executes programs with `execve()`.

- **Builtins in the Parent Process**  
  Certain built-in commands like `cd` and `export` run in the parent process to modify the shell environment directly.

- **Signal Handling**  
  Adjusts interactive behavior to behave consistently with standard shells.

## Author

fraalexa — GitHub: https://github.com/fraalexa
rdeimaos — GitHub: https://github.com/rdeiamos
