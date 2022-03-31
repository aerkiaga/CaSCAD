#ifndef AST_H
#define AST_H

#include "tree.h"
#include <stdint.h>

typedef tree_t ast_t;

enum {
    AST_TYPE_STATEMENT_LIST,                // statement...
    AST_TYPE_EXPRESSION_LIST,
    AST_TYPE_PROTO_LIST,
    AST_TYPE_PARAMETER_LIST,
    AST_TYPE_ASSIGNMENT_LIST,
    
    AST_TYPE_FN_OPERATOR,                   // function_call  statement
    AST_TYPE_PRE_OPERATOR,                  // type  statement
    
    AST_TYPE_BIND_STATEMENT,
    AST_TYPE_IF_STATEMENT,                  // expression  statement  statement
    AST_TYPE_FOR_STATEMENT,                 // assignment_list  statement
    AST_TYPE_INTERSECTION_FOR_STATEMENT,    // assignment  statement
    AST_TYPE_LET_STATEMENT,                 // assignment_list  statement
    AST_TYPE_INCLUDE_STATEMENT,             // path
    AST_TYPE_USE_STATEMENT,                 // path
    
    AST_TYPE_UNDEF_LITERAL,
    AST_TYPE_NUMBER_LITERAL,
    AST_TYPE_BOOL_LITERAL,
    AST_TYPE_STRING_LITERAL,
    AST_TYPE_RANGE_LITERAL,
    AST_TYPE_VECTOR_LITERAL,
    AST_TYPE_FUNCTION_LITERAL,
    AST_TYPE_MODULE_LITERAL,
    
    AST_TYPE_FUNCTION_CALL,
    AST_TYPE_IF_EXPRESSION,
    AST_TYPE_LET_EXPRESSION,
    AST_TYPE_BINARY_EXPRESSION,
    AST_TYPE_UNARY_EXPRESSION,
    AST_TYPE_VECTOR_INDEX,
    AST_TYPE_LIST_COMPREHENSION,
};

enum {
    OPERATOR_DISABLE,
    OPERATOR_SHOWONLY,
    OPERATOR_HIGHLIGHT,
    OPERATOR_TRANSPARENT,
};

enum {
    BINARY_OP_OR,
    BINARY_OP_AND,
    BINARY_OP_EQUAL,
    BINARY_OP_NOT_EQUAL,
    BINARY_OP_LESS_EQUAL,
    BINARY_OP_LESS,
    BINARY_OP_MORE_EQUAL,
    BINARY_OP_MORE,
    BINARY_OP_ADD,
    BINARY_OP_SUBTRACT,
    BINARY_OP_MULTIPLY,
    BINARY_OP_DIVIDE,
    BINARY_OP_MODULO,
    BINARY_OP_RAISE,
};

enum {
    UNARY_OP_MINUS,
    UNARY_OP_NOT,
};

extern ast_t ast_append_child(ast_t ast, ast_t node);
extern ast_t ast_empty(uintptr_t type);
extern void ast_set_type(ast_t ast, uintptr_t type);

extern ast_t ast_statement_list();
extern ast_t ast_expression_list();
extern ast_t ast_proto_list();
extern ast_t ast_parameter_list();
extern ast_t ast_assignment_list();

extern ast_t ast_function_operator(ast_t value);
extern ast_t ast_predefined_operator(uintptr_t type);

extern ast_t ast_bind_statement(char* name, ast_t value);
extern ast_t ast_if_statement(ast_t condition, ast_t statement, ast_t else_stmt);
extern ast_t ast_for_statement(ast_t assign_list, ast_t statement);
extern ast_t ast_intersection_for_statement(ast_t assign, ast_t statement);
extern ast_t ast_let_statement(ast_t assign_list, ast_t statement);
extern ast_t ast_include_statement(char* path);
extern ast_t ast_use_statement(char* path);

extern ast_t ast_undef_literal();
extern ast_t ast_number_literal(double value);
extern ast_t ast_bool_literal(uintptr_t value);
extern ast_t ast_string_literal(char* value);
extern ast_t ast_range_literal(ast_t start, ast_t increment, ast_t end);
extern ast_t ast_vector_literal(ast_t expr_list);
extern ast_t ast_function_literal(ast_t proto_list, ast_t expression);
extern ast_t ast_module_literal(ast_t proto_list, ast_t statement);

extern ast_t ast_function_call(char* name, ast_t param_list);
extern ast_t ast_if_expression(ast_t condition, ast_t expression, ast_t else_expr);
extern ast_t ast_let_expression(ast_t assign_list, ast_t expression);
extern ast_t ast_binary_expression(uintptr_t type, ast_t expr1, ast_t expr2);
extern ast_t ast_unary_expression(uintptr_t type, ast_t expression);
extern ast_t ast_vector_index(ast_t vector, ast_t index);
extern ast_t ast_list_comprehension(ast_t assign_list, ast_t condition, uintptr_t each, ast_t expression);

extern int ast_walk(ast_t ast, int (*fn)(ast_t node, size_t index, void *data), int (*fn2)(ast_t node, size_t index, void *data), void *data);

#endif // AST_H
