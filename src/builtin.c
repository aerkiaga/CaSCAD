#include "builtin.h"
#include "compiler.h"
#include "context.h"
#include "tree.h"
#include <stdint.h>
#include <string.h>

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

union tree_child_t builtins[] = {
    {.u = 1},
    {.s = "cylinder"}, {.u = BIND_TYPE_MODULE},
        {.p = cylinder_default}, {.p = cylinder_param}, {.p = cylinder_code}
};

const tree_t search_in_builtins(const char *name) {
    size_t i;
    for(i = 1; i <= builtins[0].u; i += 3) {
        if(!strcmp(name, builtins[i].s)) return &builtins[i];
    }
    return NULL;
}
