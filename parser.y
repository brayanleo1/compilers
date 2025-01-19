%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Symbol {
    char id[64];         // Variable/Function name
    char type[16];       // Type of the symbol
    int depth;           // Scope depth
    int isFunction;      // 1 for functions, 0 otherwise
    struct Symbol *next; // Pointer to the next symbol
} Symbol;

Symbol *symbolTable = NULL;
int currentDepth = 0;

// Function prototypes
void addSymbol(const char *id, const char *type, int isFunction);
const char *getSymbolType(const char *id);
void removeSymbolsAtDepth(int depth);
void yyaccerror(const char *msg);
const char *isFunc(const char *id);

extern int yylex();
%}

// Token attributes
%union {
    char *str; // For IDs and type strings
}


%token <str> ID CINT CFLOAT CBOOL CCHAR CSTRING CARRAY
%token <str> INT FLOAT BOOL CHAR GRAPH STRING CONST REGISTER
%token <str> MAIN T_BEGIN END IF ELIF ELSE SWITCH CASE DEFAULT FOR LOOP EXIT WHEN UNLESS PRINT
%token <str> NOT LBRACE RBRACE SEMICOLON COMMA COLON DO
%token <str> TYPE BREAK PROCEDURE FUNCTION RETURN DOT ASSIGN
%token <str> LBRACKET RBRACKET CALL PROGRAM ERROR

%left <str> OR AND
%left <str> PLUS MINUS MULTIPLY DIVIDE

%right <str> POWER

%nonassoc <str> LESSTHAN GREATERTHAN LESSTHANOREQUAL GREATERTHANOREQUAL EQUALS NOTEQUAL
%nonassoc <str> LPAREN RPAREN NOT UNIPLUS UNIMINUS

%start RULE_PROGRAM

%type <str> RULE_MAIN RULE_VAR RULE_TYPE RULE_ASSIGN RULE_ASSIGN_ RULE_ARRAY_DECL RULE_REGISTER_DECL RULE_EXPS RULE_LIT RULE_O RULE_O_ RULE_AU RULE_AP RULE_AF RULE_AT RULE_R RULE_R_ RULE_LU RULE_LC RULE_EXP RULE_ARGS RULE_STMTS RULE_STMT RULE_SUBPROGRAMS RULE_SUBPROGRAMS_ RULE_SUBPROGRAM RULE_FUNCTION RULE_RETURN RULE_PROCEDURE RULE_IF RULE_ELIF RULE_ELSE RULE_SWITCH RULE_CASE RULE_DEFAULT RULE_FOR RULE_LOOP RULE_WHEN RULE_UNLESS RULE_PRINT RULE_PRINT_


%%

RULE_PROGRAM       : RULE_SUBPROGRAMS_ RULE_MAIN {
    enterScope();
} T_BEGIN RULE_STMTS END MAIN {
    leaveScope();
}
              ;
RULE_MAIN          : MAIN LPAREN RULE_ARGS RPAREN
              ;
RULE_VAR           : CONST RULE_TYPE RULE_ASSIGN {
    addSymbol($3, $2, 0);
}
              | RULE_TYPE RULE_ASSIGN {
    addSymbol($2, $1, 0);
              }
              | RULE_REGISTER_DECL
              ;
RULE_TYPE          : INT     { $$ = "int"; }
              | FLOAT   { $$ = "float"; }
              | BOOL    { $$ = "bool"; }
              | CHAR    { $$ = "char"; }
              | GRAPH   { $$ = "graph"; }
              | STRING  { $$ = "string"; }
              ;
RULE_ASSIGN        : ID RULE_ARRAY_DECL ASSIGN RULE_ASSIGN_ SEMICOLON {
                    const char *idType = getSymbolType($1);
                    if (!idType) {
                        yyaccerror("Undeclared variable");
                    } else if (strcmp(idType, $4) != 0) {
                        yyaccerror("Type mismatch in assignment");
                    }
                    // So if it's accessing an value from an array, it should be an array
                    if (strstr($2, "array") && strcmp($4, "array") != 0) {
                        yyaccerror("Type mismatch in assignment");
                    }
                    // If it's an array of ints, but the value is not an int, it should be an error
                    if (strstr($2, "array") && strstr($4, "array") && strstr($4, "int") && !strstr($2, "int")) {
                        yyaccerror("Type mismatch in assignment");
                    }
                    // If it's an array of floats, but the value is an int, it's not an error as it can be casted
                    if (strstr($2, "array") && strstr($4, "array") && strstr($4, "float") && strstr($2, "int")) {
                        printf("Warning: Casting int to float\n");
                    }
                    // If it's an array of bools, but the value is not a bool, it should be an error
                    if (strstr($2, "array") && strstr($4, "array") && strstr($4, "bool") && !strstr($2, "bool")) {
                        yyaccerror("Type mismatch in assignment");
                    }
                    // If it's an array of chars, but the value is not a char, it should be an error
                    if (strstr($2, "array") && strstr($4, "array") && strstr($4, "char") && !strstr($2, "char")) {
                        yyaccerror("Type mismatch in assignment");
                    }
                    // If it's an array of strings, but the value is not a string or char, it should be an error
                    if (strstr($2, "array") && strstr($4, "array") && strstr($4, "string") && !strstr($2, "string") && !strstr($2, "char")) {
                        yyaccerror("Type mismatch in assignment");
                    }
                    // If it's an array of graphs, but the value is not a graph, it should be an error
                    if (strstr($2, "array") && strstr($4, "array") && strstr($4, "graph") && !strstr($2, "graph")) {
                        yyaccerror("Type mismatch in assignment");
                    }
                }
              ;
              ;
RULE_ASSIGN_       : RULE_EXP {
                    $$ = $1;
                }
              | CCHAR {
                    $$ = "char";
                }
              | CSTRING {
                    $$ = "string";
                }
              | CARRAY {
                    $$ = "array";
                }
              ;
RULE_ARRAY_DECL    : LBRACE RULE_EXP RBRACE RULE_ARRAY_DECL | 
              ;
RULE_REGISTER_DECL : REGISTER RULE_TYPE ID SEMICOLON
              ;
RULE_EXPS          : RULE_EXP | RULE_EXP RULE_EXPS 
              ;
RULE_LIT           : CINT { $$ = "int"; } | CFLOAT { $$ = "float"; } | CBOOL { $$ = "bool"; }
              ;
RULE_O             : ID RULE_O_ {
                    const char *idType = getSymbolType($1);
                    if (!idType) {
                        yyaccerror("Undeclared variable");
                    }
                    // if RULE_O_ isn't empty, it should be an array or register
                    if ($2) {
                        if (strcmp($2, "array") != 0 && strcmp($2, "register") != 0) {
                            yyaccerror("Type mismatch in variable access");
                        }
                    }
                    $$ = idType;
                }
              | RULE_LIT {
                    $$ = $1;
                }
              | LPAREN RULE_EXP RPAREN {
                    $$ = $2;
                }
              | CALL ID LPAREN RULE_EXPS RPAREN {
                    const char *idType = getSymbolType($2);
                    if (!idType) {
                        yyaccerror("Undeclared function");
                    }
                    // if it calls as a function but it's not a function or it's a procedure that doesn't return anything, it should be an error
                    if (!isFunc($2) || strcmp(idType, "void") == 0) {
                        yyaccerror("Function call error");
                    }

                    $$ = idType;
                }
              ;
RULE_O_            : LBRACKET RULE_EXPS RBRACKET RULE_O_ {
                    $$ = "array";
                }
              | DOT ID RULE_O_ {
                    $$ = "register";
                }
              ;
RULE_AU            : UNIPLUS RULE_AU {
                    if (strcmp($2, "int") != 0 && strcmp($2, "float") != 0) {
                        yyaccerror("Type mismatch in unary plus");
                    }
                    $$ = $2;
                }
              | UNIMINUS RULE_AU {
                    if (strcmp($2, "int") != 0 && strcmp($2, "float") != 0) {
                        yyaccerror("Type mismatch in unary minus");
                    }
                    $$ = $2;
                }
              | RULE_O {
                    $$ = $1;
                }
              ;
RULE_AP            : RULE_AP POWER RULE_AP {
                    if (strcmp($1, "int") != 0 && strcmp($1, "float") != 0) {
                        yyaccerror("Type mismatch in power operation");
                    }
                    if (strcmp($3, "int") != 0 && strcmp($3, "float") != 0) {
                        yyaccerror("Type mismatch in power operation");
                    }
                    // If it's an int ^ int, it should be an int
                    if (strcmp($1, "int") == 0 && strcmp($3, "int") == 0) {
                        $$ = "int";
                    } else {
                        $$ = "float";
                    }
                }
              | RULE_AU {
                    $$ = $1;
                }
              ;
RULE_AF            : RULE_AF MULTIPLY RULE_AF {
                    if (strcmp($1, "int") != 0 && strcmp($1, "float") != 0) {
                        yyaccerror("Type mismatch in multiply operation");
                    }
                    if (strcmp($3, "int") != 0 && strcmp($3, "float") != 0) {
                        yyaccerror("Type mismatch in multiply operation");
                    }
                    // If it's an int * int, it should be an int
                    if (strcmp($1, "int") == 0 && strcmp($3, "int") == 0) {
                        $$ = "int";
                    } else {
                        $$ = "float";
                    }
                }
              | RULE_AF DIVIDE RULE_AF {
                    if (strcmp($1, "int") != 0 && strcmp($1, "float") != 0) {
                        yyaccerror("Type mismatch in divide operation");
                    }
                    if (strcmp($3, "int") != 0 && strcmp($3, "float") != 0) {
                        yyaccerror("Type mismatch in divide operation");
                    }
                    // If it's an int / int, it should be an int as it rounds
                    if (strcmp($1, "int") == 0 && strcmp($3, "int") == 0) {
                        $$ = "int";
                    } else {
                        $$ = "float";
                    }
                }
              | RULE_AP {
                    $$ = $1;
                }
              ;
RULE_AT            : RULE_AT PLUS RULE_AF {
                    if (strcmp($1, "int") != 0 && strcmp($1, "float") != 0) {
                        yyaccerror("Type mismatch in plus operation");
                    }
                    if (strcmp($3, "int") != 0 && strcmp($3, "float") != 0) {
                        yyaccerror("Type mismatch in plus operation");
                    }
                    // If it's an int + int, it should be an int
                    if (strcmp($1, "int") == 0 && strcmp($3, "int") == 0) {
                        $$ = "int";
                    } else {
                        $$ = "float";
                    }
                }
              | RULE_AT MINUS RULE_AF {
                    if (strcmp($1, "int") != 0 && strcmp($1, "float") != 0) {
                        yyaccerror("Type mismatch in minus operation");
                    }
                    if (strcmp($3, "int") != 0 && strcmp($3, "float") != 0) {
                        yyaccerror("Type mismatch in minus operation");
                    }
                    // If it's an int - int, it should be an int
                    if (strcmp($1, "int") == 0 && strcmp($3, "int") == 0) {
                        $$ = "int";
                    } else {
                        $$ = "float";
                    }
                }
              | RULE_AF {
                    $$ = $1;
                }
              ;
RULE_R             : RULE_AT RULE_R_ {
                    // If it's a relational operation, both values should be equal in type
                    if (strcmp($1, $2) != 0) {
                        yyaccerror("Type mismatch in relational operation");
                    }
                    $$ = "bool";
                }
              ;
RULE_R_            : LESSTHAN RULE_AT {
                    if (strcmp($2, "int") != 0 && strcmp($2, "float") != 0) {
                        yyaccerror("Type mismatch in relational operation");
                    }
                    $$ = $2;
} | GREATERTHAN RULE_AT {
                    if (strcmp($2, "int") != 0 && strcmp($2, "float") != 0) {
                        yyaccerror("Type mismatch in relational operation");
                    }
                    $$ = $2;
} | LESSTHANOREQUAL RULE_AT {
                    if (strcmp($2, "int") != 0 && strcmp($2, "float") != 0) {
                        yyaccerror("Type mismatch in relational operation");
                    }
                    $$ = $2;
} | GREATERTHANOREQUAL RULE_AT {
                    if (strcmp($2, "int") != 0 && strcmp($2, "float") != 0) {
                        yyaccerror("Type mismatch in relational operation");
                    }
                    $$ = $2;
} | EQUALS RULE_AT {
                    if (strcmp($2, "int") != 0 && strcmp($2, "float") != 0 || strcmp($2, "bool") != 0) {
                        yyaccerror("Type mismatch in relational operation");
                    }
                    $$ = $2;
} | NOTEQUAL RULE_AT {
                    if (strcmp($2, "int") != 0 && strcmp($2, "float") != 0 || strcmp($2, "bool") != 0) {
                        yyaccerror("Type mismatch in relational operation");
                    }
                    $$ = $2;
} | 
              ;
RULE_LU            : NOT RULE_R {
                    if (strcmp($2, "bool") != 0) {
                        yyaccerror("Type mismatch in logical not operation");
                    }
                    $$ = "bool";
                }
              | RULE_R {
                    $$ = $1;
                }
              ;
RULE_LC            : RULE_LC AND RULE_LC {
                    if (strcmp($1, "bool") != 0 && strcmp($3, "bool") != 0) {
                        yyaccerror("Type mismatch in logical and operation");
                    }
                    $$ = "bool";
                }
              | RULE_LU {
                    $$ = $1;
                }
              ;
RULE_EXP           : RULE_EXP OR RULE_EXP {
                    if (strcmp($1, "bool") != 0 && strcmp($3, "bool") != 0) {
                        yyaccerror("Type mismatch in logical or operation");
                    }
                    $$ = "bool";
                }
              | RULE_LC {
                    $$ = $1;
                }
              ;
RULE_ARGS          : TYPE ID | TYPE ID COMMA RULE_ARGS | 
              ;
RULE_STMTS         : RULE_STMT | RULE_STMT RULE_STMTS
              ;
RULE_STMT          : RULE_VAR | RULE_ASSIGN | ID LPAREN RULE_EXPS RPAREN SEMICOLON | RULE_SUBPROGRAM | RULE_IF | RULE_SWITCH | RULE_FOR | RULE_LOOP | RULE_WHEN | RULE_UNLESS | RULE_PRINT
              ;
RULE_SUBPROGRAMS   : RULE_SUBPROGRAM | RULE_SUBPROGRAM RULE_SUBPROGRAMS
              ;
RULE_SUBPROGRAMS_  : RULE_SUBPROGRAMS |
RULE_SUBPROGRAM    : RULE_FUNCTION | RULE_PROCEDURE 
              ;
RULE_FUNCTION      : FUNCTION TYPE ID LPAREN RULE_ARGS RPAREN T_BEGIN {
    enterScope();
} RULE_STMTS RULE_RETURN END ID {
                    addSymbol($3, $2, 1);
                    if (strcmp($2, $9) != 0) {
                        yyaccerror("Type mismatch in function return");
                    }
                    leaveScope();
}
              ;
RULE_RETURN        : RETURN RULE_EXP SEMICOLON {
                    $$ = $2;
                }
| 
              ;
RULE_PROCEDURE     : PROCEDURE ID LPAREN RULE_ARGS RPAREN T_BEGIN {
    enterScope();
}
 RULE_STMTS END ID {
                    addSymbol($2, "void", 1);
                    leaveScope();
 }
              ;
RULE_IF            : IF LPAREN RULE_EXP RPAREN {
    if (strcmp($3, "bool") != 0) {
        yyaccerror("Type mismatch in if condition");
    }
        enterScope();
    } RULE_STMTS {
        leaveScope();
    } RULE_ELIF RULE_ELSE END IF 
                ;
RULE_ELIF          : ELIF LPAREN RULE_EXP RPAREN {
    if (strcmp($3, "bool") != 0) {
        yyaccerror("Type mismatch in elif condition");
    }
    enterScope();
    } RULE_STMTS END ELIF {
        leaveScope();
    }
    | 
              ;
RULE_ELSE          : ELSE {
                    enterScope();
                } RULE_STMTS {
                    leaveScope();
                }
              ;
RULE_SWITCH        : SWITCH LPAREN RULE_VAR RPAREN {
    if (strcmp($3, "int") != 0) {
        yyaccerror("Type mismatch in switch condition");
    }
}
RULE_CASE RULE_DEFAULT END SWITCH
              ;
RULE_CASE          : CASE LPAREN RULE_EXP LPAREN {
    if (strcmp($3, "int") != 0) {
        yyaccerror("Type mismatch in case condition");
    }
    enterScope();
    } COLON RULE_STMTS BREAK CASE {
        leaveScope();
    }
              | 
              ;
    RULE_DEFAULT       : DEFAULT {
                        enterScope();
    } COLON RULE_STMTS BREAK {
        leaveScope();
    } | 
              ;
RULE_FOR           : FOR {
        enterScope();
    } LPAREN RULE_ASSIGN SEMICOLON RULE_EXP SEMICOLON {
        // Is it a boolean?
        if (strcmp($5, "bool") != 0) {
            yyaccerror("Type mismatch in for condition");
        }
    } RULE_EXP RPAREN {
        enterScope();
    } RULE_STMTS END {
        leaveScope();
    } FOR {
        leaveScope();
    }
              ;
RULE_LOOP          : LOOP {
        enterScope();
} RULE_STMTS END LOOP {
        leaveScope();
}
              ;
RULE_WHEN          : EXIT WHEN RULE_EXP {
        if (strcmp($3, "bool") != 0) {
            yyaccerror("Type mismatch in when condition");
        }
}
              ;
RULE_UNLESS        : UNLESS RULE_EXP {
        if (strcmp($2, "bool") != 0) {
            yyaccerror("Type mismatch in unless condition");
        }
} DO {
        enterScope();
} RULE_STMT END UNLESS {
        leaveScope();
    }
              ;
RULE_PRINT         : PRINT LPAREN RULE_PRINT_ RPAREN SEMICOLON
              ;
RULE_PRINT_        : RULE_EXP | CCHAR | CSTRING | CARRAY
              ;
%%

// Symbol table functions
void addSymbol(const char *id, const char *type, int isFunction) {
    Symbol *newSymbol = (Symbol *)malloc(sizeof(Symbol));
    strcpy(newSymbol->id, id);
    strcpy(newSymbol->type, type);
    newSymbol->isFunction = isFunction;
    newSymbol->depth = currentDepth;
    newSymbol->next = symbolTable;
    symbolTable = newSymbol;
}

const char *getSymbolType(const char *id) {
    Symbol *current = symbolTable;
    while (current) {
        if (strcmp(current->id, id) == 0) {
            return current->type;
        }
        current = current->next;
    }
    return NULL; // Not found
}

const char *isFunc(const char *id) {
    Symbol *current = symbolTable;
    while (current) {
        if (strcmp(current->id, id) == 0) {
            if (current->isFunction) {
                return current->type;
            }
        }
        current = current->next;
    }
    return NULL; // Not found
}

void removeSymbolsAtDepth(int depth) {
    Symbol *current = symbolTable;
    Symbol *prev = NULL;

    while (current) {
        if (current->depth == depth) {
            if (prev) {
                prev->next = current->next;
            } else {
                symbolTable = current->next;
            }
            free(current);
            current = (prev) ? prev->next : symbolTable;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void enterScope() {
    currentDepth++;
}

void leaveScope() {
    removeSymbolsAtDepth(currentDepth);
    currentDepth--;
}

void yyaccerror(const char *msg) {
    fprintf(stderr, "Syntax error: %s\n", msg);
    exit(1);
}