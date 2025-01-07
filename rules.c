/*
1 = {RULE_PROGRAM, $}
2 = {RULE_SUBPROGRAMS_, RULE_MAIN, BEGIN, STMTS, END, PROGRAM}
3 = {MAIN, LPAREN, RULE_EXP, RPAREN}
4 = {CONST, RULE_TYPE, RULE_ASSIGN}
5 = {RULE_TYPE, RULE_ASSIGN}
6 = {RULE_REGISTER_DECL}
7 = {INT}
8 = {FLOAT}
9 = {BOOL}
10 = {CHAR}
11 = {STRING}
12 = {ID, RULE_ARRAY_DECL, ASSIGN, RULE_ASSIGN_}
13 = {RULE_EXP, SEMICOLON}
14 = {CCHAR, SEMICOLON}
15 = {CSTRING, SEMICOLON}
16 = {CARRAY, SEMICOLON}
17 = {LBRACE, RULE_SIZE, RBRACE, RULE_ARRAY_DECL}
18 = {RULE_EXP}
19 = {REGISTER, RULE_TYPE, ID, SEMICOLON}
20 = {CINT}
21 = {CFLOAT}
22 = {CBOOL}
23 = {ID, RULE_O_}
24 = {RULE_LIT}
25 = {CALL, ID, LPAREN, RULE_EXPS_, RPAREN}
26 = {LBRACE, RULE_EXP, RBRACE, RULE_O_}
27 = {RULE_O}
28 = {PLUS, RULE_O}
29 = {MINUS, RULE_O}
30 = {LPAREN, RULE_EXP, RPAREN}
31 = {RULE_AU}
32 = {RULE_OP, RULE_AP_}
33 = {POWER, RULE_AP}
34 = {RULE_AP, RULE_AF_}
35 = {TIMES, RULE_AF}
36 = {DIVIDE, RULE_AF}
37 = {RULE_AF, RULE_AT_}
38 = {PLUS, RULE_AT}
39 = {MINUS, RULE_AT}
40 = {RULE_AT, RULE_R_}
41 = {LESSTHAN, RULE_AT}
42 = {GREATERTHAN, RULE_AT}
43 = {LESSTHANOREQUAL, RULE_AT}
44 = {GREATERTHANOREQUAL, RULE_AT}
45 = {EQUALS, RULE_AT}
46 = {NOTEQUAL, RULE_AT}
47 = {RULE_R}
48 = {NOT, RULE_R}
49 = {RULE_LU, RULE_LC_}
50 = {AND, RULE_LU, RULE_LC_}
51 = {RULE_LC, RULE_EXP_}
52 = {OR, RULE_LC, RULE_EXP_}
53 = {RULE_EXP, COMMA, RULE_EXPS_}
54 = {RULE_EXPS}
55 = {RULE_TYPE, ID, RULE_ARGS_}
56 = {COMMA, RULE_ARGS}
57 = {RULE_STMT, RULE_STMTS_}
58 = {RULE_STMTS}
59 = {RULE_VAR}
60 = {RULE_ASSIGN}
61 = {CALL, ID, LPAREN, RULE_EXPS_, RPAREN, SEMICOLON}
62 = {RULE_SUBPROGRAM}
63 = {RULE_IF}
64 = {RULE_SWITCH}
65 = {RULE_FOR}
66 = {RULE_LOOP}
67 = {RULE_WHEN}
68 = {RULE_UNLESS}
69 = {RULE_PRINT}
70 = {RULE_SUBPROGRAM, RULE_SUBPROGRAMS_}
71 = {RULE_SUBPROGRAMS}
72 = {RULE_FUNCTION}
73 = {RULE_PROCEDURE}
74 = {FUNCTION, RULE_TYPE, ID, LPAREN, RULE_ARGS_, RPAREN, BEGIN, RULE_STMTS, RULE_RETURN, END, ID}
75 = {PROCEDURE, ID, LPAREN, RULE_ARGS_, RPAREN, BEGIN, RULE_STMTS, RULE_RETURN, END, ID}
76 = {IF, RULE_EXP, RULE_STMTS_, RULE_ELIF_, RULE_ELSE, END, IF}
77 = {ELIF, RULE_EXP, RULE_STMTS_, RULE_ELIF_}
78 = {RULE_ELIF}
79 = {ELSE, RULE_STMTS_}
80 = {SWITCH, LPAREN, RULE_VAR, RPAREN, RULE_CASE, RULE_DEFAULT, END, SWITCH}
81 = {CASE, RULE_EXP, COLON, RULE_STMTS_, BREAK, SEMICOLON, RULE_CASE_}
82 = {RULE_CASE}
83 = {DEFAULT, COLON, RULE_STMTS_, BREAK, SEMICOLON}
84 = {FOR, LPAREN, RULE_ASSIGN, SEMICOLON, RULE_EXP, SEMICOLON, RULE_EXP, RPAREN, RULE_STMTS_, END, FOR}
85 = {LOOP, RULE_STMTS, END, LOOP}
86 = {EXIT, WHEN, RULE_EXP}
87 = {UNLESS, RULE_EXP, DO, RULE_STMT}
88 = {PRINT, LPAREN, RULE_PRINT_, RPAREN, SEMICOLON}
89 = {RULE_EXP}
90 = {CCHAR}
91 = {CSTRING}
92 = {CARRAY}
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tokens.h"

int* getRules(int n) {
    switch (n)
    {
    case 1:
        return (int[]){RULE_PROGRAM, END_OF_FILE, -1};
    case 2:
        return (int[]){RULE_SUBPROGRAMS_, RULE_MAIN, BEGIN, RULE_STMTS, END, MAIN, -1};
    case 3:
        return (int[]){MAIN, LPAREN, RULE_ARGS_, RPAREN, -1};
    case 4:
        return (int[]){CONST, RULE_TYPE, RULE_ASSIGN, -1};
    case 5:
        return (int[]){RULE_TYPE, RULE_ASSIGN, -1};
    case 6:
        return (int[]){RULE_REGISTER_DECL, -1};
    case 7:
        return (int[]){INT, -1};
    case 8:
        return (int[]){FLOAT, -1};
    case 9:
        return (int[]){BOOL, -1};
    case 10:
        return (int[]){CHAR, -1};
    case 11:
        return (int[]){STRING, -1};
    case 12:
        return (int[]){ID, RULE_ARRAY_DECL, ASSIGN, RULE_ASSIGN_, -1};
    case 13:
        return (int[]){RULE_EXP, SEMICOLON, -1};
    case 14:
        return (int[]){CCHAR, SEMICOLON, -1};
    case 15:
        return (int[]){CSTRING, SEMICOLON, -1};
    case 16:
        return (int[]){CARRAY, SEMICOLON, -1};
    case 17:
        return (int[]){LBRACE, RULE_SIZE, RBRACE, RULE_ARRAY_DECL, -1};
    case 18:
        return (int[]){RULE_EXP, -1};
    case 19:
        return (int[]){REGISTER, RULE_TYPE, ID, SEMICOLON, -1};
    case 20:
        return (int[]){CINT, -1};
    case 21:
        return (int[]){CFLOAT, -1};
    case 22:
        return (int[]){CBOOL, -1};
    case 23:
        return (int[]){ID, RULE_O_, -1};
    case 24:
        return (int[]){RULE_LIT, -1};
    case 25:
        return (int[]){CALL, ID, LPAREN, RULE_EXPS_, RPAREN, -1};
    case 26:
        return (int[]){LBRACE, RULE_EXP, RBRACE, RULE_O_, -1};
    case 27:
        return (int[]){RULE_O, -1};
    case 28:
        return (int[]){PLUS, RULE_O, -1};
    case 29:
        return (int[]){MINUS, RULE_O, -1};
    case 30:
        return (int[]){LPAREN, RULE_EXP, RPAREN, -1};
    case 31:
        return (int[]){RULE_AU, -1};
    case 32:
        return (int[]){RULE_OP, RULE_AP_, -1};
    case 33:
        return (int[]){POWER, RULE_AP, -1};
    case 34:
        return (int[]){RULE_AP, RULE_AF_, -1};
    case 35:
        return (int[]){MULTIPLY, RULE_AF, -1};
    case 36:
        return (int[]){DIVIDE, RULE_AF, -1};
    case 37:
        return (int[]){RULE_AF, RULE_AT_, -1};
    case 38:
        return (int[]){PLUS, RULE_AT, -1};
    case 39:
        return (int[]){MINUS, RULE_AT, -1};
    case 40:
        return (int[]){RULE_AT, RULE_R_, -1};
    case 41:
        return (int[]){LESSTHAN, RULE_AT, -1};
    case 42:
        return (int[]){GREATERTHAN, RULE_AT, -1};
    case 43:
        return (int[]){LESSTHANOREQUAL, RULE_AT, -1};
    case 44:
        return (int[]){GREATERTHANOREQUAL, RULE_AT, -1};
    case 45:
        return (int[]){EQUALS, RULE_AT, -1};
    case 46:
        return (int[]){NOTEQUAL, RULE_AT, -1};
    case 47:
        return (int[]){RULE_R, -1};
    case 48:
        return (int[]){NOT, RULE_R, -1};
    case 49:
        return (int[]){RULE_LU, RULE_LC_, -1};
    case 50:
        return (int[]){AND, RULE_LU, RULE_LC_, -1};
    case 51:
        return (int[]){RULE_LC, RULE_EXP_, -1};
    case 52:
        return (int[]){OR, RULE_LC, RULE_EXP_, -1};
    case 53:
        return (int[]){RULE_EXP, COMMA, RULE_EXPS_, -1};
    case 54:
        return (int[]){RULE_EXPS, -1};
    case 55:
        return (int[]){RULE_TYPE, ID, RULE_ARGS_, -1};
    case 56:
        return (int[]){COMMA, RULE_ARGS, -1};
    case 57:
        return (int[]){RULE_STMT, RULE_STMTS_, -1};
    case 58:
        return (int[]){RULE_STMTS, -1};
    case 59:
        return (int[]){RULE_VAR, -1};
    case 60:
        return (int[]){RULE_ASSIGN, -1};
    case 61:
        return (int[]){CALL, ID, LPAREN, RULE_EXPS_, RPAREN, SEMICOLON, -1};
    case 62:
        return (int[]){RULE_SUBPROGRAM, -1};
    case 63:
        return (int[]){RULE_IF, -1};
    case 64:
        return (int[]){RULE_SWITCH, -1};
    case 65:
        return (int[]){RULE_FOR, -1};
    case 66:
        return (int[]){RULE_LOOP, -1};
    case 67:
        return (int[]){RULE_WHEN, -1};
    case 68:
        return (int[]){RULE_UNLESS, -1};
    case 69:
        return (int[]){RULE_PRINT, -1};
    case 70:
        return (int[]){RULE_SUBPROGRAM, RULE_SUBPROGRAMS_, -1};
    case 71:
        return (int[]){RULE_SUBPROGRAMS, -1};
    case 72:
        return (int[]){RULE_FUNCTION, -1};
    case 73:
        return (int[]){RULE_PROCEDURE, -1};
    case 74:
        return (int[]){FUNCTION, RULE_TYPE, ID, LPAREN, RULE_ARGS_, RPAREN, BEGIN, RULE_STMTS, RULE_RETURN, END, ID, -1};
    case 75:
        return (int[]){PROCEDURE, ID, LPAREN, RULE_ARGS_, RPAREN, BEGIN, RULE_STMTS, RULE_RETURN, END, ID, -1};
    case 76:
        return (int[]){IF, RULE_EXP, RULE_STMTS_, RULE_ELIF_, RULE_ELSE, END, IF, -1};
    case 77:
        return (int[]){ELIF, RULE_EXP, RULE_STMTS_, RULE_ELIF_, -1};
    case 78:
        return (int[]){RULE_ELIF, -1};
    case 79:
        return (int[]){ELSE, RULE_STMTS_, -1};
    case 80:
        return (int[]){SWITCH, LPAREN, RULE_VAR, RPAREN, RULE_CASE, RULE_DEFAULT, END, SWITCH, -1};
    case 81:
        return (int[]){CASE, RULE_EXP, COLON, RULE_STMTS_, BREAK, SEMICOLON, RULE_CASE_, -1};
    case 82:
        return (int[]){RULE_CASE, -1};
    case 83:
        return (int[]){DEFAULT, COLON, RULE_STMTS_, BREAK, SEMICOLON, -1};
    case 84:
        return (int[]){FOR, LPAREN, RULE_ASSIGN, SEMICOLON, RULE_EXP, SEMICOLON, RULE_EXP, RPAREN, RULE_STMTS_, END, FOR, -1};
    case 85:
        return (int[]){LOOP, RULE_STMTS, END, LOOP, -1};
    case 86:
        return (int[]){EXIT, WHEN, RULE_EXP, -1};
    case 87:
        return (int[]){UNLESS, RULE_EXP, DO, RULE_STMT, -1};
    case 88:
        return (int[]){PRINT, LPAREN, RULE_PRINT_, RPAREN, SEMICOLON, -1};
    case 89:
        return (int[]){RULE_EXP, -1};
    case 90:
        return (int[]){CCHAR, -1};
    case 91:
        return (int[]){CSTRING, -1};
    case 92:
        return (int[]){CARRAY, -1};
    case 93:
        return (int[]){DOT, ID, RULE_O_, -1};
    case 94:
        return (int[]){RETURN, RULE_EXP, SEMICOLON, -1};
    default:
        return (int[]){ERROR, -1};
    }
}