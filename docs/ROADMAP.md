# Lexora: Start-to-Finish Checklist

Project: Design and Implement a Mini Programming Language Compiler using Flex and Bison
(Compiler Construction Lab, 40% of the lab grade, replaces the lab final).
Confirm the exact deadline with your teacher. The manual says 31 July, with no extensions.

---

## Phase 0: Set up your tools
- [ ] Linux, or WSL on Windows (Ubuntu recommended by the manual)
- [ ] `sudo apt install flex bison gcc make git nodejs npm`
- [ ] Check: `flex --version`, `bison --version`, `gcc --version`, `node --version`

## Phase 1: GitHub (assessed directly, so do this first)
- [ ] Create ONE shared repo, e.g. **`lexora-compiler`**
- [ ] Add every teammate as a collaborator (Settings > Collaborators)
- [ ] Add `.gitignore` (ignore `lex.yy.c`, `y.tab.c`, `y.tab.h`, `*.o`, `node_modules/`, the compiled binary)
- [ ] Make the first commit with the folder structure from manual Section 8
- [ ] **Every member must commit**, regularly, with meaningful messages
      (good: "Add scope handling to symbol table", bad: "update", "fix")
- [ ] Never upload everything in one last-minute commit

## Phase 2: Split the work in the group
| Module | Rubric weight |
|---|---|
| Lexer (Flex) | 10% |
| Parser (Bison) | 15% |
| AST | 10% |
| Symbol table | 10% |
| Semantic analysis | 20% |
| TAC generation | 15% |
| Docs and report | 10% |
| Presentation and demo | 10% |

Give each member one or two modules plus part of the docs. Everyone must be able to explain ALL modules in the viva.

## Phase 3: Build the compiler (in this order)
1. [ ] **Lexer**: keywords, identifiers, int/float/bool literals, operators, delimiters, comments discarded, invalid tokens reported with line number
2. [ ] **Grammar (CFG)**: write it on paper first, then in Bison; unambiguous, with operator precedence
3. [ ] **Parser**: syntax errors with line numbers, plus basic recovery using Bison's `error` token
4. [ ] **AST**: nodes for program, block, declaration, assignment, if, while, print, binary and unary ops; a readable text printer
5. [ ] **Symbol table**: name, type, scope, line declared; nested scopes
6. [ ] **Semantic analyzer**: undeclared variable, redeclaration, scope violation, type mismatch, invalid assignment, invalid expression
7. [ ] **TAC generator**: arithmetic, relational/logical, if / if-else / while with labels and jumps, print
8. [ ] **Makefile**: `make` builds everything
9. [ ] **Web page and backend** (the bonus GUI feature): a small Node.js server calls the compiler, and a localhost page shows tokens, AST, symbol table, TAC and errors

## Phase 4: Tests (manual Section 15)
Put these in `tests/`, each paired with its expected output:
- [ ] At least 1 non-trivial valid program that compiles through to TAC
- [ ] At least 1 lexical error program (invalid token)
- [ ] At least 1 syntax error program
- [ ] 1 program for EACH semantic rule: undeclared use, redeclaration, scope violation, type mismatch, invalid assignment, invalid expression

## Phase 5: Documentation
- [ ] `README.md`: summary, build steps, run steps, team list, feature list
- [ ] `examples/`: a few sample programs
- [ ] Project report in `docs/`, using the chapters in manual Section 12:
      Introduction, Objectives, Language Specification (with CFG), Compiler Architecture, Lexer Design, Parser Design, AST, Semantic Analysis, Symbol Table, Intermediate Code, Challenges, Testing, Conclusion, References
- [ ] Cite every external resource and mention your AI usage

## Phase 6: Submission pack (Section 11)
- [ ] Source code
- [ ] GitHub repo link (shows commits from all members)
- [ ] README and project report
- [ ] Presentation slides
- [ ] Sample inputs and their outputs
- [ ] Screenshots of successful runs AND of error handling
- [ ] Exact build and run commands
- [ ] Optional: a short screen-recording video

## Phase 7: Presentation and viva
- [ ] Show the pipeline diagram and walk through each phase
- [ ] Live demo of one valid and one invalid program
- [ ] Show lexical, syntax and semantic errors being caught
- [ ] Show TAC output
- [ ] Talk about challenges and lessons learned
- [ ] Be ready for the teacher to type a program on the spot
- [ ] **Each member practices explaining every file.** The viva is a pass/fail gate that can scale your marks.

## AI usage (manual Section 10)
AI is allowed. You must understand every line you submit. Keep `docs/AI_USAGE_LOG.md` up to date as you go.
