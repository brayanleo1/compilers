%{
    /* C Declarations */
    #include <stdio.h>
    #include <stdlib.h>
    //#include "y.tab.h" // If you are using YACC/Bison for parsing
    #include "tokens.h"
%}

%%

 /* Regular Expressions and Actions: */

"program"          { return PROGRAM; }
"main"             { return MAIN; }
"begin"            { return BEGIN; }
"end"              { return END; }
"const"            { return CONST; }
"int"              { return INT; }
"float"            { return FLOAT; }
"bool"             { return BOOL; }
"char"             { return CHAR; }
"string"           { return STRING; }
"procedure"        { return PROCEDURE; }
"function"         { return FUNCTION; }
"if"               { return IF; }
"then"             { return THEN; }
"do"               { return DO; }
"elif"             { return ELIF; }
"else"             { return ELSE; }
"switch"          { return SWITCH; }
"case"            { return CASE; }
"default"         { return DEFAULT; }
"for"             { return FOR; }
"loop"            { return LOOP; }
"exit"            { return EXIT; }
"when"            { return WHEN; }
"print"           { return PRINT; }
"return"          { return RETURN; }
"register"        { return REGISTER; }

"<-"               { return ASSIGN; }
":="               { return ASSIGN; }
"("              { return LPAREN; }
")"              { return RPAREN; }
":"                { return COLON; }
","                { return COMMA; }
";"                { return SEMICOLON; }
"["             { return LBRACKET; }
"]"             { return RBRACKET; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }
"."                { return DOT; }

">"                { return GREATERTHAN; }
"<"                { return LESSTHAN; }
">="               { return GREATERTHANOREQUAL; }
"<="               { return LESSTHANOREQUAL; }
"!="               { return NOTEQUAL; }
"&&"               { return AND; }
"||"               { return OR; }
"=="               { return EQUALS; }

"+"                { return PLUS; }
"-"                { return MINUS; }
"*"                { return MULTIPLY; }
"/"                { return DIVIDE; }
"%"                { return MODULUS; }
"**"               { return POWER; }

[0-9]+             { /*yylval.int_val = atoi(yytext);*/ return CINT; }
[0-9]+\.[0-9]*     { /*yylval.real_val = atof(yytext);*/ return CFLOAT; }
[0-9]*\.[0-9]+     { /*yylval.float_val = atof(yytext);*/ return CFLOAT; }
\'[^\']\'          { return CCHAR; }
\"[^"]*\"         { return CSTRING; }
"true"             { return CBOOL; }
"false"            { return CBOOL; }
"["[^"]*"]"        { return CARRAY; }

[a-zA-Z_][a-zA-Z0-9_]* { /*yylval.id = strdup(yytext);*/ return ID; }

[ \t\n\r]+         ;  /*Ignore whitespace */

.                  { printf("Unrecognized character: %s\n", yytext); return ERROR; }

%%

/* C Code */

int yywrap(void) {
   return 1;
}

int yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
   return 0;
}
