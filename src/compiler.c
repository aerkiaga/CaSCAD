#include "ast.h"
#include "compiler.h"
#include "context.h"
#include "tree.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h> //D
#include <string.h>

static int dependencies_walk_fn(ast_t node, size_t index, void *data) {
    tree_t list = (tree_t) data;
    if(index == 0) {
        switch(node->u) {
            case AST_TYPE_STATEMENT_LIST:
                return 1;
            case AST_TYPE_FN_OPERATOR:
            case AST_TYPE_PRE_OPERATOR:
            case AST_TYPE_IF_STATEMENT:
            case AST_TYPE_FOR_STATEMENT:
            case AST_TYPE_INTERSECTION_FOR_STATEMENT:
            case AST_TYPE_LET_STATEMENT:
                return 2;
            case AST_TYPE_INCLUDE_STATEMENT:
            case AST_TYPE_USE_STATEMENT:
                list = tree_append_children(list, NULL);
                list[list[0].u].s = strdup(node[2].s);
                puts(list[list[0].u].s); //D
                return INT_MAX;
            default:
                return INT_MAX;
        }
        return 0;
    }
}

tree_t get_raw_dependency_list(ast_t ast) {
    tree_t r = tree_new_siblings(0);
    ast_walk(ast, dependencies_walk_fn, NULL, (void *) r);
}

context_t compiler_produce_context(ast_t ast) {
}
