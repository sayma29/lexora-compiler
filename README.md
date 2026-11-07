# Lexora Compiler

### Design and Implementation of a Mini Programming Language Compiler Using Flex and Bison

Lexora is a Compiler Construction Lab project that aims to design and implement a mini programming language compiler using **Flex and Bison**. The project follows the language specification and requirements provided in the course project manual.

The compiler will perform lexical analysis, syntax analysis, abstract syntax tree construction, symbol table management, semantic analysis, and three-address code generation.

## Project Objectives

- Implement a lexical analyzer using Flex.
- Develop a parser using Bison.
- Construct an Abstract Syntax Tree (AST).
- Implement a symbol table with nested scope management.
- Perform semantic analysis and error detection.
- Generate Three-Address Code (TAC).

## Supported Language Features

The mini language supports the following features according to the project specification:

### Data Types
- `int`
- `float`
- `bool`

### Control Statements
- `if`
- `if-else`
- `while`

### Operators

| Category | Operators |
|---|---|
| Arithmetic | `+`, `-`, `*`, `/`, `%` |
| Relational | `<`, `>`, `<=`, `>=`, `==`, `!=` |
| Logical | `&&`, `||`, `!` |
| Assignment | `=` |

### Other Features
- Variable declaration and assignment
- Boolean literals (`true`, `false`)
- Print statements
- Nested blocks and scope management
- Single-line and block comments

## Compiler Architecture

The planned compiler pipeline is:

```text
Source Code
    |
    v
Lexical Analyzer (Flex)
    |
    v
Syntax Analyzer (Bison)
    |
    v
Abstract Syntax Tree (AST)
    |
    v
Symbol Table
    |
    v
Semantic Analyzer
    |
    v
Three-Address Code (TAC)
```

## Technologies Used

- **C/C++** – Compiler implementation
- **Flex / win_flex** – Lexical analysis
- **Bison / win_bison** – Syntax analysis
- **GCC / G++** – Compilation
- **MSYS2 UCRT64** – Development environment
- **Visual Studio Code** – Code editor
- **Git and GitHub** – Version control and collaboration

## Project Structure

```text
lexora-compiler/
│
├── docs/
│   ├── language_spec.md
│   ├── AI_USAGE_LOG.md
│   └── ROADMAP.md
│
├── src/
│   ├── lexer/
│   ├── parser/
│   ├── ast/
│   ├── semantic/
│   ├── symbol_table/
│   └── diag/
│
├── tests/
│   ├── valid/
│   └── lexical_errors/
│
├── examples/
│
├── Makefile
├── .gitignore
└── README.md
```

## Development Setup

The project is currently developed on Windows using MSYS2 UCRT64 and Visual Studio Code.

Required tools:

- GCC
- Flex or win_flex
- Bison or win_bison
- mingw32-make
- Git

Verify the installed tools:

```bash
gcc --version
g++ --version
win_flex --version
win_bison --version
mingw32-make --version
git --version
```

## Build and Run

The current implementation includes a standalone lexer test driver.

Build the lexer:

```bash
mingw32-make FLEX=win_flex BISON=win_bison lexer_test
```

Run the lexer with a sample program:

```bash
./lexer_test tests/valid/sample_program.mc
```

Run the lexical test cases:

```bash
mingw32-make FLEX=win_flex BISON=win_bison test
```

Clean generated build files:

```bash
mingw32-make clean
```

## Testing

The lexer currently includes tests for:

- Valid source code and token recognition
- Invalid identifiers and malformed numeric literals
- Invalid characters and operators
- Unterminated block comments

The existing lexer test suite has passed all three test cases.

Additional parser, syntax error, semantic error, and TAC generation tests will be added as the remaining modules are implemented.

## Development Progress

| Module | Status |
|---|---|
| Project structure and setup | Completed |
| Language specification | Completed |
| Lexical Analyzer | Completed and tested |
| Syntax Analyzer (Bison) | In Progress |
| Abstract Syntax Tree | Planned |
| Symbol Table | Planned |
| Semantic Analyzer | Planned |
| TAC Generator | Planned |
| Final testing and documentation | Planned |

## Project Documentation

- [Language Specification](docs/language_spec.md)
- [Project Roadmap](docs/ROADMAP.md)
- [AI Usage Log](docs/AI_USAGE_LOG.md)

## Team

**Group Members:**
- Sayma Rahman
- Md Salman

## Repository

[Lexora Compiler – GitHub Repository](https://github.com/sayma29/lexora-compiler)

## Academic Project

This project is developed for the **Compiler Construction Lab** as part of the B.Sc. in Computer Science and Engineering program at Metropolitan University.

---
