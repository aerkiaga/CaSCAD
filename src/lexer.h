#include <stdio.h>

extern void lexer_load(const char *text);
extern int yylex(void);
extern void yyerror(char const *msg);
extern void yyrestart(FILE *input_file);
