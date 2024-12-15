/*Grammar

PROGRAM ::= SUBPROGRAMS' MAIN begin STMTS end program
MAIN ::= main ( ARGS' )
VARS ::= VAR VARS'
VARS' ::= VARS
VARS' ::= ''
VAR ::= const TYPE ASSIGN
VAR ::= TYPE ASSIGN
VAR ::= REGISTER_DECL
TYPE ::= int 
TYPE ::= float 
TYPE ::= bool 
TYPE ::= char
TYPE ::= string

ASSIGN ::= id = ASSIGN'
ASSIGN ::= ARRAY_DECL
ASSIGN' ::= EXP;
ASSIGN' ::= cchar;
ASSIGN' ::= cstring;

ARRAY_DECL ::= id[SIZE] ARRAY_DECL';
ARRAY_DECL' ::= = carray
SIZE ::= EXP

REGISTER_DECL ::= register TYPE id;

LIT ::= cint
LIT ::= cfloat
LIT ::= cbool
O ::= id O'
O ::= ARRAY_ACCESS O'
O ::= REGISTER_ACCESS O'
O ::= O'
O' ::= LIT 
O' ::= ( EXP ) 

ARRAY_ACCESS ::= id[EXP]
REGISTER_ACCESS ::= register id

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
LU ::= not R 
LU ::= R
LC ::= LU LC'
LC' ::= and LU LC' 
LC' ::= ''
EXP ::= LC EXP'
EXP' ::= or LC EXP' 
EXP' ::= ''
EXPS ::= EXP ; EXPS'
EXPS' ::= EXP ; EXPS'
EXPS' ::= ''
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
SUBPROGRAMS ::= SUBPROGRAM SUBPROGRAMS'  
SUBPROGRAMS' ::= SUBPROGRAMS 
SUBPROGRAMS' ::= '' 
SUBPROGRAM ::= FUNCTION 
SUBPROGRAM ::= PROCEDURE 
FUNCTION ::= function TYPE id ( ARGS' ) begin STMTS end id 
PROCEDURE ::= procedure id ( ARGS' ) begin STMTS end id 
IF ::= if  EXP  STMTS ELIF ELSE end if 
ELIF ::= elif  EXP  STMTS 
ELIF ::= '' 
ELSE ::= else STMTS 
ELSE ::= '' 
SWITCH ::= switch  VAR  CASE DEFAULT end switch 
CASE ::= case  EXP : STMTS break CASE' 
CASE' ::= CASE 
CASE' ::= '' 
DEFAULT ::= default : STMTS break  
DEFAULT ::= '' 
FOR ::= for  ASSIGN ; EXP ; EXP STMTS end for 
LOOP ::= loop STMTS end loop
WHEN ::= exit when ( EXP )
UNLESS ::= unless ( EXP ) do STMT

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lex.yy.c"
#include "tokens.h"

//extern enum token getToken(void);

int tok;

//void advance() {tok=getToken();  printf("Token: %d\n", tok);}
void advance() {tok=yylex();  printf("Token: %d\n", tok);}
void eat(int t) {if (tok==t) advance(); else printf("Expected: %d\n" "Found: %d\n", t, tok);
error();}

void error() {fprintf(stderr, "Syntax error\n"); printf("Expected: %d\n", tok);
exit(1);}


void VARS(void) {
    VAR();
    VARS();
}

void VARS_(void) {
    VARS();
}

void VAR(void) {
    if (tok == CONST) {
        eat(CONST);
        TYPE();
        FUNC_ASSIGN();
    } else {
        TYPE();
        FUNC_ASSIGN();
    }
}

void TYPE(void) {
    switch (tok) {
        case INT: eat(INT); break;
        case FLOAT: eat(FLOAT); break;
        case BOOL: eat(BOOL); break;
        case CHAR: eat(CHAR); break;
        case STRING: eat(STRING); break;
        default: printf("Error at TYPE\n");
        error();
    }
}

void FUNC_ASSIGN(void) {
    if (tok == ID) {
        eat(ID);
        eat(ASSIGN);
        ASSIGN_();
    } else {
        ARRAY_DECL();
    }
}

void ASSIGN_(void) {
    if (tok == CINT || tok == CFLOAT || tok == CBOOL || tok == CCHAR || tok == CSTRING) {
        eat(tok);
    } else {
        EXP();
        eat(SEMICOLON);
    }
}

void ARRAY_DECL(void) {
    eat(ID);
    eat(LBRACKET);
    SIZE();
    ARRAY_DECL_();
}

void ARRAY_DECL_(void) {
    eat(ASSIGN);
    eat(CARRAY);
}

void SIZE(void) {
    EXP();
}

void REGISTER_DECL(void) {
    eat(REGISTER);
    TYPE();
    eat(ID);
    eat(SEMICOLON);
}

void LIT(void) {
    switch (tok) {
        case CINT: eat(CINT); break;
        case CFLOAT: eat(CFLOAT); break;
        case CBOOL: eat(CBOOL); break;
        case CCHAR: eat(CCHAR); break;
        case CSTRING: eat(CSTRING); break;
        default: printf("Error at LIT\n");
        error();
    }
}

void O(void) {
    switch (tok) {
        case ID: eat(ID); O_(); break;
        case REGISTER: eat(REGISTER); eat(ID); O_(); break;
        case LBRACKET: eat(LBRACKET); EXP(); eat(RBRACKET); O_(); break;
        case LPAREN: eat(LPAREN); EXP(); eat(RPAREN); O_(); break;
        case CINT: eat(CINT); break;
        case CFLOAT: eat(CFLOAT); break;
        case CBOOL: eat(CBOOL); break;
        case CCHAR: eat(CCHAR); break;
        case CSTRING: eat(CSTRING); break;
        default: printf("Error at O\n");
        error();
    }
}

void O_(void) {
    if (tok == PLUS || tok == MINUS) {
        AU();
    } else {
        return;
    }
}

void AU(void) {
    switch (tok) {
        case PLUS: eat(PLUS); O(); break;
        case MINUS: eat(MINUS); O(); break;
        default: printf("Error at AU\n");
        error();
    }
}

void AP(void) {
    O();
    AP_();
}

void AP_(void) {
    if (tok == POWER) {
        eat(POWER);
        AP();
    } else {
        return;
    }
}

void AF(void) {
    AP();
    AF_();
}

void AF_(void) {
    if (tok == MULTIPLY || tok == DIVIDE) {
        eat(tok);
        AP();
        AF_();
    } else {
        return;
    }
}

void AT(void) {
    AF();
    AT_();
}

void AT_(void) {
    if (tok == PLUS || tok == MINUS) {
        eat(tok);
        AF();
        AT_();
    } else {
        return;
    }
}

void R(void) {
    AT();
    R_();
}

void R_(void) {
    if (tok == EQUALS || tok == NOTEQUAL || tok == LESSTHAN || tok == GREATERTHAN || tok == LESSTHANOREQUAL || tok == GREATERTHANOREQUAL) {
        eat(tok);
        AT();
        R_();
    } else {
        return;
    }
}

void LU(void) {
    if (tok == NOT) {
        eat(NOT);
        R();
    } else {
        R();
    }
}

void LC(void) {
    LU();
    LC_();
}

void LC_(void) {
    if (tok == AND) {
        eat(AND);
        LU();
        LC_();
    } else {
        return;
    }
}

void EXP(void) {
    LC();
    EXP_();
}

void EXP_(void) {
    if (tok == OR) {
        eat(OR);
        LC();
        EXP_();
    } else {
        return;
    }
}

void EXPS(void) {
    EXP();
    eat(SEMICOLON);
    EXPS_();
}

void EXPS_(void) {
    if (tok == SEMICOLON) {
        eat(SEMICOLON);
        EXPS_();
    } else {
        return;
    }
}

void ARGS(void) {
    TYPE();
    eat(ID);
    ARGS_();
}

void ARGS_(void) {
    if (tok == COMMA) {
        eat(COMMA);
        ARGS();
    } else {
        return;
    }
}

void FUNC_IF(void) {
    eat(IF);
    EXP();
    STMTS();
    FUNC_ELIF();
    FUNC_ELSE();
    eat(END);
    eat(IF);
}

void FUNC_ELIF(void) {
    if (tok == ELIF) {
        eat(ELIF);
        EXP();
        STMTS();
    } else {
        return;
    }
}

void FUNC_ELSE(void) {
    if (tok == ELSE) {
        eat(ELSE);
        STMTS();
    } else {
        return;
    }
}

void FUNC_SWITCH(void) {
    eat(SWITCH);
    VAR();
    FUNC_CASE();
    FUNC_DEFAULT();
    eat(END);
    eat(SWITCH);
}

void FUNC_CASE(void) {
    eat(CASE);
    EXP();
    eat(COLON);
    STMTS();
    eat(BREAK);
    CASE_();
}

void CASE_(void) {
    if (tok == CASE) {
        FUNC_CASE();
    } else {
        return;
    }
}

void FUNC_DEFAULT(void) {
    if (tok == DEFAULT) {
        eat(DEFAULT);
        eat(COLON);
        STMTS();
        eat(BREAK);
    } else {
        return;
    }
}

void FUNC_FOR(void) {
    eat(FOR);
    FUNC_ASSIGN();
    eat(SEMICOLON);
    EXP();
    eat(SEMICOLON);
    EXP();
    STMTS();
    eat(END);
    eat(FOR);
}

void FUNC_LOOP(void) {
    eat(LOOP);
    STMTS();
    eat(END);
    eat(LOOP);
}

void FUNC_WHEN(void) {
    eat(WHEN);
    eat(LPAREN);
    EXP();
    eat(RPAREN);
}

void FUNC_UNLESS(void) {
    eat(UNLESS);
    eat(LPAREN);
    EXP();
    eat(RPAREN);
    eat(DO);
    STMT();
}

void STMTS(void) {
    STMT();
    STMTS_();
}

void STMTS_(void) {
    if (tok == SEMICOLON) {
        eat(SEMICOLON);
        STMTS();
    } else {
        return;
    }
}

void STMT(void) {
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
        default: printf("Error at STMT\n");
        error();
    }
}

void SUBPROGRAM(void) {
    switch (tok) {
        case FUNCTION: eat(FUNCTION); TYPE(); eat(ID); eat(LPAREN); ARGS(); eat(RPAREN); eat(BEGIN); STMTS(); eat(END); eat(ID); break;
        case PROCEDURE: eat(PROCEDURE); eat(ID); eat(LPAREN); ARGS(); eat(RPAREN); eat(BEGIN); STMTS(); eat(END); eat(ID); break;
        default: printf("Error at SUBPROGRAM\n");
        error();
    }
}

void SUBPROGRAMS_(void) {
    if (tok == FUNCTION || tok == PROCEDURE) {
        SUBPROGRAMS();
    } else {
        return;
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
