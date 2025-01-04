/* Grammar

PROGRAM ::= SUBPROGRAMS' MAIN begin STMTS end program
MAIN ::= main ( EXP )
VAR ::= const TYPE ASSIGN
VAR ::= TYPE ASSIGN
VAR ::= REGISTER_DECL
TYPE ::= int 
TYPE ::= float 
TYPE ::= bool 
TYPE ::= char
TYPE ::= string

ASSIGN ::= id ARRAY_DECL = ASSIGN'
ASSIGN' ::= EXP ;
ASSIGN' ::= cchar ;
ASSIGN' ::= cstring ;
ASSIGN' ::= carray ;

ARRAY_DECL ::= [ SIZE ] ARRAY_DECL
ARRAY_DECL ::= ''
SIZE ::= EXP

REGISTER_DECL ::= register TYPE id ;

LIT ::= cint
LIT ::= cfloat
LIT ::= cbool
O ::= LIT
O ::= id O'
O ::= call id ( EXPS' )
O' ::= . id O'
O' ::= [ EXP ] O'
O' ::= ''



AU ::= + O
AU ::= - O
AU ::= O

OP ::= AU
OP ::= ( EXP )

AP ::= OP AP'
AP' ::= ^ AP 
AP' ::= ''
AF ::= AP AF'
AF' ::= * AF 
AF' ::= / AF
AF' ::= ''
AT ::= AF AT'
AT' ::= + AT
AT' ::= - AT
AT' ::= ''
R ::= AT R'
R' ::= < AT
R' ::= > AT
R' ::= <= AT
R' ::= >= AT
R' ::= == AT
R' ::= != AT
R' ::= ''
LU ::= not R 
LU ::= R
LC ::= LU LC'
LC' ::= and LU LC' 
LC' ::= ''
EXP ::= LC EXP'
EXP' ::= or LC EXP' 
EXP' ::= ''
EXPS ::= EXP , EXPS'
EXPS' ::= EXPS
EXPS' ::= ''
ARGS ::= TYPE id ARGS' 
ARGS' ::= , ARGS  
ARGS' ::= '' 
STMTS ::= STMT STMTS'  
STMTS' ::= STMTS 
STMTS' ::= '' 
STMT ::= VAR
STMT ::= ASSIGN
STMT ::= call id ( EXPS' ) ;
STMT ::= SUBPROGRAM
STMT ::= IF
STMT ::= SWITCH
STMT ::= FOR
STMT ::= LOOP
STMT ::= WHEN
STMT ::= UNLESS
STMT ::= PRINT
SUBPROGRAMS ::= SUBPROGRAM SUBPROGRAMS'  
SUBPROGRAMS' ::= SUBPROGRAMS 
SUBPROGRAMS' ::= '' 
SUBPROGRAM ::= FUNCTION 
SUBPROGRAM ::= PROCEDURE 
FUNCTION ::= function TYPE id ( ARGS' ) begin STMTS end id 
PROCEDURE ::= procedure id ( ARGS' ) begin STMTS end id 
IF ::= if  EXP  STMTS' ELIF' ELSE end if 
ELIF ::= elif  EXP  STMTS' ELIF'
ELIF' ::= '' 
ELIF' ::= ELIF
ELSE ::= else STMTS'
ELSE ::= '' 
SWITCH ::= switch ( VAR ) CASE DEFAULT end switch 
CASE ::= case  EXP : STMTS' break ; CASE' 
CASE' ::= CASE 
CASE' ::= '' 
DEFAULT ::= default : STMTS' break ;
DEFAULT ::= '' 
FOR ::= for ( ASSIGN ; EXP ; EXP ) STMTS' end for 
LOOP ::= loop STMTS end loop
WHEN ::= exit when  EXP 
UNLESS ::= unless  EXP  do STMT
PRINT ::= print ( PRINT' ) ;
PRINT' ::= EXP
PRINT' ::= cchar
PRINT' ::= cstring
PRINT' ::= carray

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lex.yy.c"
#include "tokens.h"
#include "getNameToken.c"

// This will be a non-recursive LL(1) parser for the grammar above
// Using a table and a stack of the productions to be used

// The table will be a 2D array of function pointers
// The stack will be a stack of integers

/* Tokens from tokens.h

BEGIN 1
END 2
PROGRAM 3
MAIN 4
LPAREN 5
RPAREN 6
CONST 7
INT 8
FLOAT 9
BOOL 10
CHAR 11
STRING 12
ID 13
ASSIGN 14
SEMICOLON 15
CCHAR 16
CSTRING 17
CARRAY 18
LBRACE 19
RBRACE 20
REGISTER 21
CINT 22
CFLOAT 23
CBOOL 24
CALL 25
DOT 26
PLUS 27
MINUS 28
POWER 29
MULTIPLY 30
DIVIDE 31
LESSTHAN 32
GREATERTHAN 33
LESSTHANOREQUAL 34
GREATERTHANOREQUAL 35
EQUALS 36
NOTEQUAL 37
NOT 38
AND 39
OR 40
COMMA 41
FUNCTION 42
RETURN 43
PROCEDURE 44
IF 45
ELIF 46
ELSE 47
SWITCH 48
CASE 49
COLON 50
BREAK 51
DEFAULT 52
FOR 53
LOOP 54
EXIT 55
WHEN 56
UNLESS 57
DO 58
PRINT 59

*/

// 54 constructs + S := PROGRAM $, 59 terminal tokens

int table[55][59][20] = {
    {
        {-1}, {-1}, {-1}, {RULE_PROGRAM, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {RULE_PROGRAM, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, {-1}, {RULE_PROGRAM, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}, {-1}
    }, // S := PROGRAM $
    {
        {-1}, {-1}, {-1}, {RULE_SUBPROGRAMS_, RULE_MAIN, BEGIN, RULE_STMTS, END, PROGRAM,
    }
}
    


/* Example of code using simpler grammar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100
#define TABLE_ROWS 6  // Number of non-terminals
#define TABLE_COLS 6  // Number of terminals

// Define tokens
enum Tokens {
    T_PLUS = 0,   // +
    T_STAR,       // *
    T_LPAREN,     // (
    T_RPAREN,     // )
    T_ID,         // id
    T_END         // $
};

// Non-terminal symbols
enum NonTerminals {
    NT_S = 0,  // S
    NT_E,      // E
    NT_E_,     // E'
    NT_T,      // T
    NT_T_,     // T'
    NT_F       // F
};

// Define parsing table (row: non-terminal, col: terminal)
int parsing_table[TABLE_ROWS][TABLE_COLS] = {
    {1, -1, 0, -1, 0, -1}, // S ::= E $
    {2, -1, 2, -1, 2, -1}, // E ::= T E'
    {-1, 3, -1, 4, -1, 4}, // E' ::= + T E' | ε
    {5, -1, 5, -1, 5, -1}, // T ::= F T'
    {-1, 7, -1, 6, -1, 6}, // T' ::= * F T' | ε
    {8, -1, 9, -1, 9, -1}  // F ::= ( E ) | id
};

// Production rules (array of arrays for simplicity)
const char *productions[] = {
    "S -> E $",
    "E -> T E'",
    "E' -> + T E'",
    "E' -> ε",
    "T -> F T'",
    "T' -> * F T'",
    "T' -> ε",
    "F -> ( E )",
    "F -> id"
};

// Stack structure
typedef struct {
    int items[STACK_SIZE];
    int top;
} Stack;

void push(Stack *stack, int value) {
    if (stack->top >= STACK_SIZE - 1) {
        fprintf(stderr, "Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->items[++stack->top] = value;
}

int pop(Stack *stack) {
    if (stack->top < 0) {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->items[stack->top--];
}

int peek(Stack *stack) {
    if (stack->top < 0) {
        fprintf(stderr, "Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack->items[stack->top];
}

// Lexer function prototype
int yylex();

void parse() {
    Stack stack;
    stack.top = -1;

    // Push start symbol (S) and end marker ($)
    push(&stack, T_END);  // $
    push(&stack, NT_S);   // Start symbol S

    int token = yylex();

    while (stack.top >= 0) {
        int top = peek(&stack);

        if (top >= T_PLUS && top <= T_END) {  // Terminal symbol
            if (top == token) {
                printf("Matched token: %d\n", token);
                pop(&stack);
                token = yylex();
            } else {
                fprintf(stderr, "Syntax error: unexpected token %d\n", token);
                exit(EXIT_FAILURE);
            }
        } else if (top >= NT_S && top <= NT_F) {  // Non-terminal symbol
            int rule = parsing_table[top][token];

            if (rule != -1) {
                printf("Using production: %s\n", productions[rule]);
                pop(&stack);

                // Push production in reverse order (right-to-left)
                const char *rhs = productions[rule] + 6;  // Skip "X -> "
                for (int i = strlen(rhs) - 1; i >= 0; i--) {
                    if (rhs[i] != ' ' && rhs[i] != '\' && rhs[i] != 'ε') {
                        push(&stack, rhs[i]);
                    }
                }
            } else {
                fprintf(stderr, "Syntax error: no rule for %d -> %d\n", top, token);
                exit(EXIT_FAILURE);
            }
        } else {
            fprintf(stderr, "Invalid symbol on stack: %d\n", top);
            exit(EXIT_FAILURE);
        }
    }

    if (token == T_END) {
        printf("Parsing successful!\n");
    } else {
        fprintf(stderr, "Syntax error: input not fully consumed\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    parse();
    return 0;
}
*/

