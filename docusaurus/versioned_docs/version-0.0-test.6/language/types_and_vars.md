---
sidebar_position: 2
---

# Types and Variables

Variables are symbols that work as placeholders for expressions and values. And, in Mur, variables have types.

## Defining Variables

To define a variable, you simply type in the type of the variable, followed by its name:

```mur
<type> Name;
```

You can assign a value to variables like this:

```mur
Name = <value>;
<type> Name2 = <value>;
```

## Types

There ar multiple default types of variables in Mur:

### Int

Integers are of the type `int`, and their size is usually set to 2-4 bytes.

### Float

Decimal numbers are of the type `float`, and their size is usually set to 2-4 bytes.

### Double

Long decimal numbers are of the type `double`, and their size is usually set to 8 bytes.

### Char

Characters are of the type `char`, and their size is usually set to 1 byte.

### String

Strings are of the type `string`, and their size is usually set to 2,048 byte.

### Bool

Booleans are of the type `bool`, and their size is usually set to 1 byte.

### File

Files in Mur have their own type, `file`. There is not specific limit to the size of the `file` type.
