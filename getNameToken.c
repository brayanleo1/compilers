#include "tokens.h"

/*
#define PROGRAM 1
#define MAIN 2
#define BEGIN 3
#define END 4
#define FUNCTION 5
#define PROCEDURE 6
#define IF 7
#define THEN 8
#define ELSE 9
#define SWITCH 10
#define CASE 11
#define DEFAULT 12
#define FOR 13
#define LOOP 14
#define WHEN 15
#define UNLESS 16
#define PRINT 17
#define ID 18
#define INT 19
#define FLOAT 20
#define BOOL 21
#define CHAR 22
#define STRING 23
#define REGISTER 24
#define CONST 25
#define AND 26
#define OR 27
#define NOT 28
#define PLUS 29
#define MINUS 30
#define MULTIPLY 31
#define DIVIDE 32
#define MODULUS 33
#define EQUALS 34
#define NOTEQUAL 35
#define LESSTHAN 36
#define GREATERTHAN 37
#define LESSTHANOREQUAL 38
#define GREATERTHANOREQUAL 39
#define ASSIGN 40
#define SEMICOLON 41
#define COMMA 42
#define COLON 43
#define LPAREN 44
#define RPAREN 45
#define LBRACKET 46
#define RBRACKET 47
#define LBRACE 48
#define RBRACE 49
#define CINT 50
#define CFLOAT 51
#define CBOOL 52
#define CCHAR 53
#define CSTRING 54
#define END_OF_FILE 55
#define ERROR 56
#define DO 57
#define BREAK 58
#define ELIF 59
#define CARRAY 60
#define POWER 61
#define EXIT 62
#define RETURN 63
*/

const char* getName(int token) {
    switch (token) {
        case ID: return "ID";
        case INT: return "INT";
        case FLOAT: return "FLOAT";
        case STRING: return "STRING";
        case CHAR: return "CHAR";
        case BOOL: return "BOOL";
        case IF: return "IF";
        case ELSE: return "ELSE";
        case FOR: return "FOR";
        case RETURN: return "RETURN";
        case BREAK: return "BREAK";
        case CBOOL: return "CBOOL";
        case AND: return "AND";
        case OR: return "OR";
        case NOT: return "NOT";
        case EQUALS: return "EQUALS";
        case NOTEQUAL: return "NOTEQUAL";
        case GREATERTHAN : return "GREATERTHAN";
        case LESSTHAN: return "LESSTHAN";
        case GREATERTHANOREQUAL: return "GREATERTHANOREQUAL";
        case LESSTHANOREQUAL: return "LESSTHANOREQUAL";
        case PLUS: return "PLUS";
        case MINUS: return "MINUS";
        case MULTIPLY: return "MULTIPLY";
        case DIVIDE: return "DIVIDE";
        case MODULUS: return "MODULUS";
        case ASSIGN: return "ASSIGN";
        case LPAREN: return "LPAREN";
        case RPAREN: return "RPAREN";
        case LBRACE: return "LBRACE";
        case RBRACE: return "RBRACE";
        case LBRACKET: return "LBRACKET";
        case RBRACKET: return "RBRACKET";
        case COMMA: return "COMMA";
        case SEMICOLON: return "SEMICOLON";
        case COLON: return "COLON";
        case ERROR: return "ERROR";
        case END: return "END";
        case END_OF_FILE: return "END_OF_FILE";
        case PROGRAM: return "PROGRAM";
        case MAIN: return "MAIN";
        case FUNCTION: return "FUNCTION";
        case PROCEDURE: return "PROCEDURE";
        case SWITCH: return "SWITCH";
        case CASE: return "CASE";
        case DEFAULT: return "DEFAULT";
        case LOOP: return "LOOP";
        case WHEN: return "WHEN";
        case UNLESS: return "UNLESS";
        case PRINT: return "PRINT";
        case REGISTER: return "REGISTER";
        case CONST: return "CONST";
        case DO: return "DO";
        case ELIF: return "ELIF";
        case CINT: return "CINT";
        case CFLOAT: return "CFLOAT";
        case CCHAR: return "CCHAR";
        case CSTRING: return "CSTRING";
        case CARRAY: return "CARRAY";
        case POWER: return "POWER";
        case EXIT: return "EXIT";
        case BEGIN: return "BEGIN";
        case DOT: return "DOT";
        case CALL: return "CALL";
        default: return "UNKNOWN";
    }
}