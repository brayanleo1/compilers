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
#include "rules.c"

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

int table[55][60] = {
{-1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,-1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,4,5,5,5,5,5,-1,-1,-1,-1,-1,-1,-1,-1,6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,7,8,9,10,11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,12,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,13,-1,-1,-1,-1,-1,-1,-1,13,-1,-1,14,15,16,-1,-1,-1,13,13,13,13,-1,13,13,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,17,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,18,-1,-1,-1,-1,-1,-1,-1,18,-1,-1,-1,-1,-1,-1,-1,-1,18,18,18,18,-1,18,18,-1,-1,-1,-1,-1,-1,-1,-1,-1,18,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,19,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20,21,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,23,-1,-1,-1,-1,-1,-1,-1,-1,24,24,24,25,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,0,-1,-1,-1,0,0,0,0,0,0,0,0,-1,0,-1,-1,-1,26,0,0,-1,-1,-1,0,93,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,-1,0,0,-1,0,0,0,-1,0,0,0},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,27,-1,-1,-1,-1,-1,-1,-1,-1,27,27,27,27,-1,28,29,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,30,-1,-1,-1,-1,-1,-1,-1,31,-1,-1,-1,-1,-1,-1,-1,-1,31,31,31,31,-1,31,31,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,32,-1,-1,-1,-1,-1,-1,-1,32,-1,-1,-1,-1,-1,-1,-1,-1,32,32,32,32,-1,32,32,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,0,-1,-1,-1,0,0,0,0,0,0,0,0,-1,0,-1,-1,-1,-1,0,0,-1,-1,-1,0,-1,0,0,33,0,0,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,-1,0,0,-1,0,0,0,-1,0,0,0},
{-1,-1,-1,-1,-1,34,-1,-1,-1,-1,-1,-1,-1,34,-1,-1,-1,-1,-1,-1,-1,-1,34,34,34,34,-1,34,34,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,0,-1,-1,-1,0,0,0,0,0,0,0,0,-1,0,-1,-1,-1,-1,0,0,-1,-1,-1,0,-1,0,0,-1,35,36,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,-1,0,0,-1,0,0,0,-1,0,0,0},
{-1,-1,-1,-1,-1,37,-1,-1,-1,-1,-1,-1,-1,37,-1,-1,-1,-1,-1,-1,-1,-1,37,37,37,37,-1,37,37,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,0,-1,-1,-1,0,0,0,0,0,0,0,0,-1,0,-1,-1,-1,-1,0,0,-1,-1,-1,0,-1,38,39,-1,-1,-1,0,0,0,0,0,0,-1,0,0,0,0,0,0,0,0,0,0,-1,0,0,-1,0,0,0,-1,0,0,0},
{-1,-1,-1,-1,-1,40,-1,-1,-1,-1,-1,-1,-1,40,-1,-1,-1,-1,-1,-1,-1,-1,40,40,40,40,-1,40,40,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,0,-1,-1,-1,0,0,0,0,0,0,0,0,-1,0,-1,-1,-1,-1,0,0,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,41,42,43,44,45,46,-1,0,0,0,0,0,0,0,0,0,0,-1,0,0,-1,0,0,0,-1,0,0,0},
{-1,-1,-1,-1,-1,47,-1,-1,-1,-1,-1,-1,-1,47,-1,-1,-1,-1,-1,-1,-1,-1,47,47,47,47,-1,47,47,-1,-1,-1,-1,-1,-1,-1,-1,-1,48,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,49,-1,-1,-1,-1,-1,-1,-1,49,-1,-1,-1,-1,-1,-1,-1,-1,49,49,49,49,-1,49,49,-1,-1,-1,-1,-1,-1,-1,-1,-1,49,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,0,-1,-1,-1,0,0,0,0,0,0,0,0,-1,0,-1,-1,-1,-1,0,0,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,50,0,0,0,0,0,0,0,0,0,-1,0,0,-1,0,0,0,-1,0,0,0},
{-1,-1,-1,-1,-1,51,-1,-1,-1,-1,-1,-1,-1,51,-1,-1,-1,-1,-1,-1,-1,-1,51,51,51,51,-1,51,51,-1,-1,-1,-1,-1,-1,-1,-1,-1,51,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,0,-1,-1,-1,0,0,0,0,0,0,0,0,-1,0,-1,-1,-1,-1,0,0,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,52,0,0,0,0,0,0,0,0,-1,0,0,-1,0,0,0,-1,0,0,0},
{-1,-1,-1,-1,-1,53,-1,-1,-1,-1,-1,-1,-1,53,-1,-1,-1,-1,-1,-1,-1,-1,53,53,53,53,-1,53,53,-1,-1,-1,-1,-1,-1,-1,-1,-1,53,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,54,0,-1,-1,-1,-1,-1,-1,54,-1,-1,-1,-1,-1,-1,-1,-1,54,54,54,54,-1,54,54,-1,-1,-1,-1,-1,-1,-1,-1,-1,54,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,55,55,55,55,55,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,56,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,57,57,57,57,57,57,57,-1,-1,-1,-1,-1,-1,-1,57,-1,-1,-1,57,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,57,-1,57,57,-1,-1,57,-1,-1,-1,-1,57,57,57,-1,57,-1,57},
{-1,-1,0,-1,-1,-1,-1,58,58,58,58,58,58,58,-1,-1,-1,-1,-1,-1,-1,58,-1,-1,-1,58,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,58,0,58,58,0,0,58,-1,-1,0,-1,58,58,58,-1,58,-1,58},
{-1,-1,-1,-1,-1,-1,-1,59,59,59,59,59,59,60,-1,-1,-1,-1,-1,-1,-1,59,-1,-1,-1,61,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,62,-1,62,63,-1,-1,64,-1,-1,-1,-1,65,66,67,-1,68,-1,69},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,70,-1,70,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,71,-1,71,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,72,-1,73,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,74,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,94,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,75,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,76,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,77,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,78,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,79,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,80,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,81,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,82,-1,-1,0,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,83,-1,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,84,-1,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,85,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,86,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,87,-1,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,88},
{-1,-1,-1,-1,-1,89,-1,-1,-1,-1,-1,-1,-1,89,-1,-1,90,91,92,-1,-1,-1,89,89,89,89,-1,89,89,-1,-1,-1,-1,-1,-1,-1,-1,-1,89,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
};

#define STACK_SIZE 1000

// Stack structure
typedef struct {
    int items[STACK_SIZE];
    int top;
} Stack;

void push(Stack *stack, int value) {
    if (stack->top >= STACK_SIZE - 1) {
        fprintf(stderr, "Stack overflow\n");
        printf(stack->top);
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
    return stack->items[stack->top];
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

    Stack stack;
    stack.top = -1;

    printf("Pushing S to stack\n");

    push(&stack, END_OF_FILE);
    push(&stack, RULE_PROGRAM);
    int token = yylex();
    printf("New Token = %d\n", token);
    while (stack.top >= 0) {
        int top = peek(&stack);
        printf("Top: %d\n", top);

        if(top == END_OF_FILE) {
            printf("End of file\n");
            break;
        }

        if(top == -1) {
            //print stack
            printf("Stack: ");
            for(int i = 0; i <= stack.top; i++) {
                printf("%d ", stack.items[i]);
            }
        }

        //if for if top is production rule or token
        if (top < 0 || top > 1054) {
            fprintf(stderr, "Syntax error\n");
            exit(EXIT_FAILURE);
        } else if(top < 1000) { //It is a token
            printf("Name of top token: %s\n", getName(top));
            if (top == token) {
                pop(&stack);
                token = yylex();
                printf("Token name = %d\n", getName(token));
                printf("New Token = %d\n", token);
            } else { //It is a token but it is not the same as the one on top of the stack
                fprintf(stderr, "Syntax error\n");
                exit(EXIT_FAILURE);
            }
        } else { //It is a rule
            printf("Possible rule\n");
            printf("Token = %d\n", token);
            printf("Top = %d\n", top);
            printf("Top - 1000 = %d\n", top - 1000);
            printf("Table[%d][%d] = %d\n", top - 1000, token, table[top - 1000][token]);
            int production = table[top - 1000][token]; //Need to subtract 1000 to get the token number at the table
            if (production == -1) {
                fprintf(stderr, "Syntax error\n");
                exit(EXIT_FAILURE);
            } 
            //It is a rule
            if( production == 0) {
                pop(&stack);
                printf("Empty production\n");
                continue;
            } else {
                printf("Production: %d\n", production);
                int* rules = getRules(production);

                static int stRules[20];
                stRules[0] = rules[0];
                stRules[1] = rules[1];
                stRules[2] = rules[2];
                stRules[3] = rules[3];
                stRules[4] = rules[4];
                stRules[5] = rules[5];
                stRules[6] = rules[6];
                stRules[7] = rules[7];
                stRules[8] = rules[8];
                stRules[9] = rules[9];
                stRules[10] = rules[10];
                stRules[11] = rules[11];
                stRules[12] = rules[12];
                stRules[13] = rules[13];
                stRules[14] = rules[14];
                stRules[15] = rules[15];
                stRules[16] = rules[16];
                stRules[17] = rules[17];
                stRules[18] = rules[18];
                stRules[19] = rules[19];
                
                printf("Got rules\n");

                pop(&stack);
                printf("Popped rule from stack\n");
                
                // Calculate the length knowing that the last element is -1
                int length = 0;
                while (stRules[length] != -1) {
                    length++;
                }
                printf("Length: %d\n", length);

                
                // Print the rules in normal order
                for(int i = 0; i < length; i++) {
                    printf("Rule %d: %d\n", i, stRules[i]);
                }
                

                while (length > -1) {
                    if (stRules[length] != -1) {
                        push(&stack, stRules[length]); 
                        printf("Pushed rule %d to stack\n", stRules[length]);
                    }
                    length--;}

            }
        }
    }
    printf("Syntax is correct\n");
    return 0;
}