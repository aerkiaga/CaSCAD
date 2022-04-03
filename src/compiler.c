#include "ast.h"
#include "compiler.h"
#include "context.h"
#include "deps.h"
#include "tree.h"
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern _Noreturn void error(const char *fmt, ...);

struct compile_fn_shared_t {
    uintptr_t parent_type; // storage for context->parent_type into fn2
    size_t statement_count; // number of statements in current list
    ptrdiff_t var_count_address; // address of (...) number of variables in function
    int no_children; // current node' children (if any) will not be expanded
};

static int compile_walk_fn(ast_t node, size_t index, void *data, void **common);
static int compile_walk_fn2(ast_t node, size_t index, void *data, void **common);

static void push_variable_scope(context_t context) {
    tree_t new_scope = tree_new_siblings(0);
    context->scope_stack = tree_append_children(context->scope_stack, new_scope);
}

static void pop_variable_scope(context_t context) {
    free(context->scope_stack[context->scope_stack[0].u].a);
    context->scope_stack = tree_remove_last_sibling(context->scope_stack);
}

static tree_t search_in_partial_scope(const char *name, tree_t scope) {
    size_t index;
    for(index = 1; index <= scope[0].u; index += 4) {
        if(!strcmp(name, scope[index].s)) return scope + index;
    }
    return NULL;
}

static tree_t search_in_full_scope(const char *name, context_t context) {
    size_t index;
    for(index = context->scope_stack[0].u; index >= 1; index--) {
        tree_t r;
        if(r = search_in_partial_scope(name, context->scope_stack[index].a))
            return r;
    }
    return NULL;
}

static tree_t add_variable_to_scope(const char *name, tree_t *scope_out) {
    union tree_child_t new_node;
    new_node.s = strdup(name);
    *scope_out = tree_append_sibling(*scope_out, &new_node);
    *scope_out = tree_append_sibling(*scope_out, &new_node);
    *scope_out = tree_append_sibling(*scope_out, &new_node);
    *scope_out = tree_append_sibling(*scope_out, &new_node);
    return *scope_out + (*scope_out)[0].u - 3;
}

static tree_t *get_inner_scope_ptr(context_t context) {
    return &context->scope_stack[context->scope_stack[0].u].a;
}

static ptrdiff_t get_next_data_space(context_t context) {
    return 1 + 2*context->data_variables;
}

static ptrdiff_t allocate_variable(context_t context) {
    ptrdiff_t r = get_next_data_space(context);
    context->data_variables++;
    return r;
}

static int statement_list_walk_fn(ast_t node, size_t index, void *data, void **common) {
    if(index == 0 || !node->a) return 1;
    context_t context = (context_t) data;
    struct compile_fn_shared_t **shared = (struct compile_fn_shared_t **) common;
    tree_t *inner_scope = get_inner_scope_ptr(context);
    uintptr_t child_type = node->a[1].u;
    switch(child_type) {
        case AST_TYPE_BIND_STATEMENT: {
            const char *name = node->a[2].s;
            tree_t variable = search_in_partial_scope(name, *inner_scope);
            if(!variable) variable = add_variable_to_scope(name, inner_scope);
            /* Assign expression|function|module AST. */
            variable[1].u = BIND_TYPE_NONE;
            variable[2].a = NULL;
            variable[3].a = node->a[3].a;
            break;
        }
        case AST_TYPE_INCLUDE_STATEMENT:
            // TODO
            break;
        case AST_TYPE_USE_STATEMENT:
            // TODO
            break;
    }
    return 1;
}

static ptrdiff_t get_current_address(context_t context) {
    return context->code[0].u;
}

static ptrdiff_t append_code_u(context_t context, uintptr_t value) {
    union tree_child_t new_node;
    new_node.u = value;
    context->code = tree_append_sibling(context->code, &new_node);
    return get_current_address(context);
}

static ptrdiff_t append_code_d(context_t context, double value) {
    union tree_child_t new_node;
    new_node.d = value;
    context->code = tree_append_sibling(context->code, &new_node);
    return get_current_address(context);
}

static ptrdiff_t append_code_s(context_t context, char *value) {
    union tree_child_t new_node;
    new_node.s = value;
    context->code = tree_append_sibling(context->code, &new_node);
    return get_current_address(context);
}

static void remove_code(context_t context) {
    context->code = tree_remove_last_sibling(context->code);
}

static void compile_subexpression(tree_t ast, context_t context, uintptr_t parent_type) {
    uintptr_t old_parent_type = context->parent_type;
    context->parent_type = parent_type;
    ast_walk(ast, compile_walk_fn, compile_walk_fn2, (void *) context);
    context->parent_type = old_parent_type;
}

static int compile_walk_fn_choose(
    ast_t node, size_t index, context_t context, struct compile_fn_shared_t **shared
) {
    switch(node->u) {
        case AST_TYPE_STATEMENT_LIST: {
            /* Add all identifiers, in order of first occurrence. */
            /* These contain their AST and a NULL address. */
            ast_walk(node - 1, statement_list_walk_fn, NULL, context);
            tree_t *inner_scope = get_inner_scope_ptr(context);
            size_t i;
            for(i = 1; i <= (*inner_scope)[0].u; i += 4) {
                uintptr_t bind_type = (*inner_scope + i)[1].u;
                if(bind_type != BIND_TYPE_NONE) continue;
                tree_t ast = (*inner_scope + i)[3].a;
                uintptr_t type = ast[1].u;
                /* Check if this defines a function, module or variable. */
                if(type == AST_TYPE_FUNCTION_LITERAL || type == AST_TYPE_MODULE_LITERAL) {
                    /* === Jump over code. === */
                    append_code_u(context, OP_JUMP);
                    ptrdiff_t jump_address = append_code_u(context, 0);
                    ptrdiff_t code_address = get_current_address(context) + 1;
                    /* === Add all the code. === */
                    compile_subexpression(ast, context, node->u);
                    inner_scope = get_inner_scope_ptr(context);
                    /* Remember bound variable. */
                    uintptr_t type = ast[1].u;
                    if(type == AST_TYPE_FUNCTION_LITERAL)
                        (*inner_scope + i)[1].u = BIND_TYPE_FUNCTION;
                    else
                        (*inner_scope + i)[1].u = BIND_TYPE_MODULE;
                    (*inner_scope + i)[2].u = code_address;
                    /* Finish jump. */
                    (context->code + jump_address)->u = get_current_address(context) + 1;
                } else {
                    /* === Run expression. === */
                    compile_subexpression(ast, context, node->u);
                    inner_scope = get_inner_scope_ptr(context);
                    /* === Move computed data to variable. === */
                    ptrdiff_t var = allocate_variable(context);
                    append_code_u(context, OP_STORE);
                    append_code_u(context, var);
                    /* Remember bound variable. */
                    (*inner_scope + i)[1].u = BIND_TYPE_VARIABLE;
                    (*inner_scope + i)[2].u = var;
                }
            }
            /* === Run all statements. === */
            (*shared)->statement_count = 0;
            for(i = 1; i < node[-1].u; i++) {
                uintptr_t child_type = node[i].a[1].u;
                switch(child_type) {
                    case AST_TYPE_BIND_STATEMENT:
                    case AST_TYPE_INCLUDE_STATEMENT:
                    case AST_TYPE_USE_STATEMENT:
                        break;
                    default:
                        (*shared)->statement_count++;
                }
            }
            return 1;
        }
        case AST_TYPE_BIND_STATEMENT: {
            /* This was handled in the AST_TYPE_STATEMENT_LIST case. */
            (*shared)->no_children = 1;
            return INT_MAX;
        }
        case AST_TYPE_MODULE_OPERATOR: {
            /* Execute children first. */
            return 2;
        }
        case AST_TYPE_UNDEF_LITERAL: {
            append_code_u(context, OP_UNDEF);
            (*shared)->no_children = 1;
            return 1;
        }
        case AST_TYPE_NUMBER_LITERAL: {
            double value = node[1].d;
            append_code_u(context, OP_NUMBER);
            append_code_d(context, value);
            (*shared)->no_children = 1;
            return 2;
        }
        case AST_TYPE_BOOL_LITERAL: {
            uintptr_t value = node[1].u;
            if(value) append_code_u(context, OP_TRUE);
            else append_code_u(context, OP_FALSE);
            (*shared)->no_children = 1;
            return 2;
        }
        case AST_TYPE_STRING_LITERAL: {
            const char *value = node[1].s;
            append_code_u(context, OP_STRING);
            append_code_s(context, strdup(value));
            (*shared)->no_children = 1;
            return 2;
        }
        case AST_TYPE_FUNCTION_LITERAL:
        case AST_TYPE_MODULE_LITERAL: {
            size_t parameter_count = node[1].a[0].u - 1;
            tree_t *inner_scope = get_inner_scope_ptr(context);
            /* === Save all variables within scope. === */
            append_code_u(context, OP_SAVE);
            append_code_u(context, get_next_data_space(context));
            (*shared)->var_count_address = append_code_u(context, 0);
            /* Modules have an implicit first parameter, @children. */
            ptrdiff_t last_param;
            if(node->u == AST_TYPE_MODULE_LITERAL) {
                tree_t variable = add_variable_to_scope(strdup("@children"), inner_scope);
                variable[1].u = BIND_TYPE_VARIABLE;
                variable[2].u = allocate_variable(context);
                last_param = variable[2].u;
                variable[3].a = ast_statement_list();
            }
            /* Make parameters into variables. */
            /* The parser puts them IN REVERSE ORDER! */
            size_t i;
            for(i = parameter_count + 1; i >= 2; i--) {
                const char *name = strdup(node[1].a[i].a[2].s);
                // TODO: check if name already exists (two parameters with same name)
                tree_t variable = add_variable_to_scope(name, inner_scope);
                variable[1].u = BIND_TYPE_VARIABLE;
                variable[2].u = allocate_variable(context);
                last_param = variable[2].u;
                tree_t ast = node[1].a[i].a[3].a;
                variable[3].a = ast;
            }
            if(node->u == AST_TYPE_MODULE_LITERAL) parameter_count++;
            ptrdiff_t start_address = last_param - 2*(parameter_count - 1);
            /* === Store all parameters into these variables. === */
            append_code_u(context, OP_VSTORE);
            append_code_u(context, start_address);
            append_code_u(context, parameter_count);
            return 2;
        }
        case AST_TYPE_FUNCTION_CALL:
        case AST_TYPE_MODULE_CALL: {
            const char *name = node[1].s;
            tree_t definition = search_in_full_scope(name, context);
            if(!definition) {
                /* OpenSCAD says: */
                /* WARNING: Ignoring unknown function '~', in file ~, line ~. */
                error("syntax error: '%s' not defined in current scope.", name);
            }
            uintptr_t bind_type = definition[1].u;
            if(node->u == AST_TYPE_FUNCTION_CALL && bind_type != BIND_TYPE_FUNCTION) {
                /* OpenSCAD says: */
                /* WARNING: Ignoring unknown function '~', in file ~, line ~. */
                error("syntax error: '%s' exists, but is not a function.", name);
            }
            if(node->u == AST_TYPE_MODULE_CALL && bind_type != BIND_TYPE_MODULE) {
                /* OpenSCAD says: */
                /* WARNING: Ignoring unknown module '~', in file ~, line ~. */
                error("syntax error: '%s' exists, but is not a module.", name);
            }
            /* Copy default parameters from function prototype. */
            /* The parser puts them IN REVERSE ORDER! */
            tree_t proto_list = definition[3].a[2].a;
            tree_t passed_values = tree_new_siblings(proto_list[0].u - 1);
            size_t i;
            for(i = 1; i < proto_list[0].u; i++) {
                passed_values[i].a = proto_list[proto_list[0].u + 1 - i].a;
            }
            /* Replace any values passed. */
            /* They are also placed IN REVERSE ORDER. */
            tree_t param_list = node[2].a;
            size_t numbered_argument = 1;
            for(i = param_list[0].u; i >= 2; i--) {
                tree_t param = param_list[i].a;
                if(param[1].u == AST_TYPE_BIND_STATEMENT) {
                    size_t k;
                    for(k = 1; k <= passed_values[0].u; k++) {
                        if(!strcmp(passed_values[k].a[2].s, param[2].s)) {
                            passed_values[k].a = param;
                            break;
                        }
                    }
                    if(k > passed_values[0].u) {
                        /* OpenSCAD says: */
                        /* WARNING: variable ~ not specified as parameter, in file ~, line ~ */
                        error("syntax error: '%s' does not name a paremeter of '%s'.", param[2].s, name);
                    }
                } else {
                    if(numbered_argument > proto_list[0].u - 1) {
                        /* OpenSCAD says: */
                        /* WARNING: Too many unnamed arguments supplied, in file ~, line ~ */
                        error("syntax error: %d unnamed paramaters passed to '%s', up to %d expected.",
                            numbered_argument, name, proto_list[0].u - 1
                        );
                    }
                    const char *param_name = passed_values[numbered_argument].a[2].s;
                    tree_t new_assignment = ast_bind_statement(strdup(param_name), param);
                    passed_values[numbered_argument].a = new_assignment;
                    numbered_argument++;
                }
            }
            /* === Push empty geometry if no explicit children. === */
            if(node->u == AST_TYPE_MODULE_CALL && context->parent_type != AST_TYPE_MODULE_OPERATOR) {
                append_code_u(context, OP_EMPTY);
            }
            /* === Compute and push values onto the stack. === */
            for(i = 1; i <= passed_values[0].u; i++) {
                tree_t assignment = passed_values[i].a;
                tree_t ast = assignment[3].a;
                compile_subexpression(ast, context, node->u);
            }
            /* === Perform the call. === */
            ptrdiff_t call_address = definition[2].u;
            append_code_u(context, OP_CALL);
            append_code_u(context, call_address);
            (*shared)->no_children = 1;
            return INT_MAX;
        }
        default:
            printf("%ld\n", node->u); //D
            error("fixme: unsupported AST node type.\n");
            return INT_MAX;
    }
}

/* preorder */
static int compile_walk_fn(ast_t node, size_t index, void *data, void **common) {
    context_t context = (context_t) data;
    struct compile_fn_shared_t **shared = (struct compile_fn_shared_t **) common;
    
    int r = 0;
    if(index == 0) {
        *shared = (struct compile_fn_shared_t *) malloc(sizeof(struct compile_fn_shared_t));
        (*shared)->no_children = 0;
        r = compile_walk_fn_choose(node, index, context, shared);
        push_variable_scope(context);
        (*shared)->parent_type = context->parent_type;
        context->parent_type = node->u;
    }
    
    return r;
}

static int compile_walk_fn2_choose(
    ast_t node, context_t context, struct compile_fn_shared_t **shared
) {
    switch(node->u) {
        case AST_TYPE_STATEMENT_LIST: {
            if(!(*shared)->statement_count) {
                /* === Push empty geometry. === */
                append_code_u(context, OP_EMPTY);
                break;
            }
            if((*shared)->statement_count < 2) break;
            if(context->parent_type == AST_TYPE_MODULE_OPERATOR) {
                /* === Group children to pass them up. === */
                append_code_u(context, OP_GROUP);
            } else {
                /* === Perform implicit union. === */
                append_code_u(context, OP_UNION);
            }
            append_code_u(context, (*shared)->statement_count);
            break;
        }
        case AST_TYPE_MODULE_OPERATOR: {
            ast_t function_call = node[1].a;
            compile_subexpression(function_call, context, node->u);
            break;
        }
        case AST_TYPE_FUNCTION_LITERAL:
        case AST_TYPE_MODULE_LITERAL: {
            /* Finish what was set up in fn. */
            size_t parameter_count = node[1].a[0].u - 1;
            tree_t ptr = context->code + (*shared)->var_count_address;
            ptrdiff_t var_space_base = ptr[-1].u;
            size_t variable_count = (get_next_data_space(context) - var_space_base) >> 1;
            ptr->u = variable_count;
            /* === Restore all variables within scope. === */
            append_code_u(context, OP_RESTORE);
            append_code_u(context, var_space_base);
            append_code_u(context, variable_count);
            /* Separate OP_RESTORE and OP_RETURN: future-proof. */
            append_code_u(context, OP_RETURN);
            break;
        }
    }
    return 0;
}

/* postorder */
static int compile_walk_fn2(ast_t node, size_t index, void *data, void **common) {
    context_t context = (context_t) data;
    struct compile_fn_shared_t **shared = (struct compile_fn_shared_t **) common;
    
    int r = 0;
    if(!index && (*shared)->no_children || index == node[-index - 1].u - 1) {
        context->parent_type = (*shared)->parent_type;
        r = compile_walk_fn2_choose(&node[-index], context, shared);
        pop_variable_scope(context);
        free(*shared);
    }
    return r;
}

context_t compiler_produce_with_deps(ast_t ast, deps_t deps, const char *script_path) {
    context_t r = (context_t) malloc(sizeof(struct context_value_t));
    r->code = tree_new_siblings(0);
    r->data = tree_new_siblings(0);
    r->call_stack = tree_new_siblings(0);
    r->call_stack_pushed = 0;
    r->tmp_stack = tree_new_siblings(0);
    r->tmp_stack_pushed = 0;
    
    r->script_path = script_path ? strdup(script_path) : NULL;
    r->deps = deps;
    r->parent_type = AST_TYPE_NONE;
    r->scope_stack = tree_new_siblings(0);
    r->data_variables = 0;
    
    push_variable_scope((void *) r);
    ast_walk(ast, compile_walk_fn, compile_walk_fn2, (void *) r);
    append_code_u(r, OP_FINISH);
    pop_variable_scope((void *) r);
    return r;
}

context_t compiler_produce(ast_t ast, const char *script_path) {
    debug_ast(ast); //D
    deps_t deps = get_deps_from_ast(ast, script_path);
    return compiler_produce_with_deps(ast, deps, script_path);
}
