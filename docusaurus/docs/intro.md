---
sidebar_position: 1
---

# Introduction

Mur is, like many other languages, an object-oriented and type-strict programming language. Mur depends on its own compiler to analyse and translate its code into C code. After that, it's all left for your C compiler to take care of the output code.

Mur is all about making it easier for developers to write code without compromising any runtime features with little-to-notice performance costs.

:::caution Caution
Mur is still NOT functional yet!
:::

The file extension of Mur files is `.mur`, and the file extension of Mur module files is `.murm`.

You can learn how to write any application using the Mur programming language, and how Mur's compiler works! All the necessary documentation for both the language and the compiler is available here.

:::danger Fatal
Do NOT use Mur for any important stuff, it's an experimental programming language.
:::

:::info Info
This documentation is not complete, as Mur is not really complete either right now.
:::

## The Development Environment (outdated)

To start working with *Mur* on Windows, you need to [download MSYS2](https://www.msys2.org/#installation). And it's also recommended that you use [Visual Studio Code](https://code.visualstudio.com/). You need to install all the available features in *MSYS2*. And, in case you decided to use *Visual Studio Code*, make sure to [install the C/C++ extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools). Also, make sure to [add the gcc compiler to your PATH](https://www.youtube.com/watch?v=mQra00mT3Dg)!

Execute the folllowing commands in your *MSYS2* console:

```cmd
pacman -Syu
:: Run these commands only if the compiler fails
::pacman -S mingw-w64-x86_64-toolchain
::pacman -S mingw-w64-x86_64-pcre
::pacman -S mingw-w64-x86_64-pcre2
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

If you want to contribute, make sure that you've properly set up the development environment. And, before you push your changes to [our repository](https://github.com/EnderCommunity/Murmur), make sure not to change the files inside of the `/.vscode` folder & the environment variables (in `./compiler/envi.h`).

## License

Murmur is licensed under a [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](https://mur-lang.org/legal/mur/license).
