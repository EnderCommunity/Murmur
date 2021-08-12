---
sidebar_position: 4
---

# Low-Level-Methods

Low-level methods are methods that are called outside of groups. They are always present in the [lowest scope of your program](./structure_and_scopes#root-level-scope) of the program.

## Outer-Methods

### Define

```mur
define <name> <value>;
```

The `define` outer-method is used to define a constant.

### SetSize

```mur
setsize <type> <size>;
```

The `setsize` outer-method is used to set a custom memory allocation size for the built-in types.

## Preprocessor Methods & Super-Methods

Preprocessor Methods are methods that are processed in the preprocessor stage. They are separated into two types:

- Methods
- Super-Methods

### Preprocessor Methods

Preprocessor Methods have a normal syntax that is similar to the rest of Mur's features. You can't really tell apart the normal built-in functions and the preprocessor (normal) methods.

For now, these are the planned preprocessor methods:

#### Import

```mur
import <file_path>;
```

The `import` preprocessor method is used to inject code from other files. It's important for the compiler to inject this code before the parsing stage so there would not be any need to recall any previously-used compiler functions down the line.

#### Using

```mur
using <lib_path>;
```

The `using` preprocessor method is very similar to the `import` preprocessor method, except it's used to call built-in libraries.

### Preprocessor Super-Methods

Preprocessor Super-Methods have their own syntax. They are always started with the specific character '**#**'.

For now, these are the planned preprocessor methods:

#### Header

```mur
#header <arg> <arg>...
```

The `header` super-method is used to pass flags to the compiler! The currently-available header flags are:

- ***no-comments*** - Tells the compiler to not look for comments in your code
- ***no-preprocessor-methods*** - Tells the compiler to not look for preprocessor methods in your code
- ***allow-separate*** - Tells the compiler that you're gonna use a `separation-zone`. (The separation-zone allows you to inject C code in your Mur files)

:::caution Caution
The ***allow-separate*** flag is disabled by default. You need to change the value of the environment variable `ENABLE_ALLOW_SEPARATE_FLAG` to enable this functionality!
:::

:::note Note
Some of these flags are only for debugging, and they may get removed in the future.
:::

:::note Note
The `header` super-method only works if it's used in the first line of your Mur code file!
:::

#### Separate

```mur
<<<
/* Do some weird C-wizardry */
>>>
```

The `separate` super-method is used to inject C code into your Mur files. It has been introduced for a special need in libraries.

:::caution Caution
You should never use the `separate` super-method, as it's only intended for libraries.
:::

:::danger Fatal
The `separate` super-method is not stable, and it's not monitored by the compiler!
:::
