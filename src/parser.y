%{
    #include "ast.h"
    #include "lexer.h"
    #include "strutils.h"
    #include <stdlib.h>
    #include <string.h>
    extern int yyparse();
    extern int yylex();
    extern void yyerror(char const *msg);
    ast_t outp;
%}

%union {
    int i;
    double d;
    char *s;
    ast_t a;
}

%{
%}

    /* tokens */
%token <d> LEX_NUM
%token <i> LEX_BOOL
%token <s> LEX_STR_FRAG
%token <s> LEX_STR_UNICODE

%token ',';
%token '.';
%token ';';
%token ':';
%token '(';
%token ')';
%token '[';
%token ']';
%token '{';
%token '}';

%token '*';
%token '!';
%token '%';
%token '#';
%token '+';
%token '-';
%token '/';
%token '^';
%token LEX_LESS_EQUAL;
%token '<';
%token LEX_MORE_EQUAL;
%token '>';
%token LEX_EQUAL;
%token LEX_NOT_EQUAL;
%token LEX_AND;
%token LEX_OR;
%token '=';
%token '?';

%token <i> LEX_DOT_INDEX

%token LEX_INCLUDE;
%token LEX_USE;
%token <s> LEX_PATH_FRAG

%token LEX_UNDEF
%token LEX_FUNCTION
%token LEX_MODULE
%token LEX_IF
%token LEX_ELSE
%token LEX_FOR
%token LEX_INTERSECTION_FOR
%token LEX_LET
%token LEX_EACH

%token <s> LEX_IDENTIFIER

    /* precedence and associativity */
%nonassoc LEX_FUNCTION LEX_LET
%nonassoc NON_ELSE
%nonassoc LEX_ELSE
%right '?'
%left LEX_OR
%left LEX_AND
%left LEX_EQUAL LEX_NOT_EQUAL
%left LEX_LESS_EQUAL '<' LEX_MORE_EQUAL '>'
%left '+' '-'
%left '*' '/' '%'
%right '^'
%nonassoc '!'
%nonassoc '[' LEX_DOT_INDEX

    /* nonterminals */
%type <a> top_statements statements statement operator
%type <a> expression vector if_header for_header
%type <a> intersection_for_header let_header expr_list proto_list
%type <a> param_list assignment_list function_call module_call
%type <a> assignment include_statement use_statement
%type <s> string import_path

%%
input:
    top_statements { outp = $1; }
;

top_statements:
    { $$ = ast_statement_list(); }
|   top_statements statement { $$ = ast_append_child($1, $2); }
|   top_statements use_statement { $$ = ast_append_child($1, $2); }
;

statements:
    { $$ = ast_statement_list(); }
|   statements statement { $$ = ast_append_child($1, $2); }
;

statement:
    assignment ';' { $$ = $1; }
|   module_call ';' { $$ = $1; }
|   '{' statements '}' { $$ = $2; }
|   operator '{' statements '}' { $$ = ast_append_child($1, $3); }
|   if_header statement %prec NON_ELSE { $$ = ast_if_statement($1, $2, NULL); }
|   if_header statement LEX_ELSE statement { $$ = ast_if_statement($1, $2, $4); }
|   for_header statement { $$ = ast_for_statement($1, $2); }
|   intersection_for_header statement { $$ = ast_intersection_for_statement($1, $2); }
|   let_header statement { $$ = ast_let_statement($1, $2); }
|   LEX_FUNCTION LEX_IDENTIFIER '(' proto_list ')' '=' expression ';'
        { $$ = ast_bind_statement(strdup($2), ast_function_literal($4, $7)); }
|   LEX_MODULE LEX_IDENTIFIER '(' proto_list ')' statement
        { $$ = ast_bind_statement(strdup($2), ast_module_literal($4, $6)); }
|   include_statement { $$ = $1; }
;

operator:
    module_call { $$ = ast_module_operator($1); }
|   '*' { $$ = ast_predefined_operator(OPERATOR_DISABLE); }
|   '!' { $$ = ast_predefined_operator(OPERATOR_SHOWONLY); }
|   '#' { $$ = ast_predefined_operator(OPERATOR_HIGHLIGHT); }
|   '%' { $$ = ast_predefined_operator(OPERATOR_TRANSPARENT); }
;

expression:
    LEX_IDENTIFIER { $$ = ast_identifier_expression($1); }
|   function_call { $$ = $1; }
|   '(' expression ')' { $$ = $2; }
|   expression '?' expression ':' expression %prec '?' { $$ = ast_if_expression($1, $3, $5); }
|   expression LEX_OR expression { $$ = ast_binary_expression(BINARY_OP_OR, $1, $3); }
|   expression LEX_AND expression { $$ = ast_binary_expression(BINARY_OP_AND, $1, $3); }
|   expression LEX_EQUAL expression { $$ = ast_binary_expression(BINARY_OP_EQUAL, $1, $3); }
|   expression LEX_NOT_EQUAL expression { $$ = ast_binary_expression(BINARY_OP_NOT_EQUAL, $1, $3); }
|   expression LEX_LESS_EQUAL expression { $$ = ast_binary_expression(BINARY_OP_LESS_EQUAL, $1, $3); }
|   expression '<' expression { $$ = ast_binary_expression(BINARY_OP_LESS, $1, $3); }
|   expression LEX_MORE_EQUAL expression { $$ = ast_binary_expression(BINARY_OP_MORE_EQUAL, $1, $3); }
|   expression '>' expression { $$ = ast_binary_expression(BINARY_OP_MORE, $1, $3); }
|   expression '+' expression { $$ = ast_binary_expression(BINARY_OP_ADD, $1, $3); }
|   expression '-' expression { $$ = ast_binary_expression(BINARY_OP_SUBTRACT, $1, $3); }
|   expression '*' expression { $$ = ast_binary_expression(BINARY_OP_MULTIPLY, $1, $3); }
|   expression '/' expression { $$ = ast_binary_expression(BINARY_OP_DIVIDE, $1, $3); }
|   expression '%' expression { $$ = ast_binary_expression(BINARY_OP_MODULO, $1, $3); }
|   expression '^' expression { $$ = ast_binary_expression(BINARY_OP_RAISE, $1, $3); }
|   '-' expression { $$ = ast_unary_expression(UNARY_OP_MINUS, $2); }
|   '!' expression { $$ = ast_unary_expression(UNARY_OP_NOT, $2); }
|   expression '[' expression ']' { $$ = ast_vector_index($1, $3); }
|   expression LEX_DOT_INDEX { $$ = ast_vector_index($1, ast_number_literal((double) $2)); }
|   vector { $$ = $1; }
|   '[' expression ':' expression ']' { $$ = ast_range_literal($2, ast_number_literal(1.0), $4); }
|   '[' expression ':' expression ':' expression ']' { $$ = ast_range_literal($2, $4, $6); }
|   LEX_UNDEF { $$ = ast_undef_literal(); }
|   LEX_NUM { $$ = ast_number_literal($1); }
|   LEX_BOOL { $$ = ast_bool_literal($1); }
|   string { $$ = ast_string_literal($1); }
|   LEX_FUNCTION '(' proto_list ')' expression %prec LEX_FUNCTION { $$ = ast_function_literal($3, $5); }
|   let_header expression %prec LEX_LET { $$ = ast_let_expression($1, $2); }
;

string:
    string LEX_STR_FRAG { $$ = append_string($1, $2); }
|   string LEX_STR_UNICODE { $$ = append_string($1, encode_utf8_escape($2)); }
|   LEX_STR_FRAG { $$ = append_string(get_empty_string(), $1); }
|   LEX_STR_UNICODE { $$ = append_string(get_empty_string(), encode_utf8_escape($1)); }
;

vector:
    '[' expr_list ']' { $$ = ast_vector_literal($2); }
|   '[' expr_list ',' ']' { $$ = ast_vector_literal($2); }
|   '[' for_header expression ']' {
            $$ = ast_list_comprehension($2, ast_bool_literal(1), 0, $3);
        }
|   '[' for_header LEX_EACH expression ']' {
            $$ = ast_list_comprehension($2, ast_bool_literal(1), 1, $4);
        }
|   '[' for_header if_header expression %prec NON_ELSE']' {
            $$ = ast_list_comprehension($2, $3, 0, $4);
        }
|   '[' for_header if_header expression LEX_ELSE expression']' {
            $$ = ast_list_comprehension($2, ast_bool_literal(1), 0, ast_if_expression($3, $4, $6));
        }
;

if_header:
    LEX_IF '(' expression ')' { $$ = $3; }
;

for_header:
    LEX_FOR '(' assignment_list ')' { $$ = $3; }
;

intersection_for_header:
    LEX_INTERSECTION_FOR '(' assignment ')' { $$ = $3; }
;

let_header:
    LEX_LET '(' assignment_list ')' { $$ = $3; }
;

expr_list:
    { $$ = ast_expression_list(); }
|   expression { $$ = ast_append_child(ast_expression_list(), $1); }
|   expr_list ',' expression { $$ = ast_append_child($1, $3); }
;

proto_list:
    { $$ = ast_proto_list(); }
|   LEX_IDENTIFIER
        { $$ = ast_append_child(ast_proto_list(), ast_bind_statement(strdup($1), ast_undef_literal())); }
|   assignment { $$ = ast_append_child(ast_proto_list(), $1); }
|   LEX_IDENTIFIER ',' proto_list
        { $$ = ast_append_child($3, ast_bind_statement(strdup($1), ast_undef_literal())); }
|   assignment ',' proto_list { $$ = ast_append_child($3, $1); }
;

param_list:
    { $$ = ast_parameter_list(); }
|   expression { $$ = ast_append_child(ast_parameter_list(), $1); }
|   assignment { $$ = ast_append_child(ast_parameter_list(), $1); }
|   expression ',' param_list { $$ = ast_append_child($3, $1); }
|   assignment ',' param_list { $$ = ast_append_child($3, $1); }
;

assignment_list:
    { $$ = ast_assignment_list(); }
|   assignment { $$ = ast_append_child(ast_assignment_list(), $1); }
|   assignment ',' assignment_list { $$ = ast_append_child($3, $1); }
;

function_call:
    LEX_IDENTIFIER '(' param_list ')' { $$ = ast_function_call($1, $3); }
;

module_call:
    LEX_IDENTIFIER '(' param_list ')' { $$ = ast_module_call($1, $3); }
;

assignment:
    LEX_IDENTIFIER '=' expression { $$ = ast_bind_statement(strdup($1), $3); }
;

include_statement:
    LEX_INCLUDE import_path { $$ = ast_include_statement($2); }
;

use_statement:
    LEX_USE import_path { $$ = ast_use_statement($2); }
;

import_path:
    { $$ = get_empty_string(); }
|   import_path LEX_PATH_FRAG { $$ = append_string($1, $2); }
;

%%

ast_t parser_run() {
    yyparse();
    return outp;
}
