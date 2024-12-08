%{
    /* C Declarations */
    #include <stdio.h>
    #include <stdlib.h>
    //#include "y.tab.h" // If you are using YACC/Bison for parsing
%}

%%

 /* Regular Expressions and Actions: */

"program"          { printf("Program\n");/*  return PROGRAM;*/ }
"main"             { printf("Main\n");/*  return MAIN;*/ }
"begin"            { printf("Begin\n");/*  return BEGIN;*/ }
"end"              { printf("End\n");/*  return END;*/ }
"const"            { printf("Const\n");/*  return CONST;*/ }
"int"              { printf("Int\n");/*  return INT;*/ }
"float"            { printf("Float\n");/*  return FLOAT;*/ }
"bool"             { printf("Bool\n");/*  return BOOL;*/ }
"char"             { printf("Char\n");/*  return CHAR;*/ }
"string"           { printf("String\n");/*  return STRING;*/ }
"procedure"        { printf("Procedure\n");/*  return PROCEDURE;*/ }
"function"         { printf("Function\n");/*  return FUNCTION;*/ }
"if"               { printf("If\n");/*  return IF;*/ }
"then"             { printf("Then\n");/*  return THEN;*/ }
"do"               { printf("Do\n");/*  return DO;*/ }
"elif"             { printf("Elif\n");/*  return ELIF;*/ }
"else"             { printf("Else\n");/*  return ELSE;*/ }
"switch"          { printf("Switch\n");/*  return SWITCH;*/ }
"case"            { printf("Case\n");/*  return CASE;*/ }
"default"         { printf("Default\n");/*  return DEFAULT;*/ }
"for"             { printf("For\n");/*  return FOR;*/ }
"loop"            { printf("Loop\n");/*  return LOOP;*/ }
"exit"            { printf("Exit\n");/*  return EXIT;*/ }
"when"            { printf("When\n");/*  return WHEN;*/ }
"print"           { printf("Print\n");/*  return PRINT;*/ }
"return"          { printf("Return\n");/*  return RETURN;*/ }
"register"        { printf("Register\n");/*  return REGISTER;*/ }

"<-"               { printf("Assign\n");/*  return ASSIGN;*/ }
":="               { printf("Assign\n");/*  return ASSIGN;*/ }
"("              { printf("LParen\n");/*  return LPAREN;*/ }
")"              { printf("RParen\n");/*  return RPAREN;*/ }
":"                { printf("Colon\n");/*  return COLON;*/ }
","                { printf("Comma\n");/*  return COMMA;*/ }
";"                { printf("Semicolon\n");/*  return SEMICOLON;*/ }
"["             { printf("LBracket\n");/*  return LBRACKET;*/ }
"]"             { printf("RBracket\n");/*  return RBRACKET;*/ }

">"                { printf("GreaterThan\n");/*  return GREATERTHAN;*/ }
"<"                { printf("LessThan\n");/*  return LESSTHAN;*/ }
">="               { printf("GreaterThanOrEqual\n");/*  return GREATERTHANOREQUAL;*/ }
"<="               { printf("LessThanOrEqual\n");/*  return LESSTHANOREQUAL;*/ }
"!="               { printf("NotEqual\n");/*  return NOTEQUAL;*/ }
"&&"               { printf("And\n");/*  return AND;*/ }
"||"               { printf("Or\n");/*  return OR;*/ }
"=="               { printf("Equals\n");/*  return EQUALS;*/ }

"+"                { printf("Plus\n");/*  return PLUS;*/ }
"-"                { printf("Minus\n");/*  return MINUS;*/ }
"*"                { printf("Multiply\n");/*  return MULTIPLY;*/ }
"/"                { printf("Divide\n");/*  return DIVIDE;*/ }
"%"                { printf("Modulus\n");/*  return MODULUS;*/ }
"**"               { printf("Power\n");/*  return POWER;*/ }

[0-9]+             { printf("CInt\n"); /*yylval.int_val = atoi(yytext);  return CINT;*/ }
[0-9]+\.[0-9]*     { printf("CFloat\n");/*  yylval.float_val = atof(yytext); return CFLOAT;*/ }
[0-9]*\.[0-9]+     { printf("CFloat\n");/*  yylval.float_val = atof(yytext); return CFLOAT;*/ }
\'[^\']\'          { printf("CChar\n");/*  return CCHAR;*/ }
\"[^"]*\"         { printf("CString\n");/*  return CSTRING;*/ }
"true"             { printf("CBool\n");/*  return CBOOL;*/ }
"false"            { printf("CBool\n");/*  return CBOOL;*/ }
"["[^"]*"]"        { printf("CArray\n");/*  return CARRAY;*/ }

[a-zA-Z_][a-zA-Z0-9_]* { printf("ID\n"); /*yylval.id = strdup(yytext); return ID;*/ }

[ \t\n\r]+         ; /* Ignore whitespace */

.                  { printf("Unrecognized character: %s\n", yytext);/*  return ERROR;*/ }

%%

/* C Code */

int yywrap(void) {
    return 1;
}

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Could not open file");
            return 1;
        }
        yyin = file;
    }
    yylex();
    return 0;
}
