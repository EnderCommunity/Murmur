---
sidebar_position: 3
---
# The Lexer

The lexer is supposed to label all the your code.

## Lexer Input

The lexer receives the `.tmp` file passed to the preprocessor, it then start processing the whole file content.

## Lexer Output

The output of the lexer is a `.lxic` file.

Here's the labeling format:

```murlixc
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
