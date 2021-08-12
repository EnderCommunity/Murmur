---
sidebar_position: 3
---

# Structure & Scopes

Your program consists of mutiple structures and scopes. Each Structure and scope has its own set of rules.

## Structure

It's important to note that every Mur program main file should contain, by default, one group named after the main file name, one class named `Program`, and one function named `Main`. So, for example, the start file `MyProject.mur` should contain the following code:

```mur
group MyProject {

    class Program {

        function::int Main(string[] envi, int length){

            //Your code goes here...

            return 0;

        }

    }

}
```

### Groups

You can only define groups at the [root-level-scope](#root-level-scope). To define a group, you simply use the `group` keyword:

```mur
group Name {
    ...
}
```

Each group contains a scope of its own, and that scope is called a [group-level-scope](#group-level-scope).

### Classes

You can only define classes at the group-level-scope. To define a class, you simply use the `class` keyword:

```mur
class Name {
    ...
}
```

Each class contains a scope of its own, and that scope is called a [class-level-scope](#class-level-scope).

### Functions

You can only define functions at the class-level-scope. To define a function, you simply use the `function` keyword, followed by the return type of the function:

```mur
function::<type> Name {
    ...
}
```

Each class contains a scope of its own, and that scope is called a [class-level-scope](#class-level-scope).

## Scopes

Scopes are different access areas of your program structure. There are 4 different scopes:

### Root-Level-Scope

This scope can only contain [Low-Level-Methods](./otrmethods) and groups.

### Group-Level-Scope

This scope can only contain classes.

### Class-Level-Scope

This scope can only contain variables and functions.

### Function-Level-Scope

This scope can only contain variables, functions, and super-methods.

## The seperation zone

The seperation zone is a zone that is contained between the opening quote `<<<` and the closing quote `>>>`. This zone is not touched or processed by Mur's compiler. Only C's Compiler can access this zone. This zone is used by libraries to build Mur native functions.

:::caution Caution
Only libraries have the ability to access the seperation zone **by default**.
:::
