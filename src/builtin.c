#include "builtin.h"
#include "compiler.h"
#include "context.h"
#include "tree.h"
#include <stdint.h>
#include <string.h>

/********
* SPHERE *
 ********/
static tree_t sphere_default(void) {
    /* Default parameter values. */
    tree_t r = tree_new_siblings(1);
    r[1].a = ast_bind_statement("r", ast_number_literal(1.0));
    return r;
}

static int sphere_param(ast_t param, tree_t passed_values) {
    /* Check other parameter names. */
    const char *name = param[2].s;
    if(!strcmp("d", name)) passed_values[1].a = ast_bind_statement("r",
        ast_binary_expression(BINARY_OP_DIVIDE, param[3].a, ast_number_literal(2.0))
    );
    else return 1;
    return 0;
}

static void sphere_code(context_t context) {
    append_code_u(context, OP_SPHERE);
}

/******
* CUBE *
 ******/
static tree_t cube_default(void) {
    /* Default parameter values. */
    tree_t r = tree_new_siblings(2);
    r[1].a = ast_bind_statement("size", ast_number_literal(1.0));
    r[2].a = ast_bind_statement("center", ast_bool_literal(0));
    return r;
}

static int cube_param(ast_t param, tree_t passed_values) {
    return 1;
}

static void cube_code(context_t context) {
    append_code_u(context, OP_CUBE);
}

/**********
* CYLINDER *
 **********/
static tree_t cylinder_default(void) {
    /* Default parameter values. */
    tree_t r = tree_new_siblings(4);
    r[1].a = ast_bind_statement("h", ast_number_literal(1.0));
    r[2].a = ast_bind_statement("r1", ast_number_literal(1.0));
    r[3].a = ast_bind_statement("r2", ast_number_literal(1.0));
    r[4].a = ast_bind_statement("center", ast_bool_literal(0));
    return r;
}

static int cylinder_param(ast_t param, tree_t passed_values) {
    /* Check other parameter names. */
    const char *name = param[2].s;
    if(!strcmp("d1", name)) passed_values[2].a = ast_bind_statement("r1",
        ast_binary_expression(BINARY_OP_DIVIDE, param[3].a, ast_number_literal(2.0))
    );
    else if(!strcmp("d2", name)) passed_values[3].a = ast_bind_statement("r2",
        ast_binary_expression(BINARY_OP_DIVIDE, param[3].a, ast_number_literal(2.0))
    );
    else if(!strcmp("r", name)) {
        passed_values[2].a = ast_bind_statement("r1", param[3].a);
        passed_values[3].a = ast_bind_statement("r2", param[3].a);
    }
    else if(!strcmp("d", name)) {
        passed_values[2].a = ast_bind_statement("r1",
            ast_binary_expression(BINARY_OP_DIVIDE, param[3].a, ast_number_literal(2.0))
        );
        passed_values[3].a = ast_bind_statement("r2",
            ast_binary_expression(BINARY_OP_DIVIDE, param[3].a, ast_number_literal(2.0))
        );
    }
    else return 1;
    return 0;
}

static void cylinder_code(context_t context) {
    append_code_u(context, OP_CYLINDER);
}

/***********
* TRANSLATE *
 ***********/
static tree_t translate_default(void) {
    /* Default parameter values. */
    tree_t r = tree_new_siblings(1);
    ast_t list = ast_expression_list();
    list = tree_resize(list, 4);
    list[2].a = ast_number_literal(0.0);
    list[3].a = ast_number_literal(0.0);
    list[4].a = ast_number_literal(0.0);
    r[1].a = ast_bind_statement("v", ast_vector_literal(list));
    return r;
}

static int translate_param(ast_t param, tree_t passed_values) {
    /* Check other parameter names. */
    return 1;
}

static void translate_code(context_t context) {
    append_code_u(context, OP_TRANSLATE);
}

/********
* ROTATE *
 ********/
static tree_t rotate_default(void) {
    /* Default parameter values. */
    tree_t r = tree_new_siblings(2);
    r[1].a = ast_bind_statement("a", ast_number_literal(0.0));
    ast_t list = ast_expression_list();
    list = tree_resize(list, 4);
    list[2].a = ast_number_literal(0.0);
    list[3].a = ast_number_literal(0.0);
    list[4].a = ast_number_literal(1.0);
    r[2].a = ast_bind_statement("v", ast_vector_literal(list));
    return r;
}

static int rotate_param(ast_t param, tree_t passed_values) {
    /* Check other parameter names. */
    return 1;
}

static void rotate_code(context_t context) {
    append_code_u(context, OP_ROTATE);
}

/*******
* UNION *
 *******/
static tree_t union_default(void) {
    /* Default parameter values. */
    return tree_new_siblings(0);
}

static int union_param(ast_t param, tree_t passed_values) {
    /* Check other parameter names. */
    return 1;
}

static void union_code(context_t context) {
    append_code_u(context, OP_UNION);
}

union tree_child_t builtins[] = {
    {.u = 6 * 5},
    {.s = "sphere"}, {.u = BIND_TYPE_MODULE},
        {.p = sphere_default}, {.p = sphere_param}, {.p = sphere_code},
    {.s = "cube"}, {.u = BIND_TYPE_MODULE},
        {.p = cube_default}, {.p = cube_param}, {.p = cube_code},
    {.s = "cylinder"}, {.u = BIND_TYPE_MODULE},
        {.p = cylinder_default}, {.p = cylinder_param}, {.p = cylinder_code},
    {.s = "translate"}, {.u = BIND_TYPE_MODULE},
        {.p = translate_default}, {.p = translate_param}, {.p = translate_code},
    {.s = "rotate"}, {.u = BIND_TYPE_MODULE},
        {.p = rotate_default}, {.p = rotate_param}, {.p = rotate_code},
    {.s = "union"}, {.u = BIND_TYPE_MODULE},
        {.p = union_default}, {.p = union_param}, {.p = union_code}
};

const tree_t search_in_builtins(const char *name) {
    size_t i;
    for(i = 1; i <= builtins[0].u; i += 5) {
        if(!strcmp(name, builtins[i].s)) return &builtins[i];
    }
    return NULL;
}
