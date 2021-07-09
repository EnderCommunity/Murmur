![logo](./github/photos/logo_withname.png)

![Downloads](https://img.shields.io/github/downloads/EnderCommunity/Murmur/total?color=blue) ![EnderFramework Repository Size](https://img.shields.io/github/repo-size/EnderCommunity/Murmur?label=Repository%20Size&color=blue) ![EnderFramework Top Language](https://img.shields.io/github/languages/top/EnderCommunity/Murmur?color=blue) [![Issues](https://img.shields.io/github/issues/EnderCommunity/Murmur?color=blue)](https://github.com/EnderCommunity/Murmur/issues) [![Bugs](https://img.shields.io/github/issues/EnderCommunity/Murmur/bug?label=Bugs)](https://github.com/EnderCommunity/Murmur/issues?q=label%3A%22bug%22) [![Help wanted!](https://img.shields.io/github/issues/EnderCommunity/Murmur/help%20wanted?label=Help%20Wanted&color=red)](https://github.com/EnderCommunity/Murmur/issues?q=label%3A%22help+wanted%22) [![EnderFramework Discord Invite](https://img.shields.io/discord/756472096099663954?color=blue&label=Discord%20Server&logo=discord&logoColor=white)](https://discord.com/invite/rWbtez6) [![Twitter](https://img.shields.io/twitter/follow/_EnderCommunity?style=social)](https://twitter.com/intent/follow?screen_name=EnderAdel) [![EnderAdel](https://img.shields.io/github/followers/adel-sbeh?label=The%20Original%20Creator&style=social)](https://github.com/adel-sbeh/)

Murmur - *you may also refer to it by "Mur" or "ECMPL-2021" (EnderCommunity-Maintained Programming Language -- 2021)* - is an experimental programming language. *Mur* code compiles down to C code, which is then compiled to machine code.

>***"Mur" is still not functional, this is all just some pitches and some not-even-close-to-half-baked code.***

The file extension of *Mur* files is *`.mur`*, and the file extension of *Mur* module files is *`.murm`*. (Which stands for *`"Murmur Module"`*)

## The Development Environment

To start working with *Mur* on Windows, you need to [download MSYS2](https://www.msys2.org/#installation). And it's also recommended that you use [Visual Studio Code](https://code.visualstudio.com/). You need to install all the available features in *MSYS2*. And, in case you decided to use *Visual Studio Code*, make sure to [install the C/C++ extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools). Also, make sure to [add the gcc compiler to your PATH](https://www.youtube.com/watch?v=mQra00mT3Dg)!

Execute the folllowing commands in your *MSYS2* console:

```cmd
pacman -Syu
pacman -S mingw-w64-x86_64-toolchain
pacman -S mingw-w64-x86_64-pcre
pacman -S mingw-w64-x86_64-pcre2
```

When you're done with the set up process, make sure that the `C_COMPILER_EXECUTABLE_DIR` enviroment variable is set to your `gcc.exe` executable! You might also want to make sure that the `.vscode` compiler path is correct.

## Contributing

Everyone is welcomed to contribute to this project in any way they want. (e.g. help code the compiler, or help with the pitching process)

If you want to contribute, make sure that you've properly set up the development environment. And, when you push your changes to the compiler, make sure to change back the `.vscode` compiler values, and don't change the environment variables in `./compiler/envi.h`.

## The Compiling Process

There are multiple stages of compiling: The preprocessor, the lexer, the parser, and the evaluator.

So far, we only started working on the preprocessor and the lexer. Here's how each of these two are gonna work:

### The Preprocessor

The preprocessor is the bit of code that prepares the source code for the compiler to work on. It's supposed to check the header for flags, and analyse the preprocessor methods outside of *groups*. It also cleans unnecessary whitespaces and comments.

For now, these are the planned preprocessor methods:

```mur
using system.io; //Tell the compiler that the program is going to use the "system"
                 //input/output library

import "path/to/my/file.mur"; //Import another Murmur file!

define ZERO 0; //You can use the `define` function to define a variable that
               //will be replaced by the provided value before the execution
               //of this code

setsize int 2; //Set a custom size of memory (in bytes) to allocate for any type
setsize double 10; //You can do the same with all the built-in types

import "path/to/my/file2.mur"; //You need to pay attention to the importing order
```

Only the `import` method is gonna actually be processed before the lexer!

```tmp
[{main},4;1]['import']
[{main>'path/to/my/file.mur'},1;1]... //The code in "path/to/my/file.mur"
[{main>'path/to/my/file.mur'},2;1]...
```

The available header flags are:

- ***no-comments*** - Tells the compiler to not look for comments in your code

- ***no-preprocessor-methods*** - Tells the compiler to not look for preprocessor methods in your code

- ***skip-processor*** - Tells the compiler to not analyse your code, and to jump to the c-compiling stage

- ***allow-separate*** - Tells the compiler that you're gonna use the `separate` super-method. (The separate super-method allows you to inject C code in your Mur file)

> It's important to note that some of these flags are only for debugging, and they may get removed in the future.

### The Lexer

The lexer is supposed to label all the code passed by the preprocessor.

Here's the labeling format:

```lixc
1000 `value` 0 0 0 0 | 0 0 0 0 <0.'file1'.'file2'> 0x000000000 1x000000000
```

Each row resembles a token!

- **1000** - This value is always of the length '4', and it always starts with the number one. It holds the token type.

| Value  | Environment Variable Name |   Type Name   |
| ------ | ------------------------- | ------------- |
|  1001  |       LEXER_SYMBOL        |    Symbol     |
|  1002  |       LEXER_STRING        |    String     |
|  1003  |        LEXER_CHAR         |   Character   |
|  1004  |       LEXER_NUMBER        |    Number     |
|  1005  |      LEXER_OPERATOR       |    Operator   |

- **\`...\`** - Anything between the two "\`" operators is the value of the token. *It's important to note that the start and end quotes will not be included in the values of chars and strings!*

- **0 0 0 0 | 0 0 0 0** - These eight numbers are always present, and their value only ranges from 0 to 9. They are used to provide the parser with extra information. The first four zeros hold shared values between different token types, and the other four zeros are type-specific.

| type | 1st | 2nd | 3rd | 4th | `\|` | 5th | 6th | 7th | 8th |
| --- | --- | --- | --- | --- | ---- | --- | --- | --- | --- |
| *all* | Whether this token is the first token in line or not. [0 - false, 1 - true]   | Whether there is whitespace before this token. [0 - false, 1 - true] | Whether there is whitespace after this token. [0 - false, 1 - true] | *none* [0] |  -   | -   | -   | -   | -   |
| Symbol |  *  |  *  |  *  |  *  |  -   | -   | -   | -   | -   |
| String |  *  |  *  |  *  |  *  |  -   | -   | -   | -   | -   |
| Character |  *  |  *  |  *  |  *  |  -   | -   | -   | -   | -   |
| Number |  *  |  *  |  *  |  *  |  -   | -   | -   | -   | -   |
| Operator |  *  |  *  |  *  |  *  |  -   | -   | -   | -   | -   |

(* - the same as the previously-described type)

- **<...>** - Anything between the "<" and ">" operators is descriptive information about the token value source file path. Each path is separated by a dot, and each file path should be contained in quotes (`'`). The 0 refers to the input file path.

An example of a correct path description is:

```lixc
<0.'./lib/cus.mur'.'./extr.mur'>
```

- **0x000000000** - The token value line in the source file. The "**0x**" part is used to recognise the start of this value, and it has no effect on the line number value. The numbers after the "**0x**" part represent the hex value of the line number, and this hex value is always 9 characters long.

- **1x000000000** - The token value column in the source file. The "**1x**" part is used to recognise the start of this value, and the rest of this value behaves the same as the previously-described hex value (*5 - 0x00...*).

## Compiler input

For now, you can send input to the compiler in two ways:

- *By drag-dropping the desired file on the `Mur.exe` executable.*

- *By starting the `Mur.exe` executable and typing in the path of the desired file.*

## Compiler output

As of now, the compiler will output 3 files: `.log`, `.tmp`, and `.lxic`.

- The `.log` file contains logs from the compiler.
- The `.tmp` file contains the output of the preprocessor.
- The `.lxic` file contains the output of the lexer.

Also, in case of an error, the compiler will exit with an error-specific code.

> *We'll work on an error code system soon...*

## Syntax and Functions

***Empty, check the provided `.mur` files for now!***

## Extensions

You'll find instructions on how to use the provided extensions for the perfect development environment.

### Visual Studio Code

Copy the extension folder *`/murmur-vsc`* to the extension directory.

*The extension folder directory on Windows is `%USERPROFILE%\.vscode\extensions`*.

*The extension folder directory on  Mac/Linux is `$HOME/.vscode/extensions`*.

## To-Do List

There are instructions for the building process of the compiler and libraries of Murmur:
*Follow the instructions in the `test.mur` file on how should the language work*

- [ ] *Research the best algorithms for an efficient memory-managment*
- [ ] *Write a compiler using C that compiles Murmur to C code*

# License

>We want you to understand that we chose this license because we believe that no one should profit from selling compilers for programming languages. We also chose this license because we want anyone who has a better vision for this programming language or compiler to not be denied the right to do whatever they want, without denying others the same opportunity for the potential future project/vision.

![License](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Murmur is licensed under a [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-nc-sa/4.0/).
