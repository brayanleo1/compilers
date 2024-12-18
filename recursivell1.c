/*Grammar

PROGRAM ::= SUBPROGRAMS' MAIN begin STMTS end program
MAIN ::= main ( ARGS' )
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

ARRAY_DECL ::= [ SIZE ]
ARRAY_DECL ::= ''
SIZE ::= EXP

REGISTER_DECL ::= register TYPE id ;

LIT ::= cint
LIT ::= cfloat
LIT ::= cbool
O ::= id O'
O :: O'
O ::= LIT 
O' ::= ( EXP )
O' ::= [ EXP ]
O' ::= . id
O' ::= ''


AU ::= + O 
AU ::= - O 
AU ::= O
AP ::= O AP'
AP' ::= ^ AP 
AP' ::= ''
AF ::= AP AF'
AF' ::= * AP AF' 
AF' ::= / AP AF' 
AF' ::= ''
AT ::= AF AT'
AT' ::= + AF AT' 
AT' ::= - AF AT' 
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
ARGS ::= TYPE id ARGS' 
ARGS' ::= , ARGS  
ARGS' ::= '' 
STMTS ::= STMT STMTS'  
STMTS' ::= STMTS 
STMTS' ::= '' 
STMT ::= EXP
STMT ::= VAR
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
IF ::= if ( EXP ) STMTS' ELIF' ELSE end if 
ELIF ::= elif ( EXP ) STMTS' ELIF'
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
WHEN ::= exit when ( EXP )
UNLESS ::= unless ( EXP ) do STMT
PRINT ::= print ( ASSIGN' ) ;

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lex.yy.c"
#include "tokens.h"
#include "getNameToken.c"


int tok;

void advance() {tok=yylex();  printf("Next token: %s\n", getName(tok));}
void eat(int t) {
    if (tok==t) {
        printf("Eating: %s\n", getName(t));
        advance();
} else {
        errorE(t);
    }
}

void errorE(int t) {printf("Expected: %s, found: %s at Line %d\n", getName(t), getName(tok), yylineno);
exit(1);}

void error(void) {printf("Error - unexpected token: %s at Line %d\n", getName(tok), yylineno);
exit(1);}


void VAR(void) {
    printf ("Entering VAR\n");
    switch (tok) {
        case CONST: eat(CONST); TYPE(); FUNC_ASSIGN(); break;
        case INT: TYPE(); FUNC_ASSIGN(); break;
        case FLOAT: TYPE(); FUNC_ASSIGN(); break;
        case BOOL: TYPE(); FUNC_ASSIGN(); break;
        case CHAR: TYPE(); FUNC_ASSIGN(); break;
        case STRING: TYPE(); FUNC_ASSIGN(); break;
        case REGISTER: REGISTER_DECL(); break;
        default: printf("Error at VAR\n");
        error();
    }
    printf ("Exiting VAR\n");
}

void TYPE(void) {
    printf ("Entering TYPE\n");
    switch (tok) {
        case INT: eat(INT); break;
        case FLOAT: eat(FLOAT); break;
        case BOOL: eat(BOOL); break;
        case CHAR: eat(CHAR); break;
        case STRING: eat(STRING); break;
        default: printf("Error at TYPE\n");
        error();
    }
    printf ("Exiting TYPE\n");
}

void FUNC_ASSIGN(void) {
    printf ("Entering FUNC_ASSIGN\n");
    switch (tok) {
        case ID: eat(ID); ARRAY_DECL(); eat(ASSIGN); ASSIGN_(); break;
        default: printf("Error at FUNC_ASSIGN\n");
        error();
    }
    printf ("Exiting FUNC_ASSIGN\n");
}

void ASSIGN_(void) {
    printf ("Entering ASSIGN_\n");
    switch (tok) {
        case CCHAR: eat(CCHAR); eat(SEMICOLON); break;
        case CSTRING: eat(CSTRING); eat(SEMICOLON); break;
        case CARRAY: eat(CARRAY); eat(SEMICOLON); break;
        case CINT: EXP(); eat(SEMICOLON); break;
        case CFLOAT: EXP(); eat(SEMICOLON); break;
        case CBOOL: EXP(); eat(SEMICOLON); break;
        case NOT: EXP(); eat(SEMICOLON); break;
        case ID: EXP(); eat(SEMICOLON); break;
        case LBRACKET: EXP(); eat(SEMICOLON); break;
        case LPAREN: EXP(); eat(SEMICOLON); break;
        case DOT: EXP(); eat(SEMICOLON); break;
        default: printf("Error at ASSIGN_\n");
        error();

    }
    printf ("Exiting ASSIGN_\n");
}

void ARRAY_DECL(void) {
    switch (tok) {
        case LBRACKET: eat(LBRACKET); SIZE(); eat(RBRACKET); break;
        case ASSIGN: break;
        default: printf("Error at ARRAY_DECL\n");
        error();
    }
}

void SIZE(void) {
    EXP();
}

void REGISTER_DECL(void) {
    switch (tok) {
        case REGISTER: eat(REGISTER); TYPE(); eat(ID); eat(SEMICOLON); break;
        default: printf("Error at REGISTER_DECL\n");
        error();
    }
}

void LIT(void) {
    printf("Entering LIT\n");
    switch (tok) {
        case CINT: eat(CINT); break;
        case CFLOAT: eat(CFLOAT); break;
        case CBOOL: eat(CBOOL); break;
        default: printf("Error at LIT\n");
        error();
    }
    printf("Exiting LIT\n");
}

void O(void) {
    printf("Entering O\n");
    switch (tok) {
        case ID: eat(ID); O_(); break;
        case CINT: LIT(); break;
        case CFLOAT: LIT(); break;
        case CBOOL: LIT(); break;
        case LPAREN: O_(); break;
        case LBRACKET: O_(); break;
        case DOT: O_(); break;
        default: printf("Error at O\n");
        error();
    }
    printf("Exiting O\n");
}

void O_(void) {
    printf("Entering O_\n");
    switch (tok) {
        case LPAREN: eat(LPAREN); EXP(); eat(RPAREN); break;
        case LBRACKET: eat(LBRACKET); EXP(); eat(RBRACKET); break;
        case DOT: eat(DOT); eat(ID); break;
        default: printf("Error at O_\n");
        error();
    }
    printf("Exiting O_\n");
}

void AU(void) {
    printf("Entering AU\n");
    switch (tok) {
        case PLUS: eat(PLUS); O(); break;
        case MINUS: eat(MINUS); O(); break;
        case ID: O(); break;
        case CINT: O(); break;
        case CFLOAT: O(); break;
        case CBOOL: O(); break;
        case LPAREN: O(); break;
        case LBRACKET: O(); break;
        case DOT: O(); break;
        default: printf("Error at AU\n");
        error();
    }
    printf("Exiting AU\n");
}

void OP(void) {
    printf("Entering OP\n");
    switch (tok) {
        case LPAREN: eat(LPAREN); EXP(); eat(RPAREN); break;
        case PLUS: AU(); break;
        case MINUS: AU(); break;
        case ID: AU(); break;
        case CINT: AU(); break;
        case CFLOAT: AU(); break;
        case CBOOL: AU(); break;
    }
    printf("Exiting OP\n");
}

void AP(void) {
    printf("Entering AP\n");
    OP();
    AP_();
    printf("Exiting AP\n");
}

void AP_(void) {
    switch (tok) {
        case POWER: eat(POWER); AP(); break;
        //*, /, +, -, <, >, <=, >=, ==, !=, and, ;, ], ), or, end, not, id, const, cint, cfloat, cbool, (, [, ., int, float, bool, char, string, register, if, switch, for, loop, exit, unless, function, procedure, :, elif, break, else
        case MULTIPLY: break;
        case DIVIDE: break;
        case PLUS: break;
        case MINUS: break;
        case LESSTHAN: break;
        case GREATERTHAN: break;
        case LESSTHANOREQUAL: break;
        case GREATERTHANOREQUAL: break;
        case EQUALS: break;
        case NOTEQUAL: break;
        case AND: break;
        case SEMICOLON: break;
        case RBRACKET: break;
        case RPAREN: break;
        case OR: break;
        case END: break;
        case NOT: break;
        case ID: break;
        case CONST: break;
        case CINT: break;
        case CFLOAT: break;
        case CBOOL: break;
        case LPAREN: break;
        case LBRACKET: break;
        case DOT: break;
        case INT: break;
        case FLOAT: break;
        case BOOL: break;
        case CHAR: break;
        case STRING: break;
        case REGISTER: break;
        case IF: break;
        case SWITCH: break;
        case FOR: break;
        case LOOP: break;
        case EXIT: break;
        case UNLESS: break;
        case FUNCTION: break;
        case PROCEDURE: break;
        case COLON: break;
        case ELIF: break;
        case BREAK: break;
        case ELSE: break;
        default: printf("Error at AP_\n");
        error();
    }

}

void AF(void) {
    printf("Entering AF\n");
    AP();
    AF_();
    printf("Exiting AF\n");
}

void AF_(void) {
    switch (tok) {
        case MULTIPLY: eat(MULTIPLY); AP(); AF_(); break;
        case DIVIDE: eat(DIVIDE); AP(); AF_(); break;
        case PLUS: break;
        case MINUS: break;
        case LESSTHAN: break;
        case GREATERTHAN: break;
        case LESSTHANOREQUAL: break;
        case GREATERTHANOREQUAL: break;
        case EQUALS: break;
        case NOTEQUAL: break;
        case AND: break;
        case OR: break;
        case SEMICOLON: break;
        case RBRACKET: break;
        case RPAREN: break;
        case END: break;
        case NOT: break;
        case ID: break;
        case CONST: break;
        case CINT: break;
        case CFLOAT: break;
        case CBOOL: break;
        case LPAREN: break;
        case LBRACKET: break;
        case DOT: break;
        case INT: break;
        case FLOAT: break;
        case BOOL: break;
        case CHAR: break;
        case STRING: break;
        case REGISTER: break;
        case IF: break;
        case SWITCH: break;
        case FOR: break;
        case LOOP: break;
        case EXIT: break;
        case UNLESS: break;
        case FUNCTION: break;
        case PROCEDURE: break;
        case COLON: break;
        case ELIF: break;
        case BREAK: break;
        case ELSE: break;
        default: printf("Error at AF_\n");
        error();
    }

}

void AT(void) {
    printf("Entering AT\n");
    AF();
    AT_();
    printf("Exiting AT\n");
}

void AT_(void) {
    printf("Entering AT_\n");
    switch (tok) {
        case PLUS: eat(PLUS); AF(); AT_(); break;
        case MINUS: eat(MINUS); AF(); AT_(); break;
        case LESSTHAN: break;
        case GREATERTHAN: break;
        case LESSTHANOREQUAL: break;
        case GREATERTHANOREQUAL: break;
        case EQUALS: break;
        case NOTEQUAL: break;
        case AND: break;
        case OR: break;
        case SEMICOLON: break;
        case RBRACKET: break;
        case RPAREN: break;
        case END: break;
        case NOT: break;
        case ID: break;
        case CONST: break;
        case CINT: break;
        case CFLOAT: break;
        case CBOOL: break;
        case LPAREN: break;
        case LBRACKET: break;
        case DOT: break;
        case INT: break;
        case FLOAT: break;
        case BOOL: break;
        case CHAR: break;
        case STRING: break;
        case REGISTER: break;
        case IF: break;
        case SWITCH: break;
        case FOR: break;
        case LOOP: break;
        case EXIT: break;
        case UNLESS: break;
        case FUNCTION: break;
        case PROCEDURE: break;
        case COLON: break;
        case ELIF: break;
        case BREAK: break;
        case ELSE: break;
        default: printf("Error at AT_\n");
        error();
    }
    printf("Exiting AT_\n");
}

void R(void) {
    printf("Entering R\n");
    AT();
    R_();
    printf("Exiting R\n");
}

void R_(void) {
    printf("Entering R_\n");
    switch (tok) {
        case LESSTHAN: eat(LESSTHAN); AT(); break;
        case GREATERTHAN: eat(GREATERTHAN); AT(); break;
        case LESSTHANOREQUAL: eat(LESSTHANOREQUAL); AT(); break;
        case GREATERTHANOREQUAL: eat(GREATERTHANOREQUAL); AT(); break;
        case EQUALS: eat(EQUALS); AT(); break;
        case NOTEQUAL: eat(NOTEQUAL); AT(); break;
        case AND: break;
        case OR: break;
        case SEMICOLON: break;
        case RBRACKET: break;
        case RPAREN: break;
        case END: break;
        case NOT: break;
        case ID: break;
        case CONST: break;
        case CINT: break;
        case CFLOAT: break;
        case CBOOL: break;
        case LPAREN: break;
        case LBRACKET: break;
        case DOT: break;
        case INT: break;
        case FLOAT: break;
        case BOOL: break;
        case CHAR: break;
        case STRING: break;
        case REGISTER: break;
        case IF: break;
        case SWITCH: break;
        case FOR: break;
        case LOOP: break;
        case EXIT: break;
        case UNLESS: break;
        case FUNCTION: break;
        case PROCEDURE: break;
        case COLON: break;
        case ELIF: break;
        case BREAK: break;
        case ELSE: break;
        default: printf("Error at R_\n");
        error();
    }
    printf("Exiting R_\n");
}

void LU(void) {
    printf("Entering LU\n");
    switch (tok) {
        case NOT: eat(NOT); R(); break;
        case ID: R(); break;
        case CONST: R(); break;
        case CINT: R(); break;
        case CFLOAT: R(); break;
        case CBOOL: R(); break;
        case LPAREN: R(); break;
        case LBRACKET: R(); break;
        case DOT: R(); break;
        default: printf("Error at LU\n");
        error();
    }
    printf("Exiting LU\n");
}

void LC(void) {
    printf("Entering LC\n");
    LU();
    LC_();
    printf("Exiting LC\n");
}

void LC_(void) {
    switch (tok) {
        case AND: eat(AND); LU(); LC_(); break;
        case OR: break;
        case SEMICOLON: break;
        case RBRACKET: break;
        case RPAREN: break;
        case END: break;
        case NOT: break;
        case ID: break;
        case CONST: break;
        case CINT: break;
        case CFLOAT: break;
        case CBOOL: break;
        case LPAREN: break;
        case LBRACKET: break;
        case DOT: break;
        case INT: break;
        case FLOAT: break;
        case BOOL: break;
        case CHAR: break;
        case STRING: break;
        case REGISTER: break;
        case IF: break;
        case SWITCH: break;
        case FOR: break;
        case LOOP: break;
        case EXIT: break;
        case UNLESS: break;
        case FUNCTION: break;
        case PROCEDURE: break;
        case COLON: break;
        case ELIF: break;
        case BREAK: break;
        case ELSE: break;
        default: printf("Error at LC_\n");
        error();
    }
}

void EXP(void) {
    printf("Entering EXP\n");
    LC();
    EXP_();
    printf("Exiting EXP\n");
}

void EXP_(void) {
    switch (tok) {
        case OR: eat(OR); LC(); EXP_(); break;
        case SEMICOLON: break;
        case RBRACKET: break;
        case RPAREN: break;
        case END: break;
        case NOT: break;
        case ID: break;
        case CONST: break;
        case CINT: break;
        case CFLOAT: break;
        case CBOOL: break;
        case LPAREN: break;
        case LBRACKET: break;
        case DOT: break;
        case INT: break;
        case FLOAT: break;
        case BOOL: break;
        case CHAR: break;
        case STRING: break;
        case REGISTER: break;
        case IF: break;
        case SWITCH: break;
        case FOR: break;
        case LOOP: break;
        case EXIT: break;
        case UNLESS: break;
        case FUNCTION: break;
        case PROCEDURE: break;
        case COLON: break;
        case ELIF: break;
        case BREAK: break;
        case ELSE: break;
        default: printf("Error at EXP_\n");
        error();
    }
}

void ARGS(void) {
    TYPE();
    eat(ID);
    ARGS_();
}

void ARGS_(void) {
    switch (tok) {
        case COMMA: eat(COMMA); ARGS(); break;
        case RPAREN: break;
        default: printf("Error at ARGS_\n");
        error();
    }
}

void FUNC_IF(void) {
    printf("Entering FUNC_IF\n");
    eat(IF);
    EXP();
    STMTS_();
    FUNC_ELIF_();
    FUNC_ELSE();
    eat(END);
    eat(IF);
    printf("Exiting FUNC_IF\n");
}

void FUNC_ELIF_(void) {
    switch (tok)
    {
    case ELIF: FUNC_ELIF(); break;
    case END: break;
    case ELSE: break;
    default: printf("Error at FUNC_ELIF_\n");
    error();
    }
}

void FUNC_ELIF(void) {
    switch (tok)
    { 
        case ELIF: eat(ELIF); EXP(); STMTS(); FUNC_ELIF(); break;
        default : printf("Error at FUNC_ELIF\n");
        error();
    }
}

void FUNC_ELSE(void) {
    switch (tok)
    {
        case ELSE: eat(ELSE); STMTS(); break;
        case END: break;
        default: printf("Error at FUNC_ELSE\n");
        error();
    }
}

void FUNC_SWITCH(void) {
    printf("Entering FUNC_SWITCH\n");
    eat(SWITCH);
    eat(LPAREN);
    VAR();
    eat(RPAREN);
    FUNC_CASE();
    FUNC_DEFAULT();
    eat(END);
    eat(SWITCH);
    printf("Exiting FUNC_SWITCH\n");
}

void FUNC_CASE(void) {
    eat(CASE);
    EXP();
    eat(COLON);
    STMTS();
    eat(BREAK);
    eat(SEMICOLON);
    CASE_();
}

void CASE_(void) {
    switch (tok) {
        case CASE: FUNC_CASE(); break;
        case DEFAULT: break;
        case END: break;
        default: printf("Error at CASE_\n");
        error();
    }
}

void FUNC_DEFAULT(void) {
    switch (tok) {
        case DEFAULT: eat(DEFAULT); eat(COLON); STMTS(); eat(BREAK); eat(SEMICOLON); break;
        case END: break;
        default: printf("Error at FUNC_DEFAULT\n");
        error();
    }
}

void FUNC_FOR(void) {
    printf("Entering FUNC_FOR\n");
    eat(FOR);
    eat(LPAREN);
    FUNC_ASSIGN();
    eat(SEMICOLON);
    EXP();
    eat(SEMICOLON);
    EXP();
    eat(RPAREN);
    STMTS_();
    eat(END);
    eat(FOR);
    printf("Exiting FUNC_FOR\n");
}

void FUNC_LOOP(void) {
    printf("Entering FUNC_LOOP\n");
    eat(LOOP);
    STMTS_();
    eat(END);
    eat(LOOP);
    printf("Exiting FUNC_LOOP\n");
}

void FUNC_WHEN(void) {
    eat(EXIT);
    eat(WHEN);
    EXP();
}

void FUNC_UNLESS(void) {
    eat(UNLESS);
    EXP();
    eat(DO);
    STMT();
}

void FUNC_PRINT(void) {
    eat(PRINT);
    eat(LPAREN);
    ASSIGN_();
    eat(RPAREN);
    eat(SEMICOLON);
}

void STMTS(void) {
    printf("Entering STMTS\n");
    STMT();
    STMTS_();
    printf("Exiting STMTS\n");
}

void STMTS_(void) {
    printf("Entering STMTS_\n");
    switch (tok) {
        case ID: STMTS(); break;
        case LPAREN: STMTS(); break;
        case CINT: STMTS(); break;
        case CFLOAT: STMTS(); break;
        case CBOOL: STMTS(); break;
        case CONST: STMTS(); break;
        case REGISTER: STMTS(); break;
        case INT: STMTS(); break;
        case FLOAT: STMTS(); break;
        case BOOL: STMTS(); break;
        case CHAR: STMTS(); break;
        case STRING: STMTS(); break;
        case FUNCTION: STMTS(); break;
        case PROCEDURE: STMTS(); break;
        case IF: STMTS(); break;
        case SWITCH: STMTS(); break;
        case FOR: STMTS(); break;
        case LOOP: STMTS(); break;
        case WHEN: STMTS(); break;
        case UNLESS: STMTS(); break;
        case PRINT: STMTS(); break;
        case END: break;
        case ELSE: break;
        case ELIF: break;
        case BREAK: break;
        default: printf("Error at STMTS_\n");
        error();
    }
    printf("Exiting STMTS_\n");

}

void STMT(void) {
    printf("Entering STMT\n");
    switch (tok) {
        case ID: EXP(); break;
        case LPAREN: EXP(); break;
        case CINT: EXP(); break;
        case CFLOAT: EXP(); break;
        case CBOOL: EXP(); break;
        case CONST: VAR(); break;
        case REGISTER: VAR(); break;
        case INT: VAR(); break;
        case FLOAT: VAR(); break;
        case BOOL: VAR(); break;
        case CHAR: VAR(); break;
        case STRING: VAR(); break;
        case FUNCTION: SUBPROGRAM(); break;
        case PROCEDURE: SUBPROGRAM(); break;
        case IF: FUNC_IF(); break;
        case SWITCH: FUNC_SWITCH(); break;
        case FOR: FUNC_FOR(); break;
        case LOOP: FUNC_LOOP(); break;
        case WHEN: FUNC_WHEN(); break;
        case UNLESS: FUNC_UNLESS(); break;
        case PRINT: FUNC_PRINT(); break;
        default: printf("Error at STMT\n");
        error();
    }
    printf("Exiting STMT\n");
}

void FUNC_FUNCTION(void) {
    printf("Entering FUNC_FUNCTION\n");
    eat(FUNCTION);
    TYPE();
    eat(ID);
    eat(LPAREN);
    ARGS();
    eat(RPAREN);
    eat(BEGIN);
    STMTS();
    eat(END);
    eat(ID);
    printf("Exiting FUNC_FUNCTION\n");
} 

void FUNC_PROCEDURE(void) {
    printf("Entering FUNC_PROCEDURE\n");
    eat(PROCEDURE);
    eat(ID);
    eat(LPAREN);
    ARGS();
    eat(RPAREN);
    eat(BEGIN);
    STMTS();
    eat(END);
    eat(ID);
    printf("Exiting FUNC_PROCEDURE\n");
}

void SUBPROGRAM(void) {
    switch (tok) {
        case FUNCTION: FUNC_FUNCTION(); break;
        case PROCEDURE: FUNC_PROCEDURE(); break;
        default: printf("Error at SUBPROGRAM\n");
        error();
    }
}  

void SUBPROGRAMS_(void) {
    switch (tok) {
        case FUNCTION: SUBPROGRAM(); SUBPROGRAMS_(); break;
        case PROCEDURE: SUBPROGRAM(); SUBPROGRAMS_(); break;
        case MAIN: break;
        default: printf("Error at SUBPROGRAMS_\n");
        error();
    }
}

void SUBPROGRAMS(void) {
    SUBPROGRAM();
    SUBPROGRAMS_();
}

void FUNC_MAIN(void) {
    eat(MAIN);
    eat(LPAREN);
    ARGS_();
    eat(RPAREN);
}

void FUNC_PROGRAM(void) { 
    SUBPROGRAMS_();
    FUNC_MAIN();
    eat(BEGIN);
    STMTS();
    printf("Expecting end for program\n");
    eat(END);
    eat(PROGRAM);
}

int main(int argc, char **argv) {
    //Read the archive received by parameter
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        printf("Could not open file %s\n", argv[1]);
        return 1;
    }

    advance();
    FUNC_PROGRAM();
    return 0;
}
