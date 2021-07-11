---
sidebar_position: 1
---

# Introduction

Murmur - *you may also refer to it by "Mur" or "ECMPL-2021" (EnderCommunity-Maintained Programming Language -- 2021)* - is an experimental programming language.

The whole goal of Mur is to offer everyone an easy language to learn and write in with no performance costs.
Mur code compiles down to C code, which is then compiled to machine code.

>***"Mur" is still not functional, this is all just some pitches and some not-even-close-to-half-baked code.***

The file extension of Mur files is `.mur`, and the file extension of Mur module files is `.murm`.

You can learn how to write any application using the Mur programming language, and how Mur's compiler works! All the necessary documentation for both the language and the compiler is available here.

:::danger Fatal
Do NOT use Mur for any important stuff, it's an experimental programming language.
:::

:::info Note
This documentation is not complete, as Mur is not really complete either right now.
:::

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

### Extensions

You'll find instructions on how to use the provided extensions for the perfect development environment.

#### Visual Studio Code

Copy the extension folder *`/murmur-vsc`* to the extension directory.

*The extension folder directory on Windows is `%USERPROFILE%\.vscode\extensions`*.

*The extension folder directory on  Mac/Linux is `$HOME/.vscode/extensions`*.

## Contributing

Everyone is welcomed to contribute to this project in any way they want. (e.g. help code the compiler, or help with the pitching process)

If you want to contribute, make sure that you've properly set up the development environment. And, when you push your changes to the compiler, make sure to change back the `.vscode` compiler values, and don't change the environment variables in `./compiler/envi.h`.

## License

:::note Note
We want you to understand that we chose this license because we believe that no one should profit from selling compilers for programming languages. We also chose this license because we want anyone who has a better vision for this programming language or compiler to not be denied the right to do whatever they want, without denying others the same opportunity for the potential future project/vision.
:::

![License](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Murmur is licensed under a [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-nc-sa/4.0/).
