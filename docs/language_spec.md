
# Lexora Programming Language Specification

## 1. Introduction
Lexora is a simple custom programming language designed for learning compiler construction.

## 2. Supported Data Types
- int
- float
- bool

## 3. Keywords
- int
- float
- bool
- if
- else
- while
- print
- true
- false

## 4. Operators

### Arithmetic Operators
+  -  *  /  %

### Relational Operators
<  >  <=  >=  ==  !=

### Logical Operators
&&  ||  !

## 5. Variable Declaration
Variables must be declared with a data type.

Example:
```c
int age = 22;
float price = 25.5;
bool isValid = true;
```

## 6. Conditional Statement
Lexora supports if-else statements.

Example:
```c
if (age > 18) {
    print(age);
} else {
    print(0);
}
```

## 7. Loop Statement
Lexora supports while loops.

Example:
```c
int i = 0;
while (i < 5) {
    print(i);
    i = i + 1;
}
```

## 8. Output Statement
The print statement displays an expression.

Example:
```c
print(10);
print(age);
```

## 9. Comments
Comments and whitespace are ignored by the lexer.
