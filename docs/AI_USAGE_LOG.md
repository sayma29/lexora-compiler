# AI Usage Log: Lexora

Tool used: Claude (Anthropic). Section 10 of the project manual permits AI tools.
This log lists the prompts actually sent, in order, and what the AI produced for each.
Add new rows as the project continues.

| # | Prompt (verbatim) | What the AI produced |
|---|---|---|
| 1 | "This is your compiler project manual. Add front-end(local host page) and reacquired backend for that. My ma'am gave me that now I have to make a compiler project like this.. give me the project name first and what it will does" | Read the manual. Proposed a project concept and architecture: Flex/Bison compiler in C, a small Node.js server, and a localhost web page with tabs for each phase. |
| 2 | "One of my friends is doing it...give Mr another one for compiler project" (with a screenshot of the class project-name list) | Suggested a project name not already taken in the list. |
| 3 | "Give me the name of project" | Name suggestion. |
| 4 | "Another" | Name suggestion. |
| 5 | "More" | Name suggestions. |
| 6 | "Unique name for compiler project that I will be doing like you will give me" | Name suggestions. |
| 7 | "Quillium mean" | Explained where a suggested name came from. |
| 8 | "Ok quillium" | Started building: checked and installed Flex, created the project folder structure, wrote the diagnostics module (`src/diag`) and the AST module (`src/ast`). |
| 9 | "I have to give my github link to teacher for this project what repo should I make" | (see next row) |
| 10 | "no i have given the name lexora..now give me everything that i have to do from starting to last...also she asked for ai prompts that im using for this project...can you give me that later which prompt i used for you like she will judge me if i done it all from you" | Renamed the project to Lexora, wrote `docs/ROADMAP.md` (full checklist) and this log. Suggested repo name `lexora-compiler`. |
| 11 | (pasted the terminal output of a git commit and push) "this is how much i have created" | Told me what was still missing from the GitHub setup (.gitignore, README, collaborators) and suggested installing Flex and Bison with MSYS2. |
| 12 | "my maam gave me this files to install bison flex..then why i used msys2" (with `win_flex_bison-latest.zip` and `mingw-get-setup.exe`) | Explained that the MSYS2 suggestion was a guess from the terminal prompt, and gave install steps for the teacher's tools. |
| 13 | "i will use my maams tools" | Wrote the lexer stage: `src/lexer/lexer.l`, the test driver, `Makefile`, `.gitignore`, and three test programs with expected outputs. |

## Work done by the AI so far
- Project concept and architecture proposal
- Name suggestions
- Starter code: `src/diag/` (error and token logging) and `src/ast/` (syntax tree and printers)

## Work done by the team
(Fill in honestly as you go: which modules each member wrote, edited, tested and understood.)

## Prompts to add later
(Append each new prompt you send to any AI tool, with a one-line note on what you did with the answer.)
