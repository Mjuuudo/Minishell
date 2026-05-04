# Minishell - As beautiful as a shell 🐚

![alt text](image.png)

## Brief Overview
Minishell is a 42 school project aimed at creating a simplified version of the Bourne Again SHell (`bash`). It involves parsing user input, expanding environment variables, handling quotes correctly, managing file descriptors/redirections (`<`, `>`, `<<`, `>>`), implementing pipes (`|`), and executing system binaries alongside custom built-in commands. 

This project gave a comprehensive look into process creation (using `fork`), communication (using `pipe`), process synchronization (`wait`, `waitpid`), signal handling, and file manipulation.

<a href="https://github.com/oakoudad/badge42"><img src="https://badge.mediaplus.ma/darkgray/abait-ou" alt="abait-ou's 42 stats" /></a>

## What We Learned
Rebuilding a shell from scratch exposes the exact mechanisms UNIX systems use to interpret and execute commands:
- **Lexical Analysis & Parsing:** Splitting user input into tokens, intelligently managing single (`'`) and double (`"`) quotes, and parsing complex syntax.
- **Environment Variables Management:** Extracting, updating, and storing variables locally in a custom linked list structure.
- **Process Management:** Mastering `fork` to dispatch child processes, replacing running executables using `execve`, and cleanly synchronizing processes with `waitpid`.
- **I/O Redirections & Pipes:** Diverting standard input and output to files or chaining multiple commands together via anonymous pipes.
- **Signal Handling:** Reprogramming signals like `Ctrl-C` (`SIGINT`), `Ctrl-D` (EOF), and `Ctrl-\` (`SIGQUIT`) to match standard bash behavior.

## Supported Built-ins
Minishell implements the core shell built-in functions:
- `echo` with the `-n` option
- `cd` with only a relative or absolute path
- `pwd` with no options
- `export` with no options
- `unset` with no options
- `env` with no options or arguments
- `exit` with no options

## How to Use

### Prerequisites
- A UNIX-like environment (Linux/macOS)
- `gcc` or `cc` compiler
- `make`
- `readline` library installed

### Building the Shell
Run `make` at the root of the repository to compile the source code.
```bash
make
```

### Running the Shell
After successfully compiling, you can start your brand-new shell environment:
```bash
./minishell
```

Once running, Minishell behaves exactly like bash:
```bash
minishell> export NAME="42 Student"
minishell> echo "Hello, $NAME!"
Hello, 42 Student!
minishell> ls -la | grep Makefile > output.txt
minishell> cat output.txt
-rw-r--r--  1 user group 2206 May  4 11:59 Makefile
minishell> exit
```

## Internal Architecture & Steps Followed

### 1. Environment Parsing
- `ft_addnodeenv()`: Creates and initializes an environment node (key-value pair).
- `ft_initnodeenv()`: Parses strings into key-value pairs and stores data properly.

### 2. Lexical Analysis (Lexer)
- `fg_shellon()`: Starts the loop to collect input.
- `ft_lexer()`: Divides the collected line into understandable tokens.
- `ft_spacecalculation()`: Pre-calculates space required to allocate exactly what's needed.
- `ft_quotes()`: State tracker to verify if a character sequence is within single or double quotes.

### 3. Execution
- Processes the interpreted tokens.
- Maps command strings to built-ins or queries the `PATH` strings for external executables.
- Wires up STDIN/STDOUT via `dup2` before calling `execve()`.

## Useful Resources
- **[GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)** ⭐
- [Let's Build a Shell - Writing a simple shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)
- [Understanding Pipes and Forks](https://www.rozmichelle.com/pipes-forks-dup/)
- [Readline Library Documentation](https://web.mit.edu/gnu/doc/html/rlman_1.html)
