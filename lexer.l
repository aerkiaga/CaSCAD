%{
    #include "ast.h"
    #include "lexer.h"
    #include "y.tab.h"
    #include <string.h>
    const char* inp;
    int length;
    #define YY_INPUT(buf,result,max_size) \
    { \
        strncpy(buf, inp, max_size); \
        inp += max_size; \
        length -= max_size; \
        if(length <= 0) result = 0; \
        else result = max_size; \
    }
%}

%option noyywrap
%x LONG_COMMENT
%x STRING
%x IMPORT_PATH

%%

<INITIAL>[ \t\n]+ { }

    /* comments */ 
<INITIAL>\/\/[^\n]* { }
<INITIAL>"/*" { BEGIN(LONG_COMMENT); }
<LONG_COMMENT>"*/" { BEGIN(INITIAL); }
<LONG_COMMENT>\n { }
<LONG_COMMENT>. { }

    /* numbers */
<INITIAL>(\+|\-)?([0-9]+\.?[0-9]*|[0-9]*\.[0-9]+)((E|e)(\+|\-)?[0-9]+)? {
        yylval.d = atof(yytext);
        return LEX_NUM;
    }
<INITIAL>PI { yylval.d = 3.14159265358979323846; return LEX_NUM; }
    
    /* booleans */
<INITIAL>"true" { yylval.i = 1; return LEX_BOOL; }
<INITIAL>"false" { yylval.i = 0; return LEX_BOOL; }

    /* strings */
<INITIAL>\" { BEGIN(STRING); }
<STRING>[^\n\"\\]+ { yylval.s = strdup(yytext); return LEX_STR_FRAG; }
<STRING>\n { }
<STRING>\\\" { yylval.s = "\""; return LEX_STR_FRAG; }
<STRING>\\\\ { yylval.s = "\\"; return LEX_STR_FRAG; }
<STRING>\\t { yylval.s = "\t"; return LEX_STR_FRAG; }
<STRING>\\n { yylval.s = "\n"; return LEX_STR_FRAG; }
<STRING>\\x[0-9a-fA-F]{2} { yylval.s = strdup(yytext); return LEX_STR_UNICODE; }
<STRING>\\u[0-9a-fA-F]{4} { yylval.s = strdup(yytext); return LEX_STR_UNICODE; }
<STRING>\\U[0-9a-fA-F]{6} { yylval.s = strdup(yytext); return LEX_STR_UNICODE; }
<STRING>\" { BEGIN(INITIAL); }

    /* delimiters */
<INITIAL>\, { return ','; }
<INITIAL>\; { return ';'; }
<INITIAL>\: { return ':'; }
<INITIAL>\( { return '('; }
<INITIAL>\) { return ')'; }
<INITIAL>\[ { return '['; }
<INITIAL>\] { return ']'; }
<INITIAL>\{ { return '{'; }
<INITIAL>\} { return '}'; }

    /* operators and modifiers */
<INITIAL>\* { return '*'; }
<INITIAL>\! { return '!'; }
<INITIAL>\% { return '%'; }
<INITIAL>\# { return '#'; }
<INITIAL>\+ { return '+'; }
<INITIAL>\- { return '-'; }
<INITIAL>\/ { return '/'; }
<INITIAL>\^ { return '^'; }
<INITIAL>\<\= { return LEX_LESS_EQUAL; }
<INITIAL>\< { return '<'; }
<INITIAL>\>\= { return LEX_MORE_EQUAL; }
<INITIAL>\> { return '>'; }
<INITIAL>\=\= { return LEX_EQUAL; }
<INITIAL>\!\= { return LEX_NOT_EQUAL; }
<INITIAL>\&\& { return LEX_AND; }
<INITIAL>\|\| { return LEX_OR; }
<INITIAL>\= { return '='; }
<INITIAL>\? { return '?'; }

    /* dot notation indexing */
<INITIAL>\.x { yylval.i = 0; return LEX_DOT_INDEX; }
<INITIAL>\.y { yylval.i = 1; return LEX_DOT_INDEX; }
<INITIAL>\.z { yylval.i = 2; return LEX_DOT_INDEX; }

    /* import paths */
<INITIAL>include[ \t]\< { BEGIN(IMPORT_PATH); return LEX_INCLUDE; }
<INITIAL>use[ \t]\< { BEGIN(IMPORT_PATH); return LEX_USE; }
<IMPORT_PATH>[^\n\>]+ { yylval.s = strdup(yytext); return LEX_PATH_FRAG; }
<IMPORT_PATH>\> { BEGIN(INITIAL); }

    /* keywords */
<INITIAL>undef { return LEX_UNDEF; }
<INITIAL>function { return LEX_FUNCTION; }
<INITIAL>module { return LEX_MODULE; }
<INITIAL>if { return LEX_IF; }
<INITIAL>else { return LEX_ELSE; }
<INITIAL>for { return LEX_FOR; }
<INITIAL>intersection_for { return LEX_INTERSECTION_FOR; }
<INITIAL>let { return LEX_LET; }
<INITIAL>each { return LEX_EACH; }

    /* identifiers */
<INITIAL>\$?[a-zA-Z0-9_]+ { yylval.s = strdup(yytext); return LEX_IDENTIFIER; }

%%

void lexer_load(const char *text) {
    inp = text;
    length = strlen(inp);
}

void yyerror(char const *msg) {
}
