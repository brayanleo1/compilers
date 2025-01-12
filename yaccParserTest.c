#include "lex.yy.c"
#include "y.tab.c"

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
    //Call the parser
    int success = yyparse();
    if (success == 0) {
        printf("Parsing was successful\n");
    } else {
        printf("Parsing failed\n");
        // Where the error occurred
        printf("Error occurred at line %d\n", yylineno);
        // What the error was
        printf("Error occurred at token %s\n", yytext);
    }

    fclose(yyin);

    //return yyparse();
}