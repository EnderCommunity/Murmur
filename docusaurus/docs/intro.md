---
sidebar_position: 1
---

# Introduction

![Downloads](https://img.shields.io/github/downloads/EnderCommunity/Murmur/total?color=blue) ![EnderFramework Repository Size](https://img.shields.io/github/repo-size/EnderCommunity/Murmur?label=Repository%20Size&color=blue) ![EnderFramework Top Language](https://img.shields.io/github/languages/top/EnderCommunity/Murmur?color=blue) [![Issues](https://img.shields.io/github/issues/EnderCommunity/Murmur?color=blue)](https://github.com/EnderCommunity/Murmur/issues) [![Bugs](https://img.shields.io/github/issues/EnderCommunity/Murmur/bug?label=Bugs)](https://github.com/EnderCommunity/Murmur/issues?q=label%3A%22bug%22) [![Help wanted!](https://img.shields.io/github/issues/EnderCommunity/Murmur/help%20wanted?label=Help%20Wanted&color=red)](https://github.com/EnderCommunity/Murmur/issues?q=label%3A%22help+wanted%22) [![EnderFramework Discord Invite](https://img.shields.io/discord/756472096099663954?color=blue&label=Discord%20Server&logo=discord&logoColor=white)](https://discord.com/invite/rWbtez6) [![Twitter](https://img.shields.io/twitter/follow/_EnderCommunity?style=social)](https://twitter.com/intent/follow?screen_name=EnderAdel) [![EnderAdel](https://img.shields.io/github/followers/adel-sbeh?label=The%20Original%20Creator&style=social)](https://github.com/adel-sbeh/)

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

>We want you to understand that we chose this license because we believe that no one should profit from selling compilers for programming languages. We also chose this license because we want anyone who has a better vision for this programming language or compiler to not be denied the right to do whatever they want, without denying others the same opportunity for the potential future project/vision.

![License](https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png)

Murmur is licensed under a [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-nc-sa/4.0/).
