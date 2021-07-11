---
sidebar_position: 3
---

# Structure & Scopes

Your program consists of mutiple structures and scopes. Each Structure and scope has its own set of rules.

## Structure

Your program structure should be similar to this:

```mur
group MainFileName {

    class Program {

        function::int Main(){

            //Your code goes here...

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

## Program Structure

It's important to note that every Mur program should contain, by default, one group
