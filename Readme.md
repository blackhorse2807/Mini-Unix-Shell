# Mini Unix Shell

A fully functional Unix-like shell implemented in C++ using Linux system calls.  
This project demonstrates core operating system concepts including process creation, inter-process communication, job control, signal handling, and I/O redirection.

---

## Features

- Command execution using `fork()` and `execvp()`
- Support for pipelines (`|`)
- Input and output redirection (`<`, `>`)
- Background process execution (`&`)
- Zombie process cleanup
- Job control using process groups
- Signal handling for:
  - `Ctrl+C` (SIGINT)
  - `Ctrl+Z` (SIGTSTP)
- Built-in commands:
  - `jobs`
  - `exit`

---

## Project Structure
