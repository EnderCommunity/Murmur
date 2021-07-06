/*
All the expressions in Mur are gonna be:

syb: LEXER_SYMBOL
str: LEXER_STRING
chr: LEXER_CHAR
num: LEXER_NUMBER
op: LEXER_OPERATOR

val: all
none: void

assignment: <syb, "variable"> <op, "="> <val>, output: none
keyword: <syb, "gup:stms">
type: <syb, "gup:tps">
priority: <op, "("> ... <op, ")">, output: priority
operation: <num> <op, "math-related"> <num>, output: <num>
levelled_operation: <str>||<chr> + <str>||<chr>, output: <str>
declaration: <syb, "type"> <syb>, output: none
function_call: <syb, "function"> <op, "("> ... <op, ")">, output: <val>||none
function_levelled_call: <class_obj> <op, "."> <syb, "function"> <op, "("> ... <op, ")">, output: <val>||none
function_definition: <syb, "val:function"> <op, ":"> <op, ":"> <syb, "type"> <syb> <op, "("> ... <op, ")"> <op, "{"> ... <op, "}">, output: none
group_call: <syb, "group"> <op, ".">, output: <group_obj>
group_definition: <syb, "val:group"> <syb> <op, "{"> ... <op, "}">, output: none
class_call: <group_obj> <op, "."> <syb, "class">, output: <class_obj>
class_definition: <syb, "val:class"> <syb> <op, "{"> ... <op, "}">, output: none
constructor_definition: <syb, "val:function"> <op, ":"> <op, ":"> <syb, "val:constructor"> <syb> <op, "("> ... <op, ")"> <op, "{"> ... <op, "}">, output: <constructor_object>

*/