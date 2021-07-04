
<img alt="Murmur's Logo" src="./brand/logo.png" width="128">

# Murmur

Murmur - *you may also refer to it by "Mur" or "ECMSL-2021" (EnderCommunity Maintained Scripting Language - 2021)* - is an experimental programming language. ***It's still not even functional, this is all just a pitch of the language itself.*** *Mur* code compiles down to C code, which is then compiled to machine code.

The file extension of *Mur* files is *`.mur`*.

The file extension of *Mur* module files is *`.murm`*. (Which stands for *`"Murmur Module"`*)

## The Development Environment

To start working with *Mur* on Windows, you need to [download MSYS2](https://www.msys2.org/#installation). And it's also recommended that you use [Visual Studio Code](https://code.visualstudio.com/). You need to install all the available features in *MSYS2*. And, in case you decided to use *Visual Studio Code*, make sure to [install the C/C++ extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools). Also, make sure to [add the gcc compiler to your PATH](https://www.youtube.com/watch?v=mQra00mT3Dg)!

Execute the folllowing commands in your *MSYS2* console:

```cmd
pacman -Syu
pacman -S mingw-w64-x86_64-pcre
pacman -S mingw-w64-x86_64-pcre2
```

When you're done with the set up process, make sure that the `C_COMPILER_EXECUTABLE_DIR` enviroment variable is set to your `gcc.exe` executable! You might also want to make sure that the `.vscode` compiler path is correct.

## Contributing

Everyone is welcomed to contribute to this project in any way they want. (e.g. help code the compiler, or help with the pitching process)

If you want to contribute, make sure that you've properly set up the development environment. And, when you push your changes to the compiler, make sure to change back the `.vscode` compiler values, and don't change the environment variables in `./compiler/envi.h`.

## The Compiling Process (outdated)

This is a diagram of the current plan for the compiling process:

![plan.png](./github/photos/plan.svg)

## Compiler input

For now, you can send input to the compiler in two ways:

- *By drag-dropping the desired file on the `start.exe` executable.*

- *By starting the `start.exe` executable and typing in the path of the desired file.*

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
