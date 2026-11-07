# Lexora Programming Language Specification

## 1. Introduction

Lexora is a mini programming language implemented as part of the Compiler Construction Lab Project.

The language specification follows the requirements provided in the course project manual. The compiler supports lexical analysis, syntax analysis, semantic analysis, symbol table management, and three-address code (TAC) generation.

## 2. Supported Data Types

The language supports the following data types:

- `int` – Integer values
- `float` – Floating-point values
- `bool` – Boolean values (`true` and `false`)

## 3. Keywords

The following keywords are supported:

- `int`
- `float`
- `bool`
- `if`
- `else`
- `while`
- `print`
- `true`
- `false`

## 4. Operators

### 4.1 Arithmetic Operators

- `+` – Addition
- `-` – Subtraction
- `*` – Multiplication
- `/` – Division
- `%` – Modulus

### 4.2 Relational Operators

- `<` – Less than
- `>` – Greater than
- `<=` – Less than or equal to
- `>=` – Greater than or equal to
- `==` – Equal to
- `!=` – Not equal to

### 4.3 Logical Operators

- `&&` – Logical AND
- `||` – Logical OR
- `!` – Logical NOT

## 5. Variable Declaration

Variables must be declared using one of the supported data types: `int`, `float`, or `bool`.

Example:

```c
int age;
float price;
bool isValid;
```

## 6. Assignment Statement

A value or expression can be assigned to a previously declared variable using the assignment operator `=`.

Example:

```c
int age;
age = 22;
```

## 7. Conditional Statements

The language supports `if` and `if-else` conditional statements.

Example:

```c
if (age > 18) {
    print age;
} else {
    print age;
}
```

## 8. Loop Statement

The language supports the `while` loop for repeated execution of statements while a condition is true.

Example:

```c
int i;
i = 0;

while (i < 5) {
    print i;
    i = i + 1;
}
```

## 9. Output Statement

The `print` statement is used to display an expression or variable.

Example:

```c
int a;
a = 10;
print a;
```

## 10. Blocks and Scope

The language supports nested blocks using curly braces `{ }`.

Variables declared inside a block belong to that block's scope and cannot be accessed outside it.

Example:

```c
int x;
x = 10;

if (x > 5) {
    int y;
    y = 20;
    print y;
}
```

## 11. Lexical Rules

The lexer recognizes the following elements:

- **Identifiers:** Must start with a letter or underscore, followed by letters, digits, or underscores.
- **Integer literals:** Whole-number constants.
- **Float literals:** Floating-point constants.
- **Boolean literals:** `true` and `false`.
- **Delimiters:** `{`, `}`, `(`, `)`, and `;`.
- **Comments:** Single-line and/or block comments are ignored by the lexer.
- **Whitespace:** Spaces, tabs, and newlines are ignored where appropriate.

Invalid tokens must produce lexical error messages with line numbers.

## 12. Sample Program

The following program demonstrates variable declaration, assignment, boolean values, a while loop, conditional statements, and print statements.

```c
int x;
int y;
bool flag;

x = 10;
y = 0;
flag = true;

while (x > 0) {
    y = y + x;
    x = x - 1;
}

if (flag == true) {
    print y;
} else {
    print x;
}
```

## 13. Compiler Output

The compiler will process the source program through the following stages:

1. Lexical Analysis
2. Syntax Analysis
3. Abstract Syntax Tree (AST) Construction
4. Symbol Table Management
5. Semantic Analysis
6. Three-Address Code (TAC) Generation

The final required output of the compiler is Three-Address Code (TAC).