#include "ast.h"
#include "tree.h"
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

ast_t ast_append_child(ast_t ast, ast_t node) {
    return tree_append_children(ast, node);
}

ast_t ast_sized_list(uintptr_t type, size_t size) {
    ast_t r = tree_new_siblings(size + 1);
    tree_node_sibling(r, 0)->u = type;
    return r;
}

ast_t ast_empty(uintptr_t type) {
    return ast_sized_list(type, 0);
}

void ast_set_type(ast_t ast, uintptr_t type) {
    tree_node_sibling(ast, 0)->u = type;
}

ast_t ast_string(uintptr_t type, char *string) {
    ast_t r = ast_sized_list(type, 1);
    tree_node_sibling(r, 1)->s = string;
    return r;
}

ast_t ast_string_child(uintptr_t type, char *string, ast_t child) {
    ast_t r = ast_sized_list(type, 2);
    tree_node_sibling(r, 1)->s = string;
    tree_node_sibling(r, 2)->a = child;
    return r;
}

ast_t ast_two_children(uintptr_t type, ast_t child1, ast_t child2) {
    ast_t r = ast_sized_list(type, 2);
    tree_node_sibling(r, 1)->a = child1;
    tree_node_sibling(r, 2)->a = child2;
    return r;
}




ast_t ast_statement_list() {
    return ast_empty(AST_TYPE_STATEMENT_LIST);
}

ast_t ast_expression_list() {
    return ast_empty(AST_TYPE_STATEMENT_LIST);
}

ast_t ast_proto_list() {
    return ast_empty(AST_TYPE_PROTO_LIST);
}

ast_t ast_parameter_list() {
    return ast_empty(AST_TYPE_PARAMETER_LIST);
}

ast_t ast_assignment_list() {
    return ast_empty(AST_TYPE_ASSIGNMENT_LIST);
}

ast_t ast_module_operator(ast_t value) {
    ast_t r =  ast_sized_list(AST_TYPE_MODULE_OPERATOR, 1);
    tree_node_sibling(r, 1)->a = value;
    return r;
}

ast_t ast_predefined_operator(uintptr_t type) {
    ast_t r =  ast_sized_list(AST_TYPE_PRE_OPERATOR, 1);
    tree_node_sibling(r, 1)->u = type;
    return r;
}

ast_t ast_bind_statement(char *name, ast_t value) {
    return ast_string_child(AST_TYPE_BIND_STATEMENT, name, value);
}

ast_t ast_if_statement(ast_t condition, ast_t statement, ast_t else_stmt) {
    ast_t r = ast_sized_list(AST_TYPE_IF_STATEMENT, else_stmt ? 3 : 2);
    tree_node_sibling(r, 1)->a = condition;
    tree_node_sibling(r, 2)->a = statement;
    if(else_stmt) tree_node_sibling(r, 3)->a = else_stmt;
    return r;
}

ast_t ast_for_statement(ast_t assign_list, ast_t statement) {
    return ast_two_children(AST_TYPE_FOR_STATEMENT, assign_list, statement);
}

ast_t ast_intersection_for_statement(ast_t assign, ast_t statement) {
    return ast_two_children(AST_TYPE_INTERSECTION_FOR_STATEMENT, assign, statement);
}

ast_t ast_let_statement(ast_t assign_list, ast_t statement) {
    return ast_two_children(AST_TYPE_LET_STATEMENT, assign_list, statement);
}

ast_t ast_include_statement(char *path) {
    return ast_string(AST_TYPE_INCLUDE_STATEMENT, path);
}

ast_t ast_use_statement(char *path) {
    return ast_string(AST_TYPE_USE_STATEMENT, path);
}

ast_t ast_undef_literal() {
    ast_t r = ast_sized_list(AST_TYPE_UNDEF_LITERAL, 0);
    return r;
}

ast_t ast_number_literal(double value) {
    ast_t r = ast_sized_list(AST_TYPE_NUMBER_LITERAL, 1);
    tree_node_sibling(r, 1)->d = value;
    return r;
}

ast_t ast_bool_literal(uintptr_t value) {
    ast_t r = ast_sized_list(AST_TYPE_BOOL_LITERAL, 1);
    tree_node_sibling(r, 1)->u = value;
    return r;
}

ast_t ast_string_literal(char *value) {
    return ast_string(AST_TYPE_STRING_LITERAL, value);
}

ast_t ast_range_literal(ast_t start, ast_t increment, ast_t end) {
    ast_t r = ast_sized_list(AST_TYPE_RANGE_LITERAL, 3);
    tree_node_sibling(r, 1)->a = start;
    tree_node_sibling(r, 2)->a = increment;
    tree_node_sibling(r, 3)->a = end;
    return r;
}

ast_t ast_vector_literal(ast_t expr_list) {
    ast_set_type(expr_list, AST_TYPE_VECTOR_LITERAL);
    return expr_list;
}

ast_t ast_function_literal(ast_t proto_list, ast_t expression) {
    return ast_two_children(AST_TYPE_FUNCTION_LITERAL, proto_list, expression);
}

ast_t ast_module_literal(ast_t proto_list, ast_t statement) {
    return ast_two_children(AST_TYPE_MODULE_LITERAL, proto_list, statement);
}

ast_t ast_identifier_expression(char *name) {
    return ast_string(AST_TYPE_IDENTIFIER_EXPRESSION, name);
}

ast_t ast_function_call(char *name, ast_t param_list) {
    return ast_string_child(AST_TYPE_FUNCTION_CALL, name, param_list);
}

ast_t ast_module_call(char *name, ast_t param_list) {
    return ast_string_child(AST_TYPE_MODULE_CALL, name, param_list);
}

ast_t ast_if_expression(ast_t condition, ast_t expression, ast_t else_expr) {
    ast_t r = ast_sized_list(AST_TYPE_IF_EXPRESSION, else_expr ? 3 : 2);
    tree_node_sibling(r, 1)->a = condition;
    tree_node_sibling(r, 2)->a = expression;
    if(else_expr) tree_node_sibling(r, 3)->a = else_expr;
    return r;
}

ast_t ast_let_expression(ast_t assign_list, ast_t expression) {
    return ast_two_children(AST_TYPE_LET_EXPRESSION, assign_list, expression);
}

ast_t ast_binary_expression(uintptr_t type, ast_t expr1, ast_t expr2) {
    ast_t r = ast_sized_list(AST_TYPE_BINARY_EXPRESSION, 3);
    tree_node_sibling(r, 1)->u = type;
    tree_node_sibling(r, 2)->a = expr1;
    tree_node_sibling(r, 3)->a = expr2;
    return r;
}

ast_t ast_unary_expression(uintptr_t type, ast_t expression) {
    ast_t r = ast_sized_list(AST_TYPE_UNARY_EXPRESSION, 2);
    tree_node_sibling(r, 1)->u = type;
    tree_node_sibling(r, 2)->a = expression;
    return r;
}

ast_t ast_vector_index(ast_t vector, ast_t index) {
    return ast_two_children(AST_TYPE_VECTOR_INDEX, vector, index);
}

ast_t ast_list_comprehension(ast_t assign_list, ast_t condition, uintptr_t each, ast_t expression) {
    ast_t r = ast_sized_list(AST_TYPE_LIST_COMPREHENSION, 4);
    tree_node_sibling(r, 1)->a = assign_list;
    tree_node_sibling(r, 2)->a = condition;
    tree_node_sibling(r, 3)->u = each;
    tree_node_sibling(r, 4)->a = expression;
    return r;
}

int ast_walk(
    ast_t ast,
    int (*fn)(ast_t node, size_t index, void *data, void **common),
    int (*fn2)(ast_t node, size_t index, void *data, void **common),
    void *data
) {
    return tree_walk((tree_t) ast, fn, fn2, data);
}

int ast_debug_walk_fn(ast_t node, size_t index, void *data, void **common) {
    if(index == 0) {
        switch(node->u) {
            case AST_TYPE_STATEMENT_LIST:
                fprintf(stderr, "AST_TYPE_STATEMENT_LIST\n");
                return 1;
            case AST_TYPE_PROTO_LIST:
                fprintf(stderr, "AST_TYPE_PROTO_LIST\n");
                return 1;
            case AST_TYPE_PARAMETER_LIST:
                fprintf(stderr, "AST_TYPE_PARAMETER_LIST\n");
                return 1;
            case AST_TYPE_BIND_STATEMENT:
                fprintf(stderr, "AST_TYPE_BIND_STATEMENT %s\n", node[1].s);
                return 2;
            case AST_TYPE_UNDEF_LITERAL:
                fprintf(stderr, "AST_TYPE_UNDEF_LITERAL\n");
                return 1;
            case AST_TYPE_NUMBER_LITERAL:
                fprintf(stderr, "AST_TYPE_NUMBER_LITERAL %g\n", node[1].d);
                return 2;
            case AST_TYPE_BOOL_LITERAL:
                fprintf(stderr, "AST_TYPE_BOOL_LITERAL %s\n", node[1].u ? "true" : "false");
                return 2;
            case AST_TYPE_STRING_LITERAL:
                fprintf(stderr, "AST_TYPE_STRING_LITERAL %s\n", node[1].s);
                return 2;
            case AST_TYPE_FUNCTION_LITERAL:
                fprintf(stderr, "AST_TYPE_FUNCTION_LITERAL\n");
                return 1;
            case AST_TYPE_MODULE_LITERAL:
                fprintf(stderr, "AST_TYPE_MODULE_LITERAL\n");
                return 1;
            case AST_TYPE_FUNCTION_CALL:
                fprintf(stderr, "AST_TYPE_FUNCTION_CALL %s\n", node[1].s);
                return 2;
        }
        return INT_MAX;
    }
    return 0;
}

void debug_ast(ast_t ast) {
    fputs(
        "Abstract Syntax Tree\n"
        "====================\n",
        stderr
    );
    ast_walk(ast, ast_debug_walk_fn, NULL, NULL);
    fputs(
        "====================\n"
        "\n",
        stderr
    );
}

