---
sidebar_position: 1
---

# Introduction

In every programming language, there's a need for something to translate and compile the language's code into machine code so your machine can understand and execute your code. This is where compilers come in!

In most programming languages, compilers directly compile your input code into machine code. But Mur is a bit different. Mur's compiler compiles Mur code into C code. Your output C code then gets compiled into machine code using your preferred C compiler. (We'd recommend you use a well-known C compile)

:::note Note
Mur's compiler is currently completely written in C. That does not mean you cannot use other languages to add more features to the compiler. If you find any new integration to be useful, do not hold back.
:::

:::caution Caution
Mur's compiler is not final. If you have any suggestions to improve this compiler, do not hesitate to [open an issue on GitHub](https://github.com/EnderCommunity/Murmur/issues/new/choose).
:::

## Why Compile to C?

The reasoning behind us choosing to compile Mur code to C code is quite simple. Compiling code into C code is much easier than directly compiling code into machine code. And, to add on top of that, C has proven to be solid and useful since [its release back in 1972](https://en.wikipedia.org/wiki/C_(programming_language)), so it'd be pretty safe for us to use it.

It only seems logical (*to us*) to compile Mur code into C code. Mur is meant to be maintained and powered by the open-source community. The easier it is to write the compiler, the more likely more people will jump in to help build this language.

Of course, we might end up scratching the whole idea of compiling Mur code into C code if any complication happens along the way. That would not be the end of the compiler that has already been built, as the Mur-to-C compiling process is only one stage of many that the compiler goes through for you to end up with working machine code.

## The Compiling Process

Like any compiler, Mur's compiler has multiple stages of compiling:

- The preprocessor
- The lexer
- The parser
- The optimisor
- The evaluator

:::note Note
So far, we only started working on the preprocessor and the lexer.
:::

## Compiler input

For now, you can send input to the compiler in two ways:

- *By drag-dropping the desired file on the `Mur.exe` executable.*

- *By starting the `Mur.exe` executable and typing in the path of the desired file.*

## Compiler output

As of now, the compiler will output 3 files: `.log`, `.tmp`, and `.lxic`.

- The `.tmp` file contains the output of the preprocessor.
- The `.lxic` file contains the output of the lexer.
- *The `.prs` file contains the output of the parser.*
- *The `.opt` file contains the output of the optimisor.*
- *The `.val` file contains the output of the evaluator.*
- *The `.c` file contains the final C output.*
- The `.log` file contains logs from the compiler.
- *The `.opf` file contains general warnings and errors.*

Also, in case of an error, the compiler will exit with an error-specific code.

:::note Note
We'll work on an error code system soon...
:::
